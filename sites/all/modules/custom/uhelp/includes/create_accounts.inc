<?php

function _uhelp_enabled_entities() {
  $whitelist = array(
    'civicrm_address' => 'address',
    'civicrm_event' => 'event',
    'civicrm_contact' => 'contact',
    'civicrm_contribution' => 'contribution',
    'civicrm_participant' => 'participant',
    'civicrm_relationship' => 'relationship',
    'civicrm_relationship_type' => 'relationship_type',
    'civicrm_activity' => 'activity',
    'civicrm_entity_tag' => 'entity_tag',
    'civicrm_membership' => 'membership',
    'civicrm_membership_type' => 'membership_type',
    'civicrm_group' => 'group',
    'civicrm_grant' => 'grant',
    'civicrm_tag' => 'tag',
  );
  //dirty check for whether financialType exists
//  if (!method_exists('CRM_Contribute_PseudoConstant', 'contributionType' )){
//    $whitelist['civicrm_financial_type'] = 'financial_type';
//  }
  return $whitelist;
}


//
//
//

function _uhelp_get_entity_name_from_camel($entity) {
  if ($entity == strtolower($entity)) {
    return $entity;
  }
  else {
    $entity = ltrim(strtolower(
      str_replace('U_F', 'uf',
        // That's CamelCase, beside an odd UFCamel that is expected as uf_camel
        preg_replace('/(?=[A-Z])/', '_$0', $entity)
      )), '_');
  }
  return $entity;
}

/**
 * Implement the post hook and fire the corresponding rules event.
 *
 * @param $op
 * @param $object_name
 * @param $object_id
 * @param $object_ref
 */
 

function uhelp_civicrm_post($op, $object_name, $object_id, &$object_ref) {
  //dsm("test one ".$object_name);
  $contact_types = array(
    'Individual',
    'Household',
    'Organization',
  );
  if (in_array($object_name, $contact_types)) {
    $object_name = 'Contact';
  }

  $valid_objects = _uhelp_enabled_entities();
$entity_name = $object_name;
  $entity_name = _uhelp_get_entity_name_from_camel($object_name);
  if (!in_array($entity_name, $valid_objects, TRUE)) {
    return;
  }
  $event_name = NULL;
  switch ($op) {
    case 'create':
      //dsm($entity_name."...".$object_id."...".$op);
 //      dsm($object_ref);
//       dsm($object_ref->contact_sub_type);
       $subtype =  $object_ref->contact_sub_type;
//       print "--".$subtype."--";
       $subtypestudent= "Student";
       if (strpos($subtype,'Student') !== false) {
         //dsm($subtype);
         //dsm($object_ref);       
         uhelp_action_create_user($object_ref,1);

       }
//       if ($subtype == $subtypestudent) {
//         dsm($subtype);
//         dsm($object_ref);
//         }      
    case 'edit':
    case 'delete':
      $event_name = 'civicrm_' . $entity_name . "_{$op}";
      break;

    default:
      break;

  }
       
}

function uhelp_action_create_user($contact, $is_active, $notify = FALSE, $signin = FALSE) {
  if (!is_array($contact)) {
    // Perhaps we should be accepting object rather than array here?
    $contact = (array) $contact;
  }
  // We'll use the civicrm sync mechanism to see if Civi can match the
  // contact to an existing user.
  //
  // Don't think this is a great approach but will use for now - could
  // just create the user but no great support for that yet.
  if (empty($contact['display_name']) || empty($contact['email'])) {
    $contact = civicrm_api('contact', 'getsingle', array(
      'version' => 3,
      'id' => $contact['id'],
      'sequential' => 1,
//      'status' => 1,
      'return' => 'email,display_name',
      'roles' => array(
      DRUPAL_AUTHENTICATED_RID => 'authenticated user',
             9 => 'HELP Student',
            ),
    ));
  }
  if (!is_string($contact['email']) && isset($contact['email'][0]->email)) {
    $contact['email'] = $contact['email'][0]->email;
  }
  // @TODO What happens if they don't have an email at this point?
  // An email is a pre-requisite for a Drupal account, so the action
  // fails if they don't have an email.

$parts = explode("@", $contact['email'] );
$login_name = $parts[0];

  $params = array(
//    'name' => $contact['display_name'],
    'name' => $login_name,
    'mail' => $contact['email'],
    'email' => $contact['email'],
    'init' => $contact['email'],
  );

  // Check if the requested username is available.
  $errors = array();
  $config = CRM_Core_Config::singleton();
  $config->userSystem->checkUserNameEmailExists($params, $errors);
  if (!empty($errors)) {
    foreach ($errors as $error) {
      drupal_set_message(t($error), 'error');
    }
    return FALSE;
  }
$params['cms_name'] = $params['name'];
//  $params['cms_name'] = $params['name'] = $user['name'] = !empty($contact['display_name']) ? $contact['display_name'] : $params['mail'];

//set a random password

  $params['cms_pass'] = $user['pass'] = substr(str_shuffle("abcefghijklmnopqrstuvwxyz"), 0, 8);
  $params['status'] = $is_active;


  if ($notify) {
    $params['notify'] = TRUE;
  }

//TODO this probably does not need to be set twice
// here and in the initial user array declaration above 
  $params['roles'] = array(
    DRUPAL_AUTHENTICATED_RID => 'authenticated user',
           9 => 'HELP Student',
  );

  // Set $config->inCiviCRM = TRUE to prevent creating a duplicate
  // contact from user_save().
  $config = CRM_Core_Config::singleton();
  $config->inCiviCRM = TRUE;
//dsm($params);
  $user_object = user_save('', $params);
  $user_object->password = $user['pass'];

  $config->inCiviCRM = FALSE;

  // If selected in action configuration, notify the newly created
  // user & send registration link. Does not contain password in D7.
  if ($notify) {
    drupal_mail('user', 'register_no_approval_required', $params['mail'], NULL, array('account' => $user_object), variable_get('site_mail', 'noreply@example..com'));
  }

  // CiviCRM doesn't do this when created off CiviCRM Form.
  //
  // Note that we 'pretend' to be logging in to make it do a ufmatch
  // on just the email.
  CRM_Core_BAO_UFMatch::synchronizeUFMatch($user_object, $user_object->uid, $contact['email'], 'drupal', NULL, NULL, TRUE);

  // If selected in action configuration, automatically sign in the
  // current user.
  if ($signin) {
    global $user;
    $user = user_load($user_object->uid);
    watchdog('civicrm_entity', 'User %name logged in via CiviCRM Entity rule execution.', array('%name' => $user->name), WATCHDOG_INFO);
    $form_values = array('uid' => $user->uid);
    user_login_finalize($form_values);
  }

  return array('civicrm_user' => $user_object);
}


