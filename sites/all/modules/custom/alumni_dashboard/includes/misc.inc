<?php


function alumni_dashboard_get_field($title, $type, $req=FALSE, $states=array(),
				    $prefix = '', $suffix = '', $weight = 0,
				    $description = '',$options = array(),
				    $default = '') {

  $field = array(		 
		 '#title' => $title,
		 '#type' => $type,
		 '#default_value' => $default,
		 '#description' => $description,
		 '#prefix' => $prefix,
		 '#suffix' => $suffix,
		 '#weight' => $weight,
		 '#required' => $req,
		 );

  if ($type == 'date_popup') {
    $field['#date_label_position'] = 'within';
    $field['#size'] = 15;
    $field['#date_format'] = 'd M Y';
    $field['#timepicker'] = FALSE;
  }
		 
  else if ($type == 'textfield') {
    $field['#size'] = 20;
  }

  if ($options) {
    $field['#options'] = $options;
  }
  if ($states) {
    $field['#states'] = $states;
  }
  return $field;
}

function alumni_dashboard_webform_submission_insert($node, $submission) {
  //FIXME UPDATE THIS ONCE DB'S PULLED DOWN FROM LIVE
  //the webform node is different on stage and live
  if ($node->nid == 34728 && $node->nid == 35179) {
    $contact_id = alumni_dashboard_get_logged_in_contact();
    $commune = $submission->data[9][0];
    $phone = $submission->data[10][0];
    $email = $submission->data[11][0];
    
    $commune = $commune ? $commune : '';
    
    $result = civicrm_api3('Address', 'get',
			   array(
				 'sequential' => 1,
				 'contact_id' => $contact_id,
				 'is_primary' => 1,
				 ));
    if ($result && isset($result['values']) && $result['values']) {
      $address_id = $result['values'][0]['id'];
      $params = array('sequential' => 1,
		      'id' => $address_id,
		      'contact_id' => $contact_id,
		      'custom_45' => $commune,);
      $result = civicrm_api3('Address', 'create', $params);
    }
    
    if (module_exists('email_notifications')) {
      $address = $result['values'][0];
      $alumni_name =
	db_query("SELECT display_name from civicrm_contact where id=$contact_id")
	->fetchField();
      
      global $base_url;
      $alumni_link = $base_url . "/civicrm/contact/view?cid=" . $contact_id;
      
      $country =
	db_query("select name from civicrm_country where id = " . $address['country_id'])
	->fetchField();
      $state =
	db_query("select name from civicrm_state_province where id = " .
		 $address['state_province_id'])
	->fetchField();
      
      $data = array('street' => $address['street_address'],
		    'street2' => $address['supplemental_address_1'],
		    'city' => $address['city'],
		    'state' => $state,
		    'country' => $country,
		    'code' => $address['postal_code'],
		    'phone' => $phone,
		    'email' => $email,
		    'commune' => $commune,
		    'alumni_link' => $alumni_link,
		    'alumni_name' => $alumni_name, 
		    'date' => date('d M Y'));
      
      
      email_notifications_send('alumni_address', $data);
    }
  }
  //FIXME UPDATE THIS ONCE DB'S PULLED DOWN FROM LIVE
  //different node nids and field keys on testing sites and live
  else if (($node->nid == 34727 || $node->nid == 35180) &&
	   module_exists('email_notifications')) {
    if ($node->nid == 35180) {
      $status_key = 3;
      $look_key = 4;
    }
    else {
      $status_key = 5;
      $look_key = 6;
    }
    
    $contact_id = alumni_dashboard_get_logged_in_contact();
    $alumni_name =
      db_query("SELECT display_name from civicrm_contact where id=$contact_id")
      ->fetchField();
    
    global $base_url;
    $alumni_link = $base_url . "/civicrm/contact/view?cid=" . $contact_id;
    
    //FIXME FIND OUT A WAY NOT TO HARD CODE
    $status_option_group_id =
      db_query("select option_group_id from civicrm_custom_field where id= 128")
      ->fetchField();

    $options = alumni_dashboard_civicrm_get_options($status_option_group_id, $value);
    $statuses = '';
    $separator = '';
    foreach($submission->data[$status_key] as $value) {
      $statuses .= $separator . $options[$value];
      $separator = '' ? ', ' : ', ';
    }

    $look_option_group_id =
      db_query("select option_group_id from civicrm_custom_field where id= 129")
      ->fetchField();

    $options = alumni_dashboard_civicrm_get_options($look_option_group_id);
    
    $looks = '';
    $separator = '';
    foreach($submission->data[$look_key] as $value) {
      $looks .= $separator . $options[$value];
      $separator = '' ? ', ' : ', ';
    }

    $data = array(
		  'status' => $statuses,
		  'looks' => $looks,
		  'alumni_link' => $alumni_link,
		  'alumni_name' => $alumni_name, 
		  'date' => date('d M Y'));

    email_notifications_send('alumni_status', $data);
  }
}
function alumni_dashboard_civicrm_get_options($gid) {
  $options = array();
  $results = civicrm_api3("OptionValue","get",
			  array ('sequential' =>'1',
				 'option_group_id' => $gid));
  if ($results && isset($results['values'])) {
    foreach ($results['values'] as $result) {
      $label = $result['label'];
      $value = $result['value']; 
      $options[$value] = $label;
    }
  }
  
  return $options;

}




function alumni_dashboard_civicrm_post($op, $object_name, $object_id,
				       &$object_ref) {
 
				      
  if ($object_name == 'Individual') {
    alumni_dashboard_update_employer_relationships($object_id, $object_ref);
// dsm($object_ref);
  }
}

function alumni_dashboard_civicrm_preProcess($form_name, &$form) {
    dsm($form_name);
if ($form->_flagSubmitted) {
    
  if ($form_name == 'CRM_Contact_Form_CustomData') {
 //   alumni_dashboard_update_employer_relationships($form->_entityId);
// only act if this is the work history field group 
    if ($form->_groupID == "26") {    
  //    dsm($form);
      //pull out the values that were submitted 
       $fields_to_set = array_filter($form->_submitValues, function($k){
         return preg_match('#custom_\d#', $k);
         }, ARRAY_FILTER_USE_KEY);   
//      dsm($fields_to_set);
  
       $relationshipID = array_filter($fields_to_set, function($k){
         return preg_match('#custom_143_\d#', $k);
       $relationshipID = array_values($relationshipID);
         }, ARRAY_FILTER_USE_KEY);
       $relationshipKey=key($relationshipID);
       $relationshipID =reset($relationshipID);
       $employerID = array_filter($fields_to_set, function($k){
         return preg_match('#custom_85_\d#', $k);
         }, ARRAY_FILTER_USE_KEY);
       $employerKey=key($employerID);  
       $employerID =reset($employerID);
       
       $jobTitle = array_filter($fields_to_set, function($k){
         return preg_match('#custom_86_\d#', $k);
         }, ARRAY_FILTER_USE_KEY);
       $jobTitleKey=key($jobTitle);  
       $jobTitle =reset($jobTitle);
       
       $jobStart = array_filter($fields_to_set, function($k){
         return preg_match('#custom_87_\d#', $k);
         }, ARRAY_FILTER_USE_KEY);
       $jobStartKey=key($jobStart);           
       $jobStart =reset($jobStart);
       if (empty($jobStart)) {
          $jobStart = "";
 
          }
       $jobEnd = array_filter($fields_to_set, function($k){
         return preg_match('#custom_88_\d#', $k);
         }, ARRAY_FILTER_USE_KEY);
       $jobEndKey=key($jobEnd);  
       $jobEnd =reset($jobEnd);
              if (empty($jobEnd)) {
          $jobEnd = "";
          }
//                   dsm($jobEnd,"end");
       
      $currentcontact = $form->_entityId;
//$employerstringx= reset($fields_to_set);
//$employerstring =array_slice($employerID, 0, 1);

//dsm($employerstring);  
//dsm($jobStart);
//dsm($jobEnd);

$isactive =1;

        //  $form->_submitValues[$relationshipKey] = "1234";
//          $form->_elements[13]->_attributes['value'] = "1234";
          //dsm($form);
 //         return $form;
       if (!empty($relationshipID)) {
//       dsm("update");
//      set relationship values 

$params=array(
           "id"=> $relationshipID,
           'contact_id_a' => $currentcontact,
           'contact_id_b' => $employerID,
           'relationship_type_id' => 5, 
           'is_active' => $isactive,
           'description' => $jobTitle,
           );
           
           if (!empty($jobStart)) {
           $params['start_date'] = $jobStart;
           }
           if (!empty($jobEnd)) {
           $params['end_date'] = $jobEnd;
           }                      
         $result = civicrm_api3('Relationship', 'create', $params);

       }else{
  //     dsm("new");
// set relationship values and bring back the id 
// set the field to the right id 

         $params=array(
           'contact_id_a' => $currentcontact,
           'contact_id_b' => $employerID,
           'relationship_type_id' => 5, 
           'is_active' => $isactive,
           'description' => $jobTitle,
           );
           
           if (!empty($jobStart)) {
           $params['start_date'] = $jobStart;
           }
           if (!empty($jobEnd)) {
           $params['end_date'] = $jobEnd;
           }                      
         $result = civicrm_api3('Relationship', 'create', $params);
        
         $form->_submitValues[$relationshipKey] = $result['id'];
//    dsm($result['id']);   
//         
//dsm("rel created");
//          $form->_submitValues[$relationshipKey] = "1234";
//          $form->_elements[13]['_attributes']['value'] = "1234";
       }                     
    }
  }
}
}

function alumni_dashboard_update_employer_relationship_tab_add($contact_id,$values) {

// update the 

}

function alumni_dashboard_update_employer_relationship_tab_edit($contact_id,$values) {


}

function alumni_dashboard_update_employer_relationship_tab_delete($contact_id) {


}

function alumni_dashboard_update_employer_relationships($contact_id,
							$contact = NULL){
  if (!$contact_id) {
    //do nothing
    return;
  }
  //fetch employment history, store by employer to get overall start&end
  $employee_fields = array('Employer' => 85,
			   'Job Title' => 86,
			   'Start' => 87,
			   'End' => 88,
			   'Salary' => 90,
			   'Currency' => 91);
  $employment_field_data = array();

  $result = civicrm_api3('CustomValue', 'get', array(
						     'sequential' => 1,
						     'entity_id' =>
						     $contact_id,
						     ));
  if ($result && isset($result['values']) && $result['values']) {
    foreach ($result['values'] as $key => $field_values) {
      if (in_array($field_values['id'], $employee_fields)) {
	foreach ($field_values as $index => $value) {
	  if (is_int($index)) {
	    $employment_field_data[$index] =
	      isset($employment_field_data[$index]) ?
	      $employment_field_data[$index] : array();
	    
	    $employment_field_data[$index][$field_values['id']] =
	      $value;
	  }
	}
      }
    }
  }
  
  $employer_data = array();
  foreach ($employment_field_data as $fieldset_id => $fields) {
    $employer_id = $fields[$employee_fields['Employer']];
    $employer_data[$employer_id] = isset($employer_data[$employer_id]) ?
      $employer_data[$employer_id] : array();

    $cached_start = isset($employer_data[$employer_id]['start']) ?
      strtotime($employer_data[$employer_id]['start']) : NULL;
    
    $cached_end = isset($employer_data[$employer_id]['end']) ?
      $employer_data[$employer_id]['end'] : NULL;

    $cached_end = ($cached_end != 'none') ? strtotime($cached_end) : 'none';
    
    $start = isset($fields[$employee_fields['Start']]) ?
      strtotime($fields[$employee_fields['Start']]) : NULL;
    $end = isset($fields[$employee_fields['End']]) ?
      strtotime($fields[$employee_fields['End']]) : NULL;

    if ((!$cached_start && $start) ||
	($start && ($start < $cached_start))) {
      $employer_data[$employer_id]['start'] = date('Y-m-d H:i:s',$start);
    }
    
    if (!$end) {
      $employer_data[$employer_id]['end'] = 'none';
    }
    else if ($cached_end == 'none') {
      //do nothing, if we have an open ending, we will keep it open
    }
    else if ((!$cached_end && $end) || ($end && ($end > $cached_end))) {
      $employer_data[$employer_id]['end'] = date('Y-m-d H:m:s',$end);
    }
  }

  foreach($employer_data as $employer_id => $dates)  {
    //look up each employer, is there a relationship with this contact
    $result = civicrm_api3('Relationship', 'get',
			   array(
				 'sequential' => 1,
				 'contact_id_b' => $employer_id,
				 'contact_id_a' => $contact_id,
				 'relationship_type_id' => 5,
				 ));
    
    if ($result && isset($result['values']) && $result['values']) {
      $relationship = $result['values'][0];
      $start = isset($relationship['start_date']) ? $relationship['start_date']
	: '';
      
      $end = isset($relationship['end_date']) ?	$relationship['end_date'] : '';
      
      //if relationship, compare relationship end date with latest end date
      // (or null end dat if it exists) for this employer

      $should_update = FALSE;
      //compare start and end times, if they differ delete relationship
      if (strtotime($start) != strtotime($dates['start'])) {
	$relationship['start_date'] = $dates['start'];
	$should_update = TRUE;
      }

      if ($end && $dates['end'] == 'none'){
	$relationship['end_date'] = '';
	$should_update = TRUE;
      }
      else if ($dates['end'] &&
	       (strtotime($date) != strtotime($dates['end']))) {
	$relationship['end_date'] = $dates['end'];
	$should_update = TRUE;
      }

      if (!$should_update) {
	//if they don't differ continue
	continue;
      }
      else {
	$result = civicrm_api3('Relationship', 'create', $relationship);
      }
    }
    else {
      $parameters =
	array(
	      'sequential' => 1,
	      'contact_id_a' => $contact_id,
	      'contact_id_b' => $employer_id,
	      'relationship_type_id' => 5,
	      'start_date' => $dates['start'],
	      );
      if ($dates['end'] && $dates['end'] != 'none') {
	$parameters['end_date'] = $dates['end'];
      }
      //if not create a new one
      $rel_result = civicrm_api3('Relationship', 'create', $parameters);

      //if no relationship, create one
    }
  }

}

function alumni_dashboard_get_logged_in_contact() {
  //FETCH CONTACT
  global $user;
  $contact_id = NULL;
  
  civicrm_initialize();
 
  $result = civicrm_api3('UFMatch', 'get', array(
						 'sequential' => 1,
						 'uf_id' => $user->uid,
						 ));

  if ($result && isset($result['values']) && $result['values']) {
    $contact_id = $result['values'][0]['contact_id'];
  }

  return $contact_id;
}

function alumni_dashboard_contact_info_header() {
  $ret = '';
  $contact_id = alumni_dashboard_get_logged_in_contact();

  civicrm_initialize();
  
  $result = civicrm_api3('Contact', 'get', array(
						 'sequential' => 1,
						 'id' => $contact_id,
						 ));

  if ($result && isset($result['values']) && $result['values']) {
    $contact = $result['values'][0];

    $ret .= t("Name:").' '.$contact['display_name']."<br/>";

    $result = civicrm_api3('Relationship', 'get',
			   array(
				 'sequential' => 1,
				 'contact_id_a' => 1,
				 'contact_id_b' => $contact_id,
				 'relationship_type_id' => 50,
				 ));

    if ($result && isset($result['values']) && $result['values']) {
      foreach ($result['values'] as $k => $relationship) {
	$start = isset($relationship['start_date']) ?
	  date('M Y', strtotime($relationship['start_date'])) : '';
	
	
	$end = isset($relationship['end_date']) ?
	  date('M Y', strtotime($relationship['end_date'])) : '';

	$help = civicrm_api3('Contact', 'get', array(
						    'sequential' => 1,
						    'id' => $relationship['contact_id_a'],
						    ));
	
	if ($help && isset($help['values']) && $help['values']) {
	  
	  $help_name = $help['values'][0]['display_name'];
	  $start = $start ? "From $start" : "";
	  $end = $end ? "- $end" : "";
	  $ret .= "Enrolled at <strong>$help_name</strong> $start $end </br>";
	}
      }
    }

    
    $result = civicrm_api3('Relationship', 'get',
			   array(
				 'sequential' => 1,
				 'contact_id_a' => $contact_id,
				 'relationship_type_id' => 54,
				 ));
    
    if ($result && isset($result['values']) && $result['values']) {
      foreach ($result['values'] as $k => $relationship) {
	$uni = civicrm_api3('Contact', 'get', array(
						    'sequential' => 1,
						    'id' => $relationship['contact_id_b'],
						    ));
	
	$start = isset($relationship['start_date']) ?
	  date('M Y', strtotime($relationship['start_date'])) : '';
	
	
	$end = isset($relationship['end_date']) ?
	  date('M Y', strtotime($relationship['end_date'])) : '';
      
	if ($uni && isset($uni['values']) && $uni['values']) {
	  $uni_name = $uni['values'][0]['display_name'];
	  $start = $start ? "From $start" : "";
	  $end = $end ? "- $end" : "";
	  $ret .= "Enrolled at <strong>$uni_name</strong> $start $end </br>";
	}

      }
    }
  }
  return $ret."<br/>";
}

function alumni_dashboard_email_notifications_types_alter(&$types) {
  $types[] = 'alumni_employment';
  $types[] = 'alumni_milestone';
  $types[] = 'alumni_status';
  $types[] = 'alumni_address';
}