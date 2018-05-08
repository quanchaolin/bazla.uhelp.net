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

//function that calculate number of interns and employers a prospecive employer has
function uhelp_dev_count_interns_and_employees($cid,$array_of_relationship_ids){
  
  $count = array();
  $count[0] = 0;
//for each id of relationship
  foreach ($array_of_relationship_ids as $pos=>$value) {
        civicrm_initialize();
        $result = civicrm_api3('Relationship', 'get', array(
          'sequential' => 1,
          'contact_id_b' => $cid,
          'relationship_type_id' => $value,
        )); 

        //if contact has relationship
        if($result['count'] > 0){
                //initialized result count to zero for return statement
                $count[0] = 0;
                 
              
               foreach ($result['values'] as $pos=>$value1){
                //id of contact to verify
               $contact_id_a =  $result['values'][$pos]['contact_id_a'];
              // dpm($contact_id_a);
               //check if id of relationship type was  intern or  employer 
               if( $value == 15){
                   //get its contacts which are interns
                   $result2 = civicrm_api3('Contact', 'get', array(
                    'sequential' => 1,
                    'contact_sub_type' => array("Former_student_DNF_", "Alumni", "Student"),
                    'id' => $contact_id_a,
                  ));
              }else if( $value == 5){
                  //get its contacts which are employees
                   $result2 = civicrm_api3('Contact', 'get', array(
                    'sequential' => 1,
                    'id' => $contact_id_a,
                    'contact_sub_type' => "Alumni", 
                  ));
              }
              // dpm("for relationship ".$pos ."  and result".$result2['count']);
               //if($result2['count'] > 0){
               $count[0] = $count[0]+$result2['count'];
             //}
             //  dpm("Alumni check for id :".$contact_id_a."  2nd api call values'count is: ".$result2['count']);
             // dpm("count is : ".$count[0]);
            }  
      }
     // dpm("employees : ",$count[0]);
      return $count[0];
  //$count[0] = $result['count'] ;
  //dpm("values: ",$result['values']);
        //dpm("count intens", $count[0]);


}

}