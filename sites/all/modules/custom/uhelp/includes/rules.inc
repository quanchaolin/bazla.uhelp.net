<?php 

// rules calls this funciton and passed the node of the application
// and the node of the associated internship/job

function uhelp_rules_create_case($application,$internship) {
    civicrm_initialize( );
    //require_once 'CRM/Core/Config.php';
    //$config =& CRM_Core_Config::singleton( );
//dsm($internship);
    //require_once 'api/v2/Case.php';

// get start and end date of internship

$start_date = uhelp_get_entity_single_value_field($internship, 
    'field_internship_dates', 'value');

$end_date = uhelp_get_entity_single_value_field($internship, 
    'field_internship_dates', 'value2');

//dsm($start_date);
//dsm($end_date);

// get the cid of the organization
$org = uhelp_get_entity_single_value_field($internship, 
    'field_internship_org', 'contact_id');

// get the info from the field collection (pay period,etc.)

$info_entity_id = uhelp_get_entity_single_value_field($internship, 
    'field_internship_info', 'value');

//$info_entity_data = entity_load('field_internship_info', array($info_entity_id));
$info_entity_data = field_collection_item_load($info_entity_id, $reset = FALSE);
//dsm($info_entity_data);

$pay_period = $info_entity_data->field_int_compensation_period['und'][0]['value'];

//dsm($pay_period);

    $uid = uhelp_get_entity_single_value_field($application, 
    'field_app_applicant_entity', 'target_id');

// get the cid of the student 
    $result = civicrm_api3('UFMatch', 'get', array(
        'sequential' => 1,
        'id' => $uid,
    ));

    if ($result && isset($result['values']) && $result['values']) {
        $student_cid = $result['values'][0]['contact_id'];
    }

    //get the cid of the advisor from the drupal variable table, will default
    //to 183 which is Fedorah
    $advisor_cid = variable_get('uhelp_default_case_manager_contact_id', 183); 

    if ($student_cid) {
        // create new case
        $params = array(  
            'sequential' => 1,
            'case_type_id'  => '7',
//            'start_date'    => date('Y-m-d'),  
            'start_date'  => $start_date,
            'status_id'      => 1, // ongoing
            'contact_id' => $student_cid,
            'creator_id'      => 183, // the case manager
            'subject' => 'Internship',
        );
        
       $result = civicrm_api3('Case', 'create', $params);
        dsm($result, 'case');
        dsm($result['id']);
        
        $case_created = $result['id'];
        
        //add relationships
        
        $createcase = CRM_Case_BAO_Case::createCaseRoleActivity($case_created, array(15), 6676, 6);
dsm($createcase);
// now we have the case created so we create the default set of activities

//set the end date of the internship 


    $result = civicrm_api3('Activity', 'create', array(
      'sequential' => 1,
      'activity_type_id' => 74,
      'case_id' => $case_created,
      'status_id' => 1,
      'activity_date_time' => $end_date,
      'subject' => "End of Internship",
    ));



        
    }

    return;

//CRM/Contact/Form/Relationship.php:     
//CRM_Case_BAO_Case::createCaseRoleActivity($this->_caseId, $relationshipIds, $params['contact_check'], $this->_contactId);



/**
    // configure new case
    $params = array(  'case_id'          => $new_case['result'],
    'case_type'        => 'Christmas Case',
    'contact_id'      => 333, // the client
    'creator_id'      => 444, // the case manager
    'activity_subject'=> 'Jingle Bells',
    'location'        => 'The North Pole',
    'start_date'      => 20101225,
    'medium_id'        => '1', //"In Person"
    'duration'        => '',
    'details'          => '',1);
*/
}