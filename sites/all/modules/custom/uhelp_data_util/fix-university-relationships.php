<?php 
//load spreadsheet into an array
 //   $filename = "help-rec-data-sample.csv";

//finds students with active relationships to a field of study
	
  civicrm_initialize();
  print "started";
    $result = civicrm_api3('Contact', 'get', array(
      'sequential' => 1,
      'contact_sub_type' => "Student",
      'options' => array(
        'limit' => 0,
      ),
    ));
//    print_r($result);
    $rownumber = 0;
 //   print "result above \n";
      foreach ($result['values'] as $student){

if ($rownumber < 2000){

//      foreach ($students as $student){
//print_r($student);      
      $student_cid = $student['contact_id'];
//    print_r("in the loop \n");  
//marches up the chain (dept/faculty) to find the university that field of study is in
    $result = civicrm_api3('Relationship', 'get', array(
      'sequential' => 1,
      'contact_id_a' => $student_cid,
      'relationship_type_id' => 51,
    ));
    print "relationship below \n";
print_r($result);    
    $field_of_study_cid = $result['values']['contact_id_b'];
    print $field_of_study_cid."\n";
    if ($result['count'] == 0){
    
        $result = civicrm_api3('Relationship', 'get', array(
      'sequential' => 1,
      'contact_id_a' => $student_cid,
      'relationship_type_id' => 25,
    ));
        print "relationship below \n";
print_r($result);  
        $field_of_study_cid = $result['values'][0]['contact_id_b'];
print "value above \n";
    }
    print_r("field of study". $field_of_study_cid."\n");
    $result = civicrm_api3('Relationship', 'get', array(
      'sequential' => 1,
      'contact_id_a' => $field_of_study_cid,
      'relationship_type_id' => 27,
    ));

    $department_cid = $result['values']['contact_id_b'];
    print($department_cid)."\n";
    $result = civicrm_api3('Relationship', 'get', array(
      'sequential' => 1,
      'contact_id_a' => $department_cid,
      'relationship_type_id' => 31,
    ));

    $faculty_cid = $result['values']['contact_id_b'];

    print $faculty_cid ."\n";

//adds new Is undergraduate student at relationship with the same start date as the existing field of study relationship





// create relationship between person and school 
/*
      $result4 = civicrm_api3('Relationship', 'create', array(
        'sequential' => 1,
        'contact_id_a' => $school_contact_id1,
        'contact_id_b' => $school_cid,
        'relationship_type_id' => 38,
      ));
*/
print "done";

$rownumber++;
print $rownumber."\n";
}
}
print "done";