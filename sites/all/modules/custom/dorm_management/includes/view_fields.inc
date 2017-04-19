<?php

function dorm_management_room_capacity_numbers($row) {
  $ret = '';
  $node = node_load($row->nid);
  if ($node) {
    $fields = array("capacity" => "field_dorm_room_capacity",
		    "closets" => "field_dorm_room_closets",
		    "morebeds" => "field_dorm_room_morebeds",
		    "bathrooms" => "field_dorm_room_bathroom",
		    "available" => "field_cmptd_available_beds");
    foreach($fields as $field_id => $field_name) {
      $$field_id = dorm_management_get_entity_single_value_field($node,
								 $field_name,
								 'value');
      if (!$$field_id) {
	$$field_id = 0;
      }
    }

    $morebeds = $morebeds ? 'Yes' : 'No';

    $actual_available = dorm_managment_available_beds($node);
    if ($actual_available != $available) {
      $node->field_cmptd_available_beds[LANGUAGE_NONE][0]['value'] =
	$actual_available;
      field_attach_update('node', $node);      
    }
    $ret .=
      "Capacity: $capacity<br/>".
      "Available: $actual_available<br/>".
      "Bathrooms: $bathrooms<br/>".
      "Closets: $closets<br/>".
      "More Beds? $morebeds";
  }
  return $ret;
}
function dorm_management_relationship_type_transform($row) {
  $result = civicrm_api3('RelationshipType', 'get',
			 array(
			       'sequential' => 1,
			       'id' => $row->relationship_type,
			       ));
  if ($result && isset($result['values']) && $result['values']) {
    $name_b_a = $result['values'][0]['label_b_a'];

    $index = strrpos($name_b_a, ' ');
    return substr($name_b_a, 0,  $index);
  }
  return '';
}
function dorm_management_dorm_student_assignments($row) {
  $node = node_load($row->nid);
  $ret = '<ul>';
  $beds = $node->field_dorm_room_students[LANGUAGE_NONE];
  if ($beds) {
    foreach ($beds as $data) {      
      $name = '';
      $assignment = entity_load('field_collection_item',
				array($data['value']));
      $assignment = $assignment ? array_pop($assignment) : '';
      
      if ($assignment) {
	$field_name = 'field_dorm_studentcontact';
	$student_id =
	  dorm_management_get_entity_single_value_field($assignment,
							$field_name,
							'contact_id');
	if ($student_id) {
	  $result = civicrm_api3('Contact', 'get',
				 array(
				       'sequential' => 1,
				     'id' => $student_id,
				       )
				 );
	  
	  if ($result && isset($result['values']) && $result['values']) {
	    $name = $result['values'][0]['display_name'];
	    $name = l($name, "civicrm/contact/view",
		      array('query'=> array('cid'=>$student_id)));
	  }
	}
	  
	$field_name = 'field_dorm_students_bed_number';
	$bed_number =
	  dorm_management_get_entity_single_value_field($assignment,
							$field_name,
							'value');
	$field_name = 'field_dorm_students_student_date';
	$date = dorm_management_get_entity_single_value_field($assignment,
							      $field_name,
							      'value');
	$date = $date ? date('(d M Y)', strtotime($date)) : '';

	if (!$bed_number && !$student_id) {
	  continue;
	}
	if ($name || $bed_number || $date) {
	  $ret .= "<li>" . t("Bed #"). ' <strong>' . $bed_number .
	    '</strong> ';
	  
	  if ($name) {
	    $ret .= $name . ' '.$date;
	  }
	  else {
	    $ret .= "<strong>".t('AVAILABLE')."</strong>";
	  }
	  $destination = drupal_get_destination();
	  $destination = $destination['destination'];
	  $ret .= ' '.l('update',
			"field-collection/field-dorm-room-students/".
			$data['value']."/edit",
			array('query'=>
			      array('destination'=> $destination)));

	}
	
	
      }
    }
    $ret .= "<li><br/>".l(t("<Add New Bed>"), 'node/'.$row->nid.'/edit')."</li>";
    $ret .= "</ul>";

  }
  
  return $ret;
}
