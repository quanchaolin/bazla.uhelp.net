<?php


function student_util_help_year_form($form, &$form_state) {
  $form['help_year_fieldset'] =
    array(
	  '#type' => 'fieldset',
	  );
  $form['help_year_fieldset']['submit_button'] =
    array(
	  '#type' => 'submit',
	  '#value' => t('Update Help Year'),
	  );
  return $form;
}

function student_util_help_year_form_submit($form, &$form_state) {
  student_util_update_help_year();
}

function student_util_update_help_year() {
  civicrm_initialize();
  //find all relationships to help
  $result = civicrm_api3('Relationship', 'get',
			 array(
			       'sequential' => 1,
			       'contact_id_a' => 1,
			       'relationship_type_id' => 50,
			       'options' => array('limit' => 5000),
			       ));

  //for each relationship
  if ($result && isset($result['values']) && $result['values']) {
    foreach($result['values'] as $k=>$relationship) {
      if ($relationship['end_date'] &&
	  strtotime($relationship['end_date']) < strtotime('now')) {
	$year = 0;
      }
      else {
	$year =
	  student_util_get_help_year(strtotime($relationship['start_date']));
      }
      student_util_set_help_year($relationship['contact_id_b'], $year);
    }
  }
}

function student_util_set_help_year($contact_id, $year) {
  civicrm_initialize();
  $field_label = "HELP Year";
  $result = civicrm_api3('CustomField', 'get',
			 array(
			       'sequential' => 1,
			       'label' => $field_label,
			       ));

  if ($result && isset($result['values']) && $result['values']) {
    $field_id = $result['values'][0]['id'];
  }

  if ($field_id) {
    $params = array('contact_id' => $contact_id,
		    'custom_'.$field_id => $year);

    $result = civicrm_api3('Contact', 'create', $params);
  }
  //save contact record from relatioship, setting year
}
function student_util_get_help_year($orig_start) {
  //set $date to last Aug 31st
  if (date('m') >= 9) {
    $date = strtotime(date('Y').'-08-31');
  }
  else {
    $date = strtotime((date('Y')-1).'-08-31');
  }

  if (date('m', $orig_start) >= 9) {
    $start = strtotime(date('Y', $orig_start).'-08-31');
  }
  else {
    $start = strtotime((date('Y',$orig_start)-1).'-08-31');
  }

  return date('Y', $date) - date('Y', $start) + 1;
}

function student_util_civicrm_postProcess($form_name, &$form) {
  if ($form_name == 'CRM_Contact_Form_Relationship') {
  
    // if this the student is enrolled at (relationship type)
    if ($form->_relationshipTypeId == 50) {
      $relationship = $form->_submitValues;
      if ($relationship['related_contact_id'] == 1) {
        $year =
    student_util_get_help_year(strtotime($relationship['start_date']));
        student_util_set_help_year($form->_contactId, $year);
      }
    }
  }
}
