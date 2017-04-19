<?php 

function uhelp_dev_secondary_schools_contact_name($row, $position) {

  $contact_array = uhelp_dev_secondary_schools_contact_array($row->id);
  return $contact_array[$position]['display_name'];
}

function uhelp_dev_secondary_schools_contact_email($row, $position) {

  $contact_array = uhelp_dev_secondary_schools_contact_array($row->id);
  return $contact_array[$position]['email'];
}

function uhelp_dev_secondary_schools_contact_phone($row, $position) {

  $contact_array = uhelp_dev_secondary_schools_contact_array($row->id);
  return $contact_array[$position]['phone'];
}

function uhelp_dev_secondary_schools_contact_job_title($row, $position) {

  $contact_array = uhelp_dev_secondary_schools_contact_array($row->id);
    return $contact_array[$position]['job_title'];
}

function uhelp_dev_secondary_schools_contact_array($school_cid) {
  $var_name = "uhelp_dev_secondary_school_array_" .$school_cid;

  global $$var_name;

  if (isset($$var_name)) {
    return $$var_name;
  }
  $$var_name = array();

  $result = civicrm_api3('Relationship', 'get', array(
						     'sequential' => 1,
						     'contact_id_b' => 
						     $school_cid,
						      ));

  $results = (!$result['is_error'] && isset($result['values']) && 
	      isset($result['values'][0])) ?
    $result['values'] : array();

  $all_contacts = array();
  foreach($results as $position=>$relationship) {
    $contact_id = $relationship['contact_id_a'];
    $result2 = civicrm_api3('Contact', 'get', array(
						    'sequential' => 1,
						    'id' => $contact_id,
						    ));

    $result2s = (!$result2['is_error'] && isset($result2['values']) && 
		isset($result2['values'][0])) ?
      $result2['values'][0] : array();

    $contact_array = array('contact_id'=>$result2s['contact_id'],
				 'display_name'=>$result2s['display_name'],
				 'email'=>$result2s['email'],
				 'phone'=>$result2s['phone'],
				 'job_title'=>$result2s['job_title'],
				 );

    $all_contacts[] = $contact_array;
    
  }
  $$var_name = $all_contacts;

  return $$var_name;
}