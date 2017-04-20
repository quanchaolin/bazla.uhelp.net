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

function alumni_dashboard_civicrm_post($op, $object_name, $object_id,
				       &$object_ref) {
  if ($object_name == 'Individual') {
    alumni_dashboard_update_employer_relationships($object_id, $object_ref);
  }
}

function alumni_dashboard_civicrm_postProcess($form_name, &$form) {
  if ($form_name == 'CRM_Contact_Form_CustomData') {
    alumni_dashboard_update_employer_relationships($form->_entityId);
  }
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

