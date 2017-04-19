<?php


/**
 *  This is for the available beds computed field on the Dorm Room content 
 *  type (machine name = dorm-bed
 */
function computed_field_field_cmptd_available_beds_compute(&$entity_field, $entity_type, $entity, $field, $instance, $langcode, $items) {

  $available_beds = dorm_managment_available_beds($entity);
  return $available_beds;
}

function dorm_managment_available_beds($entity) {
  $capacity =
    dorm_management_get_entity_single_value_field($entity,
						  'field_dorm_room_capacity',
						  'value');

  $number_of_occupants = 
    count($entity->field_dorm_room_students[LANGUAGE_NONE]);

  $number_of_occupants = 0;
  foreach ($entity->field_dorm_room_students[LANGUAGE_NONE] as $k=>$v) {
    $assignment = entity_load('field_collection_item', array($v['value']));
    $assignment = $assignment ? array_pop($assignment) : '';
      
    if ($assignment) {
      $field_name = 'field_dorm_studentcontact';
      $student_id =
	dorm_management_get_entity_single_value_field($assignment,
						      $field_name,
						      'contact_id');
      
      if ($student_id) {
	$number_of_occupants++;
      }
    }
  }

  $available_beds = $capacity - $number_of_occupants;
  $entity_field[0]['value'] = $available_beds;
  return $available_beds;
}

function computed_field_field_dorm_student_display_name_compute(&$entity_field, $entity_type, $entity, $field, $instance, $langcode, $items){
//  dsm($entity->field_dorm_students_student);
  $uid_of_student=$entity->field_dorm_students_student['und'][0]['target_id'];
  civicrm_initialize( );
  $cidtouse = CRM_Core_BAO_UFMatch::getContactID($uid_of_student);
  $params = array(
  'contact_id' => $cidtouse,
  'version' => 3,
  );

// Get Contact details for the user.
  $contact = civicrm_api( 'contact','get',$params );
  
  dsm($contact['values'][$cidtouse]['display_name']);
  $entity_field[0]['value'] =$contact['values'][$cidtouse]['display_name'];
  return $contact['values'][$cidtouse]['display_name'];
}
