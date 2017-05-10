<?php

function dorm_management_form_alter(&$form, &$form_state, $form_id) {


  if ($form['#form_id'] == 'field_collection_item_form' && $form['#entity'] &&
      $form['#entity']->field_name == 'field_dorm_room_students' ) {
    $item_id = $form['#entity']->item_id;
    $nid = db_query("SELECT entity_id FROM field_data_field_dorm_room_students ".
		    "WHERE field_dorm_room_students_value = " . $item_id)->fetchField();
    
    $room = node_load($nid);
    
    drupal_set_title(t("Updating a bed for @room", array('@room'=>$room->title)));
    
    //if we don't have a student, default date to today
    $student = dorm_management_get_entity_single_value_field($form['#entity'],
							     'field_dorm_studentcontact',
							     'contact_id');

    if (!$student) {
      $form['field_dorm_students_student_date'][LANGUAGE_NONE][0]['#default_value']['value']
	= date('Y-m-d H:i:s');
    }
    
    $form['#validate'][] = 'dorm_management_bed_assignment_validate';
  }
  //UPDATE CONTACT FORM SO THAT IF YOU PASS IN A CATEGORY ID THE CATEGORY WILL DEFAULT TO IT
  //AND DISABLE THE FIELD
  else if ($form_id == 'contact_site_form') {
    $category = filter_input(INPUT_GET, 'category');

    if ($category) {
      $form['cid']['#default_value'] = $category;
      $form['cid']['#disabled'] = TRUE;

      if ($category == 2) {
	drupal_set_title("Contact us about updating incorrect information about you in Bazla");
      }
    }
    
  }
}


function dorm_management_bed_assignment_validate($form, $form_values){
  $date =
    $form_values['values']['field_dorm_students_student_date'][LANGUAGE_NONE][0]['value'];

  $bed_number =
    $form_values['values']['field_dorm_students_bed_number'][LANGUAGE_NONE][0]['value'];

  $contact_id =
    $form_values['values']['field_dorm_studentcontact'][LANGUAGE_NONE][0]['contact_id'];

  $item_id = $form['#entity']->item_id;
  
  if (!$bed_number) {
    $form_field = 'field_dorm_students_bed_number';
    $msg = t('You must enter a room number.');
    form_set_error($form_field, $msg);	  
  }

  if ($contact_id && !$date) {
    $form_field = 'field_dorm_students_student_date';
    $msg = t('If you are adding a student you must add their date assigned.');
    form_set_error($form_field, $msg);	  
  }

  //find if the original now has a bed somewhere else in same building,
  //if so continue
  $view = views_get_view('dorm_building_room_assignments');
  $view->set_display('block_2');
  $view->set_arguments(array($contact_id));

  $view->execute(); 
  $results = $view->result;

  foreach($results as $result) {

    $other_item_id = $result->field_collection_item_field_data_field_dorm_room_students_it;

    if ($other_item_id == $item_id){
      //do nothing
      continue;
    }
    else {
      if ($contact_id) {
	$student =
	  db_query("SELECT display_name from civicrm_contact where id=$contact_id")
	  ->fetchField();
      }
      
      $room = node_load($result->nid)->title;

      $link =
	l("update", "field-collection/field-dorm-room-students/".$other_item_id."/edit",
	  array('query' => array('destination' => 'node/'.$result->nid),
		'attributes' => array('target' => '_blank')));
      
      $overlap_msg .= t('@student is already in @building @room. !link.',
	       array('@building' => $building, '@room' => $room,
		     '@student' => $student, '!link'=> $link))."<br/>";

    }    
  }

  if (isset($overlap_msg) && $overlap_msg) {
    $form_field = 'field_dorm_studentcontact';
    form_set_error($form_field, $overlap_msg);	  
  }

  
}