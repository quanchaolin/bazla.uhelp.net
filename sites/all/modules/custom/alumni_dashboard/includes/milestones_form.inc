<?php 

// ---------------  AJAX CALLBACK  FUNCTIONS FOR TEXT FIELD-----------------
/**
 * Call back is used by all the ajax buttons on the slot grid, it rebuilds the
 * grid
 */
function alumni_dashboard_milestones_grid_callback($form, $form_state) {
  return $form['milestones_grid_cells'];
}

function alumni_dashboard_milestones_form_submit($form, &$form_state) {
  $contact_id = alumni_dashboard_get_logged_in_contact();

  $milestone_fields = array('Milestone' => 92,
			    'Date' => 93,
			    'Details' => 94,
			    );
  $values = $form_state['values']['milestones_grid_cells'];
  foreach ($values as $milestone_id => $fields) {
    if (!is_int($milestone_id)) {
      continue;
    }
    $date = $fields[$milestone_fields['Date']];
    $date = strtotime($date);
    $date = date('Y-m-d H:i:s', $date);
     
    //SAVE CONTACT WITH ALL THE FIELDS FOR EMPLOYER HISTORY
    //FIXME, FIND OUT HOW TO USE CIVICRM API TO SAVE A NEW MULTI VALUE
    //FIELD, TRIED ABOVE WITHOUT SUCCESS SO FOR NOW DIRECT QUERY INSERT

    $sql =
      "INSERT INTO civicrm_value_life_civic_milestones_27 " .
      "(entity_id, milestone_92, details_94,date_93) VALUES " .
      "(".$contact_id.", '" . 
      $fields[$milestone_fields['Milestone']]. "', '". 
      $fields[$milestone_fields['Details']] .
      "', '".$date . "')";

    db_query($sql);

    if (module_exists('email_notifications')) {
      $alumni_name =
	db_query("SELECT display_name from civicrm_contact where id=$contact_id")
	->fetchField();
	
      global $base_url;
      $alumni_link = $base_url . "/civicrm/contact/view?cid=" . $contact_id;
      
      $data = array('milestone' => $fields[$milestone_fields['Milestone']],
		    'details' => $fields[$milestone_fields['Details']],
		    'alumni_link' => $alumni_link,
		    'alumni_name' => $alumni_name, 
		    'date' => date('d M Y', strtotime($date)));
      
      
      email_notifications_send('alumni_milestone', $data);
    }
  }
}
function alumni_dashboard_milestones_form_validate($form, &$form_state) {
  $milestone_fields = array('Milestone' => 92,
			    'Date' => 93,
			    'Details' => 94,
			    );

  $values = $form_state['values']['milestones_grid_cells'];
  foreach ($values as $milestone_id => $fields) {
    if (!is_int($milestone_id)) {
      continue;
    }

    //empty date field comes as an array, why? who knows
    if (is_array($fields[$milestone_fields['Date']])) {
      $date = '';
    }
    else {
      $date = $fields[$milestone_fields['Date']];
      $date = $date ? strtotime($date) : '';
      $date = $date? date('Y-m-d H:i:s', $date) : '';
    }
      
    $milestone = $fields[$milestone_fields['Milestone']]; 
    $details = $fields[$milestone_fields['Details']];

    if ($milestone == 'other' && !$details) {
      form_set_error('milestones_grid_cells]['.$milestone_id.']['.
		     $milestone_fields['Details'],
		     t("You must add details when selecting 'other' for ".
		       "your 'New Achievement/Milestone' choice."));
     
    }
  }
}
function alumni_dashboard_milestones_form($form, &$form_state,
					  $no_js_use = FALSE) {


  drupal_add_css('.container-inline-date .date-padding {padding:0px;}', 
  		 'inline');

  $form = array();
  $form['#tree'] = TRUE;
  $form['#attributes']['enctype'] = 'multipart/form-data';

  if (empty($form_state['num_rows'])) {
    $form_state['num_rows'] = 1;
  }

  $form['milestones_grid_cells'] = 
    array(
	  '#type' => 'fieldset',
	  '#prefix' => '<div id="milestones-grid-wrapper">',
	  '#suffix' => '</div>',
	  );


  $contact_id = alumni_dashboard_get_logged_in_contact();
  
  if (!$contact_id) {
    $form['error'] = array('#markup'=>t("Sorry, cannot do that for you."));
    return $form;
  }
  /////////////////////////////////////////////////////////////////

  $milestone_fields = array('Milestone' => 92,
			   'Date' => 93,
			   'Details' => 94,
			    );
  $milestones_field_data = array();
  $result = civicrm_api3('CustomValue', 'get', array(
						     'sequential' => 1,
						     'entity_id' =>
						     $contact_id,
						     ));
  if ($result && isset($result['values']) && $result['values']) {
    foreach ($result['values'] as $key => $field_values) {
      if (in_array($field_values['id'], $milestone_fields)) {

	foreach ($field_values as $index => $value) {
	  if (is_int($index)) {
	    $milestones_field_data[$index] =
	      isset($milestones_field_data[$index]) ?
	      $milestones_field_data[$index] : array();
	    
	    $milestones_field_data[$index][$field_values['id']] =
	      $value;
	  }
	}
      }
    }
  }

  $form_state['num_rows'] =
    ((count($milestones_field_data) + 1) > $form_state['num_rows']) ?
    count($milestones_field_data) + 1 : $form_state['num_rows'];

  $table = "<table  class='milestones_form_grid'><th>Milestone</th>".
    "<th>Details</th><th>Date</th>";
  $row_class = 'padded_odd';
  $first_pass = true;
  for ( $i = 0; $i < $form_state['num_rows']; $i++) {
    if ($first_pass) {
      $first_pass = FALSE;
      foreach($milestones_field_data as $set_id => $values) {
	$table .= "<tr class='$row_class'>";
	$row_class = ($row_class == 'padded_odd') ?
	  'padded_even' : 'padded_odd';

	$table .= "<td>".$values[$milestone_fields['Milestone']]."</td>";

	$table .= "<td>".$values[$milestone_fields['Details']]."</td>";

	$date = date('d M Y' ,strtotime($values[$milestone_fields['Date']]));
	$table .= "<td>".$date."</td>";
	
	$i++;
      }
    }


    //set id will come from the id's in the custom field data, if there is
    //none we will just start with 1
    if (isset($set_id) && $set_id) {
      $set_id ++;
    }
    else {
      $set_id = 1;
    }

    $row = "<tr class='$row_class'>";
    $row_class = ($row_class == 'padded_odd') ? 'padded_even' : 'padded_odd';

    $cell = '<td style="vertical-align:top">';
    
    $sql="select id,value from civicrm_option_value where option_group_id=108";
    $results = db_query($sql);
    while ($result = $results->fetchObject()) {
      $options[$result->value] = $result->value;
    }
    $options['other'] = 'other';
    
    
    $form['milestones_grid_cells'][$set_id]
      [$milestone_fields['Milestone']] =
      array(
	    '#type' => 'select',
	    '#title' => t("New Achievement/Milestone"),
	    '#required' => true,
	    '#description' => '',
	    '#options' => $options,
	    '#prefix' => $table.$row.$cell,
	    '#suffix' => '</td>',
	    );
    $table = '';
    
    $form['milestones_grid_cells'][$set_id]
      [$milestone_fields['Details']] =
      array(
	    '#type' => 'textfield',
	    '#title' => t("Details on new Event"),
	    '#required' => false,
	    '#description' => '',
	    '#prefix' => $cell,
	    '#suffix' => '</td>',
	    '#size' => 20,
	    );
    
    $form['milestones_grid_cells'][$set_id]
      [$milestone_fields['Date']] =
      array(
	    '#title' => t('New Event Date'),
	    '#type' => 'date_popup',
	    '#required' => true,
	    '#date_label_position' => 'within',
	    '#size' => 15,
	    '#date_format' => 'd M Y',
	    '#timepicker' => FALSE,
	    '#description' => '',
	    '#prefix' => $cell,
	    '#suffix' => '</td></tr>',
	    );
  }
  $form['milestones_grid_cells']['add_row_button'] = 
    array(
	  '#type' => 'submit',
	  '#value' => t('Add another Row'),
	  '#submit' => array('alumni_dashboard_add_another_row'),
	  '#ajax' =>
	  array(
		'callback' => 'alumni_dashboard_milestones_grid_callback',
		'wrapper' => 'milestones-grid-wrapper',
		),
	  '#prefix' => "<tr class='$row_class'><td colspan=2>&nbsp;</td><td>",
	  '#suffix' => "</td></tr>",
	  );
  /**
  $form['milestones_grid_cells']['remove_row_button'] = 
    array(
	  '#type' => 'submit',
	  '#value' => t('Remove New Row'),
	  '#submit' => array('alumni_dashboard_remove_row'),
	  '#ajax' =>
	  array(
		'callback' => 'alumni_dashboard_milestones_grid_callback',
		'wrapper' => 'milestones-grid-wrapper',
		),
	  '#prefix' => "<tr class='$row_class'><td colspan=2>&nbsp;</td><td>",
	  '#suffix' => "</td></tr>",
	  );
  */
  $row_class = ($row_class == 'padded_odd') ? 'padded_even' : 'padded_odd';
  $form['milestones_grid_cells']['submit_button'] = 
    array(
	  '#type' => 'submit',
	  '#value' => t('Update Achievements/Milestones History'),
	  '#prefix' => "<tr class='$row_class'><td colspan=6>",
	  '#suffix' => "</td></tr></table>",
	  );
  
  return $form;
  
}
