<?php

function dorm_management_entity_update($entity, $type){
  if ($type == 'field_collection_item') {
    dorm_management_update_room_availability($entity);
    dorm_management_update_relationship($entity, 'update');
  }
}
function dorm_management_entity_insert($entity, $type){
  if ($type == 'field_collection_item') {
    dorm_management_update_room_availability($entity);
    dorm_management_update_relationship($entity, 'insert');
  }
}
function dorm_management_entity_delete($entity, $type){
  if ($type == 'field_collection_item') {
    dorm_management_update_room_availability($entity);
    dorm_management_update_relationship($entity, 'delete');
  }
}


function dorm_management_entity_presave($entity, $type){
  $parent_field_name = isset($entity->field_name) ? $entity->field_name : '';
  if ($type == 'field_collection_item' &&
      $parent_field_name && $parent_field_name == 'field_dorm_room_students') {
    $contact_id =
      dorm_management_get_entity_single_value_field($entity->original,
						   'field_dorm_studentcontact',
						    'contact_id');
    if ($contact_id) {
      global $dorm_management_original_bed_occupier;
      $dorm_management_original_bed_occupier = $contact_id;
    }
 
  }
}

function dorm_management_update_room_availability($entity) {
  $sql =
    "SELECT entity_id 
     FROM field_data_field_dorm_room_students 
     WHERE field_dorm_room_students_value= ". $entity->item_id;

  $nid = db_query($sql)->fetchField();
  $room = node_load($nid);

  if (!$room) {
    $nid = arg(1);
    $room = node_load($nid);
  }

  $room->field_cmptd_available_beds[LANGUAGE_NONE][0]['value'] =
    dorm_managment_available_beds($room);
  field_attach_update('node', $room);      
  entity_get_controller('node')->resetCache(array($node->nid));
}
function dorm_management_update_relationship($entity, $op) {
  $contact = NULL;
  $parent_field_name = isset($entity->field_name) ? $entity->field_name : '';
  if ($parent_field_name && $parent_field_name == 'field_dorm_room_students') {

    $field_name = 'field_dorm_studentcontact';

    //FIND THE BUILDING
    $item_id = $entity->item_id;
    $nid = db_query("SELECT entity_id FROM field_data_field_dorm_room_students ".
		    "WHERE field_dorm_room_students_value = " . $item_id)->fetchField();
    
    $room = node_load($nid);
    if (!$room) {
      $nid = arg(1);
      $room = node_load($nid);
    }
    
    $building_id =
      dorm_management_get_entity_single_value_field($room,
						    'field_dorm_building',
						    'contact_id');

    $contact_id =
      dorm_management_get_entity_single_value_field($entity,
						    $field_name,
						    'contact_id');
    if ($contact_id) {
      civicrm_initialize();
      $result = civicrm_api3('Contact', 'get',
			     array(
				   'sequential' => 1,
				   'id' => $contact_id,
				   )
			     );
      
      if ($result && isset($result['values']) && $result['values']) {
	$contact = $name = $result['values'][0];
	$name = $result['values'][0]['display_name'];
	$name = l($name, "civicrm/contact/view",
		  array('query'=> array('cid'=>$contact_id)));
      }
    }

    //update original's relationship
    global $dorm_management_original_bed_occupier;

    if ($dorm_management_original_bed_occupier && 
	$dorm_management_original_bed_occupier != $contact_id) {
      

      //find if the original now has a bed somewhere else in same building,
      //if so continue
      $view = views_get_view('dorm_building_room_assignments');
      $view->set_display('block_2');
      $view->set_arguments(array($dorm_management_original_bed_occupier,
			   $building_id));

      $view->execute(); 
      $results = $view->result;

      if (array_pop($results)) {
	//if we found a result, i.e. this person has already moved to another
	//bed in the same building, we won't bother updating their relationship
      }
      else {
	//look up original relationship (the person beeing booted out of a bed
	$result = civicrm_api3('Relationship', 'get',
			       array(
				     'sequential' => 1,
				     'contact_id_b' => $building_id,
				     'contact_id_a' =>
				     $dorm_management_original_bed_occupier,
				     'relationship_type_id' => 13,
				     ));
	if ($result && isset($result['values']) && $result['values']) {
	  $relationship = $result['values'][0];
	  //if it exists, change end date to today and mark unactive
	  $relationship['is_active'] = 0;
	  $relationship['end_date'] = date('Y-m-d');
	  $rel_result = civicrm_api3('Relationship', 'create',
				     $relationship);

	}
	

      }
    }
    
    $field_name = 'field_dorm_students_student_date';
    $date = dorm_management_get_entity_single_value_field($entity,
							  $field_name,
							  'value');
    if ($contact) {
      //see if there is a relationship
      $result = civicrm_api3('Relationship', 'get',
			     array(
				   'sequential' => 1,
				   'contact_id_b' => $building_id,
				   'contact_id_a' => $contact_id,
				   'relationship_type_id' => 13,
				   ));
      if ($result && isset($result['values']) && $result['values']) {
	//if relationship, compare relationship end date with latest end date
	// (or null end dat if it exists) for this employer
	$relationship = $result['values'][0];
	
	if ($op == 'delete') {
	  //delete relationship
	  $parameters =
	    array(
		  'sequential' => 1,
		  'id' => $relationship['id'], 
		  'contact_id_a' => $contact_id,
		  'contact_id_b' => $building_id,
		  'relationship_type_id' => 13,
		  'start_date' => $date,
		  'end_date' => date('Y-m-d H:i:s'),
		  'is_active' => 0,
		  );
	  //update relationship
	  $rel_result = civicrm_api3('Relationship', 'create',
				     $parameters);
	  	  
	}
	else if ((strtotime($date) != strtotime($relationship['start_date']))
		 || strtotime($relationship['end_date'])) {
	  ////else if relationshp start date doesn't match update relationshp
	  $parameters =
	    array(
		  'sequential' => 1,
		  'id' => $relationship['id'], 
		  'contact_id_a' => $contact_id,
		  'contact_id_b' => $building_id,
		  'relationship_type_id' => 13,
		  'start_date' => $date,
		  'end_date' => '',
		  'is_active' => 1,
		  );
	  //update relationship
	  $rel_result = civicrm_api3('Relationship', 'create',
				     $parameters);
	}
	else {
	  ////else do nothing
	}
      }
      //no relationship exists with building
      else {
	//if there is no relationship create it
	$parameters =
	  array(
		'sequential' => 1,
		'contact_id_a' => $contact_id,
		'contact_id_b' => $building_id,
		'relationship_type_id' => 13,
		'start_date' => $date,
		);
	//if not create a new one
	$rel_result = civicrm_api3('Relationship', 'create',
				   $parameters);
      }
    }
  }
}