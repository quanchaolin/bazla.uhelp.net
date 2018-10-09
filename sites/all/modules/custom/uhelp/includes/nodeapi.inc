<?php

function uhelp_node_validate($node, $form, &$form_state) {

  if ($node->type=='class_session_time') {
  
    $start_date_field = $node->field_class_schedule['und'][0]['value'];
    $end_date_field = $node->field_class_schedule['und'][0]['value2'];

    $start_date_object = 
new DateTime($start_date_field, 
         new DateTimeZone('UTC'));
    $start_date_object->setTimeZone(new DateTimeZone('America/New_York'));
    
    $end_date_object = 
new DateTime($end_date_field, 
         new DateTimeZone('UTC'));
    $end_date_object->setTimeZone(new DateTimeZone('America/New_York'));  

    $start_datetime = $start_date_object->format('m/d/Y H:ia');    
    $start_date = $start_date_object->format('m/d/Y');
    $start_time = $start_date_object->format('H:ia');
    $start_hour = $start_date_object->format('H');
    $end_datetime = $end_date_object->format('m/d/Y H:ia');    
    $end_date = $end_date_object->format('m/d/Y');
    $end_time = $end_date_object->format('H:ia');  
    $end_hour = $end_date_object->format('H');       

    if ($start_datetime == $end_datetime) {
      form_set_error(UHELP_SCHEDULE_CHECK1,
		    t("The start date and time can not match the end date and time"));
    }

    if ($start_date != $end_date) {
      form_set_error(UHELP_SCHEDULE_CHECK2,
        t("The start date of the first session must match the end date"));
    }

    // built-in validation already checks for this but left in case this changes
    if ($end_datetime == $start_datetime) {
      form_set_error(UHELP_SCHEDULE_CHECK3,
        t("The end time of the first session must be after the start time of the first session"));
    }

    if ($start_time < 7) {
      form_set_error("field_class_schedule_starttime",
        t("Please use 24 hour time. Class sessions can not start before 07:00"));
    }

    if ($end_time > 20) {
      form_set_error("field_class_schedule_endtime",
        t("Please use 24 hour time. Class sessions can not end after 20:00"));
    }

    if (!isset ($node->field_class_schedule['und'][0]['rrule'])) {
      form_set_error("field_class_schedule_repeat",
                     t("class schedules must have repeat rules set"));
    }

  }

  else if($node->type=='help_class' || $node->type=='university_class' || $node->type=='service_project') {

    $button = $form_state['clicked_button']['#value'];
    if ($button == 'Delete') {

      $sql = 
	"SELECT count(1)
         FROM field_data_field_eval_class eval
         INNER JOIN field_data_field_eval_grade grade
         ON grade.entity_id = eval.entity_id
         WHERE eval.field_eval_class_target_id = ".$node->nid; 

      $result = db_query($sql)->fetchField();

      if ($result > 0) {
	form_set_error("",
		       t("Sorry, we can't delete the class. There are already grades set for this class so this class can not be deleted without deleting the grades first."));

      }
    }
  }


}




//uhelp_recruitment_node is called from two rules
//one fires when a new node of type recruitment_event is saved
//the other when it is updated

function uhelp_recruitment_node($node){

    // dsm($node);

//get contact id of the school 
  $school_cid = $node->field_recruitment_school['und'][0]['contact_id'];

  //dsm($school_cid);

//get team leader cid 

//get array of team members' cids 
  $recruiters= $node->field_r_recruiter_names['und'];
//dsm($recruiters);
// get cid of team leader
  $team_leader = $node->field_r_team_leader['und'][0]['contact_id'];

//dsm($recruiters);
//dsm($team_leader);

// get date of the visit 
  $visit_date = $node->field_recruitment_date_of_visit['und'][0]['value'];

//dsm($visit_date);
  civicrm_initialize();
    //$result = civicrm_api3('Contact', 'get', array(
    //'sequential' => 1,
    //'id' => $school_cid,
    //));
    
    
//get the details of the school's contact record     
  $params = array(
  'version' => 3,
  'sequential' => 1,
  'id' => $school_cid,
  );
  $school_contact_data = civicrm_api('Contact', 'get', $params); 
    
    
    //dsm($school_contact_data);
    
 //from the address of the school, determine the Department
 //for the recruitment team relationships   
  $department = $school_contact_data['values'][0]['state_province_name'];
 
  //dsm($department);
 // this is the set of cids for recruitment relationships
 
  $recruitement_departments = array(
    "AR" => "513",
    "CE" => "514",
    "Data Entry"  => "523",
    "A" => "515",
    "NI" => "516",
    "ND" => "517",
    "NE" => "518",
    "NO" => "519",
    "OU" => "520",
    "SD" => "522",
    "SE" => "521",
    );    

// set cid of department
  $school_dpt_cid = $recruitement_departments[$department];

if (empty($school_dpt_cid)) {

dsm("NOTICE: this school's address is not complete (no Department) so relationships for recruiters can not be set. Please update the school's record and re-save this node");
}
//dsm($school_dpt_cid);

  $visit_datetime = strtotime($visit_date);

// look to see if this student already has this relationship 
// set for this year 
// if they have, set $leader_set to no 

  $leader_set = "yes";
//dsm($leader_set);
  $params_leader_check = array ( 
    'version' => 3,
    'sequential' => 1,
    'relationship_type_id' => "40",
    'contact_id_a' => $team_leader,
    'contact_id_b' => $school_dpt_cid,
  );
//dsm($params_leader_check);
  $leader_check_result = civicrm_api('Relationship', 'get', $params_leader_check);
//  dsm($leader_check_result);
  if ($leader_check_result['count'] >=1){
    $relationship_new_year = date('Y', strtotime($visit_date)); 
    foreach ($leader_check_result['values'] as $relationship) {
      $relationship_existing_year = date('Y', strtotime($relationship['start_date']));
      if ($relationship_existing_year == $relationship_new_year) {
        $leader_set = "no";
      }
    }
  } 
//  dsm($leader_set);
       
// set relationship for team leader
  if ($leader_set == "yes"){
    $params_leader = array(
      'version' => 3,
      'sequential' => 1,
      'relationship_type_id' => "40",  
      'start_date' =>  $visit_date,
      'end_date' => $visit_date,
      "is_active" => "0",
//     'id' => 39,
      'contact_id_a' => $team_leader,
      'contact_id_b' => $school_dpt_cid,
      );
    $result = civicrm_api('Relationship', 'create', $params_leader);
  }


//dsm($school_dpt_cid);
/*
  $member_set = "yes";
  $params_member_check = array ( 
    'version' => 3,
    'sequential' => 1,
    'relationship_type_id' => "39",
    'contact_id_a' => $recruiter_cid,
    'contact_id_b' => $school_dpt_cid,
  );
  $member_check_result = civicrm_api('Relationship', 'get', $params_member_check);
dsm($member_check_result);
*/
// set relationships for team members 

//if (!empty($node->field_r_recruiter_names['und'])){

  foreach ($recruiters as $recruiter) {
// look to see if this student already has this relationship 
// set for this year 
// if they have, set $member_set to no 

    $member_set = "yes";
//dsm($member_set);
      $recruiter_cid = $recruiter['contact_id'];
    $params_member_check = array ( 
      'version' => 3,
      'sequential' => 1,
      'relationship_type_id' => "39",
      'contact_id_a' => $recruiter_cid,
      'contact_id_b' => $school_dpt_cid,
    );
    $member_check_result = civicrm_api('Relationship', 'get', $params_member_check);

//dsm($params_member_check);
    if ($member_check_result['count'] >=1){
      $relationship_new_year = date('Y', strtotime($visit_date)); 
      foreach ($member_check_result['values'] as $relationship) {
        $relationship_existing_year = date('Y', strtotime($relationship['start_date']));
        if ($relationship_existing_year == $relationship_new_year) {
          $member_set = "no";
      }
    }
  } 
    // dsm($member_set);
    if ($member_set == "yes" ){  
      $recruiter_cid = $recruiter['contact_id'];
    //dsm($recruiter_cid);
    //dsm($school_dpt_cid);
      $params = array(
        'version' => 3,
        'sequential' => 1,
        'relationship_type_id' => "39",  
        'start_date' =>  $visit_date,
        'end_date' => $visit_date,
	"is_active" => "0",
//     'id' => 39,
        'contact_id_a' => $recruiter_cid,
        'contact_id_b' => $school_dpt_cid,
        );
      $result = civicrm_api('Relationship', 'create', $params);
    }
//dsm($result);
  }
  
// set data entry relationship for node author 
// look to see if this student already has this relationship 
// set for this year 
// if they have, set $member_set to no 

    $data_entry_credit_set = "yes";

// get cid from node author uid 
  $author_cid = CRM_Core_BAO_UFMatch::getContactID($node->uid);

    $params_data_check = array ( 
      'version' => 3,
      'sequential' => 1,
      'relationship_type_id' => "39",
      'contact_id_a' => $author_cid,
      'contact_id_b' => 523,
    );
    $data_entry_check_result = civicrm_api('Relationship', 'get', $params_data_check);
    if ($data_entry_check_result['count'] >=1){
      $relationship_new_year = date('Y', strtotime($visit_date)); 
      foreach ($data_entry_check_result['values'] as $relationship) {
        $relationship_existing_year = date('Y', strtotime($relationship['start_date']));
        if ($relationship_existing_year == $relationship_new_year) {
          $data_entry_credit_set = "no";
        }
      }
    } 
    
    if ($data_entry_credit_set == "yes" ){  
//      $recruiter_cid = $recruiter['contact_id'];
    //dsm($recruiter_cid);
    //dsm($school_dpt_cid);
      $params = array(
        'version' => 3,
        'sequential' => 1,
        'relationship_type_id' => "39",  
        'start_date' =>  $visit_date,
        'end_date' => $visit_date,
	"is_active" => "0",
//     'id' => 39,
        'contact_id_a' => $author_cid,
        'contact_id_b' => 523,
        );
      $result = civicrm_api('Relationship', 'create', $params);
    }

  
//}
// looks to see if activity already exists
//TODO: now that the activity id is saved into the nodes
//change this check to look for the activity of that id 
//if it exists, check for changes and update the activity
//instead of just ignoring 
 $result_activity_check['count'] =0;
if (isset($node->field_r_civi_activity_id['und'][0]['value'])){
   $result_activity_check['count'] =1;
   }
/*
dsm($school_cid);
  $params_activity_check="";
  $params_activity_check = array(
    'version' => 3,
    'sequential' => 1,
    'activity_type_id' => 50,
    'activity_date_time' => $visit_date,
    'source_contact_id' => $school_cid,
    );

dsm($params_activity_check);
  $result_activity_check = civicrm_api('activity', 'get', $params_activity_check);
   dsm($result_activity_check);
//   
//   $params = array(
//   'version' => 3,
//   'sequential' => 1,
//   'activity_type_id' => 50,
//    'activity_date_time'=> "2015-01-14 00:00:00",
// 
// );
  
  //dsm($result_activity_check);
  
// set activity only if result count is 0
*/


 
  if ($result_activity_check['count'] ==0) { 
  $recruitment_node_href = '<a href="/node/'.$node->nid.'">click here for details</a>';
  $visit_year = date('Y', strtotime($visit_date)); 
  global $user;
     $cid = CRM_Core_BAO_UFMatch::getContactID($user->uid);
  //set activity on school 
    $params2 = array(
      'version' => 3,
      'sequential' => 1,
      'source_contact_id' => $school_cid,
      'activity_type_id' => 71,
      'activity_date_time' => $visit_date,
      'activity_details' => $recruitment_node_href,
      
      'activity_subject' => 'recruitment visit '.$visit_year,
    );

    $result_activity = civicrm_api('activity', 'create', $params2);
    
//    dsm($node);
//    node_save($node);


    node_object_prepare($node);
    $node->language = LANGUAGE_NONE;   
    
    ///civicrm/activity?atype=71&action=view&reset=1&id=1593&cid=532&context=activity&searchContext=activity
    $activitylink= "<a href='/civicrm/activity?atype=71&action=view&reset=1&id=".$result_activity['values'][0]['id']."&cid=".$school_cid."&context=activity&searchContext=activity'>activity detail link</a>";
//    $node->field_r_civi_activity_id['und'][0]['value'] = $result_activity['values'][0]['id'];
    $node->field_r_civi_activity_id['und'][0]['value'] = $activitylink;
    $node->field_r_civi_activity_id['und'][0]['format']  = 'filtered_html';
    $node->field_r_activity_id_number['und'][0]['value'] = $result_activity['values'][0]['id'];
    $node = node_submit($node); 
    node_save($node);

//dsm($node->nid);
  $recruitment_node_href = '<a href="/node/'.$node->nid.'">click here for details</a>';
    $params2 = array(
      'version' => 3,
      'sequential' => 1,
      'id' => $result_activity['values'][0]['id'],
//      'source_contact_id' => $school_cid,
//      'activity_type_id' => 71,
//      'activity_date_time' => $visit_date,
      'activity_details' => $recruitment_node_href,
      
//      'activity_subject' => 'recruitment visit '.$visit_year,
    );

    $result_activity = civicrm_api('activity', 'create', $params2);



//    $node->field_r_civi_activity_id['und'][0]['value'] = $result2['values'][0]['id'];                            
//    $node->field_r_civi_activity_id['und'][0]['value'] = $result2['id']; 
//    dsm($result_activity);
unset($school_cid);
//   return($node);


  }

}

function uhelp_recruitment_viewfield_argument($argument){

//dsm(arg(1));
$nid=arg(1);
//$thisnode = entity_load('node', array($nid));
$thisnode = node_load($nid);
//dsm($thisnode);
$cid_to_return = $thisnode->field_recruitment_school['und'][0]['contact_id'];
//return $argument->value;
//return "512";
//dsm($cid_to_return);
return $cid_to_return;
}