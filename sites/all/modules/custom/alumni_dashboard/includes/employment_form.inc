<?php 

// ---------------  AJAX CALLBACK  FUNCTIONS FOR TEXT FIELD-----------------
/**
 * Call back is used by all the ajax buttons on the slot grid, it rebuilds the
 * grid
 */
function alumni_dashboard_employment_grid_callback($form, $form_state) {
  return $form['employment_grid_cells'];
}

function alumni_dashboard_add_another_row($form, &$form_state) {

  if (!isset($form_state['num_rows'])) {
    $form_state['num_rows'] = 0;
    $form_state['num_rows']++;
  }
  $form_state['num_rows']++;

  $form_state['rebuild'] = TRUE;
}

function alumni_dashboard_employment_form_submit($form, &$form_state) {
  $contact_id = alumni_dashboard_get_logged_in_contact();
  
  $employee_fields = array('Employer' => 85,
			   'Job Title' => 86,
			   'Start' => 87,
			   'End' => 88,
			   'Salary' => 90,
			   'Currency' => 91);

  $values = $form_state['values']['employment_grid_cells'];
  
  foreach ($values as $job_id => $fields) {
    $existing_employer = isset($fields[$employee_fields['Employer']]) ?
      $fields[$employee_fields['Employer']] : NULL;
    $new_employer = (isset($fields['new_employer']) && $fields['new_employer'])
      ? $fields['new_employer'] : NULL;
    $end_date = isset($fields[$employee_fields['End']]) ?
      $fields[$employee_fields['End']] : '';
    
    
    if (!$existing_employer && !$new_employer && $end_date) {
      $end_date = strtotime($end_date);
      $end_date = date('Y-m-d H:i:s', $end_date);

      /**
      //MAMA TRIED, COULDN'T GET THE API TO CORRECTLY SET MULTI VALUE FIELDS
      $params = array('contact_id' => $contact_id,
		      'custom_'.$employee_fields['End'].':'.$job_id =>
		      $end_date,);
      $params = array('contact_id' => $contact_id,
		      'End_Date:Employment_History:'.$job_id => $end_date,);
      $params = array('contact_id' => $contact_id,
		      'End Date:Employment History:'.$job_id =>$end_date, );
      $result = civicrm_api3('Contact', 'create', $params);
      dsm($params, 'params'); dsm($result, 'post save');
      **/

      //FIXME TRY TO DO IT THE ABOVE WAY RATHER THAN DIRECTLY SAVING TO DB
      $sql =
	"UPDATE civicrm_value_employment_history_26 " .
	"SET end_date_88 = '$end_date' " .
	"WHERE id = $job_id";
      db_query($sql);

      alumni_dashboard_update_employer_relationships($contact_id);
    }
    else if ($existing_employer || $new_employer){
      if ($new_employer) {
	//CREATE NEW CONTACT
	$new_contact = $fields['new_contact'];
	$create_result =
	  civicrm_api3('Contact', 'create',
		       array(
			     'sequential' => 1,
			     'organization_name' =>
			     $new_contact['employer_name'],
			     'contact_type' => "Organization",
			     'contact_sub_type' => "Company",
			     ));
	
	if ($create_result && isset($create_result['values']) &&
	    $create_result['values']) {
	  //GET NEW CONTACT ID
	  $employer_id = $create_result['values'][0]['id'];
	  $params =
	    	 array(
		       'sequential' => 1,
		       'contact_id' => $employer_id,
		       'location_type_id' => 3,
		       'street_address' =>
		       $new_contact['street_address_1'],
		       'supplemental_address_1' =>
		       $new_contact['street_address_2'],
		       'city' => $new_contact['city'],
		       'postal_code' => $new_contact['code'],
		       );

	  if ($new_contact['state']) {
	    $params['state_province_id'] = $new_contact['state'];
	  }
	  if ($new_contact['country']) {
	    $params['country_id'] = $new_contact['country'];
	  }
	  if ($new_contact['commune']) {
	    $params['custom_45'] = $new_contact['commune'];
	  }

	  $add_result = civicrm_api3('Address', 'create', $params);
	}	
	//PUT NEW CONTACT IN USER ENTERED EMPLOYER GROUP
	$params = array(
			'contact_id' => $employer_id,
			'group_id' => 42,
			);
	$result = civicrm_api3('GroupContact', 'create', $params);
       
      }
      else if ($existing_employer) {
	//PARSE THE CIVI ORG contact_id FROM THE $existing_employer
	$employer_id =
	  substr($existing_employer, (strrpos($existing_employer, '(') + 1),
		 ((strrpos($existing_employer, ')') -
		   strrpos($existing_employer, '(')) - 1));
      }
      
      $start_date = strtotime($fields[$employee_fields['Start']]);
      $start_date = date('Y-m-d H:i:s', $start_date);

      $end_date = $fields[$employee_fields['End']] ?
	strtotime($fields[$employee_fields['End']]) : '';
      
      $end_date = $end_date ? "'".date('Y-m-d H:i:s', $end_date)."'" : 'NULL';

      //SAVE CONTACT WITH ALL THE FIELDS FOR EMPLOYER HISTORY
      //FIXME, FIND OUT HOW TO USE CIVICRM API TO SAVE A NEW MULTI VALUE
      //FIELD, TRIED ABOVE WITHOUT SUCCESS SO FOR NOW DIRECT QUERY INSERT
      $salary = str_replace('$', '', $fields[$employee_fields['Salary']]);
      $sql =
	"INSERT INTO civicrm_value_employment_history_26 " .
	"(entity_id, employer_85, job_title_86, start_date_87, end_date_88, " .
	" salary_yearly__90, currency_91) VALUES " .
	"(".$contact_id.", " . $employer_id . ", '".
	$fields[$employee_fields['Job Title']] . "', '".
	$start_date . "', ".$end_date . ", ". $salary . ", '".
	$fields[$employee_fields['Currency']] . "') ";

      db_query($sql);
      alumni_dashboard_update_employer_relationships($contact_id);
    }
  }
}
function alumni_dashboard_employment_form_validate($form, &$form_state) {
  $contact_id = alumni_dashboard_get_logged_in_contact();

  $employee_fields = array('Employer' => 85,
			   'Job Title' => 86,
			   'Start' => 87,
			   'End' => 88,
			   'Salary' => 90,
			   'Currency' => 91);

  $values = $form_state['values']['employment_grid_cells'];
  
  foreach ($values as $job_id => $fields) {
    if (!is_int($job_id)) {
      continue;
    }
    $employer = isset($fields[$employee_fields['Employer']]) ?
      $fields[$employee_fields['Employer']] : NULL;

    $new_contact = $employer_id = NULL;
    
    $new_employer = (isset($fields['new_employer']) && $fields['new_employer'])
      ? $fields['new_employer'] : NULL;
    $entering_employer = FALSE;
    if ($new_employer) {
      $employer_id = NULL;
      $new_contact = $fields['new_contact'];
      $employer_name = $new_contact['employer_name'];      
      $street_address_1 = $new_contact['street_address_1'];
      $street_address_2 = $new_contact['street_address_2'];
      $code = $new_contact['code'];
      $city = $new_contact['city'];
      $state = $new_contact['state'];
      $country = $new_contact['country'];
      $entering_employer = TRUE;
    }
    else if ($employer) {
      $entering_employer = TRUE;
      $first_paren_index = strrpos($employer, '(');
      $second_paren_index = strrpos($employer, ')');
      if ($first_paren_index && $second_paren_index) {
	$employer_id =
	  substr($employer, ($first_paren_index + 1),
		 (($second_paren_index - $first_paren_index) - 1));

	$result = civicrm_api3('Contact', 'get',
			       array(
				     'sequential' => 1,
				     'id' => $employer_id,
				     )
			       );
	
	if ($result && isset($result['values']) && $result['values'] &&
	    $result['values'][0]['contact_type'] == 'Organization') {
	  //do nothing, our contact id is real and is an organization
	}
	else {
	  //didn't have a real contact id of an organization so unsetting
	  $employer_id = NULL;
	}
      } 
    }
    else {
      $employer_id = NULL;
    }
    $employee_fields = array('Employer' => 85,
			     'Job Title' => 86,
			     'Start' => 87,
			     'End' => 88,
			     'Salary' => 90,
			     'Currency' => 91);
    
    $start = $fields[$employee_fields['Start']] ?
      $fields[$employee_fields['Start']] : '';
    $start = $start ? strtotime($start) : '';
    $start = $start ? date('Y-m-d H:i:s', $start) : '';

    $end = $fields[$employee_fields['End']] ?
      $fields[$employee_fields['End']] : '';
    $end = $end ? strtotime($end) : '';
    $end = $end ? date('Y-m-d H:i:s', $end) : '';

    $job_title = isset($fields[$employee_fields['Job Title']]) ?
      $fields[$employee_fields['Job Title']] : '';
    $salary = isset($fields[$employee_fields['Salary']]) ?
      $fields[$employee_fields['Salary']] : '';
    $currency = isset($fields[$employee_fields['Currency']]) ?
      $fields[$employee_fields['Currency']] : '';

    /**
    if ($new_employer && (!$employer_name || !$street_address_1 || !$code ||
			  !$city || !$state    || !$country)) {
      $contact_fields = array('employer_name', 'street_address_1', 'code',
			      'city', 'state', 'country');
      
      $msg = t("If you are trying to add a new Employer to Bazla you must " .
	"fill out all the necessary fields highlighted in red below.");
      foreach ($contact_fields as $field_name) {
	$form_field = 'employment_grid_cells]['.$job_id.'][new_contact]['.
	  $field_name;
	if ($msg && !($$field_name)) {
	  form_set_error($form_field, $msg);
	  $msg = '';
	}
	else if (!($$field_name)) {
	  form_set_error($form_field);
	}
      }
    }
    */
    if ($new_employer && !$employer_name) {
      $form_field = 'employment_grid_cells]['.$job_id.'][new_contact][employer_name';
      $msg = t("If you are trying to add a new Employer to Bazla you must " .
	"fill out all the necessary fields highlighted in red below.");
      form_set_error($form_field, $msg);
    }

    if (!$new_employer && $employer && !$employer_id) {
      $form_field = 'employment_grid_cells]['.$job_id.']['.
	$employee_fields['Employer'];
      $msg = t('You did select a valid Employer.');
      form_set_error($form_field, $msg);	  
    }

    //fixme, if we ever allow editing of more than one field this will need
    //to be fixed
    if (count($fields) == 2) {
      //do nothing,
    }
    else if ($entering_employer || $start || $end || $job_title ||
	     $salary || $currency) {
      $msg = t("If you wish to add a new job to your history you must fill ".
	       "out all the fields highlighted below");
      foreach ($employee_fields as $field_name=>$field_id) {
	$form_field = 'employment_grid_cells]['.$job_id.']['.
	  $employee_fields[$field_name];
	if ($field_name == 'Employer' && !$entering_employer) {
	  if ($msg) {
	    form_set_error($form_field, $msg);
	    $msg = '';
	  }
	  else {
	    form_set_error($form_field);
	  }
	}
	else if ($field_name == 'Employer') {
	  //do nothing
	}
	else if (!$fields[$employee_fields[$field_name]] &&
		 $field_name != 'End') {
	  if ($msg) {
	    form_set_error($form_field, $msg);
	    $msg = '';
	  }
	  else {
	    form_set_error($form_field);
	  }
	}
      } 
    }

    if ($salary) {
      $salary = str_replace("$", "", str_replace(",", "", $salary));
      if (!is_numeric($salary) || $salary <= 0) {
	$msg = t("You entered an incorrect format for salary, please just ".
	  "enter a number.");
	$form_field = 'employment_grid_cells]['.$job_id.']['.
	  $employee_fields['Salary'];
	  
	form_set_error($form_field, $msg);
      }
    }

    if ($start && $end) {
      if (strtotime($end) < strtotime($start)) {
	$form_field = 'employment_grid_cells]['.$job_id.']['.
	  $employee_fields['End'];
	$msg =
	  t("Your end time for your job must be later than your start time");
	
	form_set_error($form_field, $msg);
      }
    }
    
    

  }
}
function alumni_dashboard_employment_form($form, &$form_state,
					  $no_js_use = FALSE) {


  drupal_add_css('.container-inline-date .date-padding {padding:0px;}', 
  		 'inline');

  $form = array();
  $form['#tree'] = TRUE;
  $form['#attributes']['enctype'] = 'multipart/form-data';

  

  if (empty($form_state['num_rows'])) {
    $form_state['num_rows'] = 1;
  }

  $form['employment_grid_cells'] = 
    array(
	  '#type' => 'fieldset',
	  '#prefix' => '<div id="employment-grid-wrapper">',
	  '#suffix' => '</div>',
	  );


  $contact_id = alumni_dashboard_get_logged_in_contact();
  
  if (!$contact_id) {
    $form['error'] = array('#markup'=>t("Sorry, cannot do that for you."));
    return $form;
  }
  /////////////////////////////////////////////////////////////////

  $employee_fields = array('Employer' => 85,
			   'Job Title' => 86,
			   'Start' => 87,
			   'End' => 88,
			   'Salary' => 90,
			   'Currency' => 91);
  $employment_field_data = array();
  $result = civicrm_api3('CustomValue', 'get', array(
						     'sequential' => 1,
						     'entity_id' =>
						     $contact_id,
						     ));
  if ($result && isset($result['values']) && $result['values']) {
    foreach ($result['values'] as $key => $field_values) {
      if (in_array($field_values['id'], $employee_fields)) {

	foreach ($field_values as $index => $value) {
	  if (is_int($index)) {
	    $employment_field_data[$index] =
	      isset($employment_field_data[$index]) ?
	      $employment_field_data[$index] : array();
	    
	    $employment_field_data[$index][$field_values['id']] =
	      $value;
	  }
	}
      }
    }
  }
  $form_state['num_rows'] =
    ((count($employment_field_data) + 1) > $form_state['num_rows']) ?
    count($employment_field_data) + 1 : $form_state['num_rows'];

  $table =
    "<table class='employment_form_grid'>".
    "<th>Employer</th>".
    "<th>Job Title</th><th>Salary</th><th>Currency</th>".
    "<th>Start</th><th>End</th>";
  
  $form['employment_grid_cells']['header'] =
    array('#prefix' => $table, '#markup' => '');

  $table = '';
  
  $row_class = 'padded_odd';
  $first_pass = true;
  for ( $i = 0; $i < $form_state['num_rows']; $i++) {
    if ($first_pass) {
      $first_pass = FALSE;
      foreach($employment_field_data as $set_id => $values) {
	$table .=	"<tr class='$row_class'>";
	$row_class = ($row_class == 'padded_odd') ?
	  'padded_even' : 'padded_odd';
	$result = civicrm_api3('Contact', 'get',
			       array(
				     'sequential' => 1,
				     'id' =>
				     $values[$employee_fields['Employer']],
				     )
			       );
	
	if ($result && isset($result['values']) && $result['values']) {
	  $table .= "<td>".$result['values'][0]['display_name']."</td>";
	}
	else {
	  $table .= "<td>Missing</td>";
	}
	
	$table .= "<td>".$values[$employee_fields['Job Title']]."</td>";
	$table .= "<td>".$values[$employee_fields['Salary']]."</td>";

	$currency_array = array('us'=>'US Dollars','htg'=>'HTG');
	$currency = $currency_array[$values[$employee_fields['Currency']]];
	$table .= "<td>".$currency."</td>";
	
	$start = date('d M Y' ,strtotime($values[$employee_fields['Start']]));
	$table .= "<td>".$start."</td>";

	if ($values[$employee_fields['End']]) {
	  $end = date('d M Y' ,strtotime($values[$employee_fields['End']]));
	  $form['employment_grid_cells'][$set_id]
	    [$employee_fields['End']] =
	    array(
		  '#prefix' => $table."<td>",
		  '#markup' => $end,
		  '#suffix' => '</td></tr>',
		  );
	  $table = '';
	}
	else {
	  $form['employment_grid_cells'][$set_id][$employee_fields['End']] =
	    alumni_dashboard_get_field('End', 'date_popup', FALSE, array(),
				       $table."<td>", "</td></tr>");
	  $form['employment_grid_cells'][$set_id][$employee_fields['Start']] =
	  array(
		'#type' => 'hidden',
		'#value' => $start,
		);

	  $table = "";
	}
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
    $not_checked_state =
      array('visible' =>
	    array(
		  ':input[name="employment_grid_cells['.
		  $set_id.'][new_employer]"]' => array('checked' => FALSE),
		  ),
	    );
	    
    $checked_state =
      array('visible' =>
	    array(
		  ':input[name="employment_grid_cells['.
		  $set_id.'][new_employer]"]' => array('checked' => TRUE),
		  ),
	    );
        
    $form['employment_grid_cells'][$set_id][$employee_fields['Employer']] =
      alumni_dashboard_get_field(t('Find Employer'), 'textfield', FALSE,
				 $not_checked_state, $row.$cell);

    $form['employment_grid_cells'][$set_id][$employee_fields['Employer']]
      ['#autocomplete_path'] = 'dashboard/alumni/employer_autocomplete';
    
    $form['employment_grid_cells'][$set_id]['new_employer'] =
      alumni_dashboard_get_field(t('Add New Employer?'), 'checkbox', FALSE,
				 array(), "</br>", '', 0,
				 t('Check here if you cannot find your '.
				   'employer.'));

    $form['employment_grid_cells'][$set_id]['new_contact'] = 
      array(
	    '#title' => t('Add new Employer to Bazla'),
	    '#type' => 'fieldset',
	    '#states' => $checked_state,
	    );
    
    $form['employment_grid_cells'][$set_id]['new_contact']['employer_name'] =
      alumni_dashboard_get_field(t('Employer Name'), 'textfield', FALSE,
				 $checked_state, "", '', 10);

    $form['employment_grid_cells'][$set_id]['new_contact']['street_address_1']=
      alumni_dashboard_get_field(t("Street Address 1"), 'textfield', FALSE,
				 $checked_state, "", '', 11);

    $form['employment_grid_cells'][$set_id]['new_contact']['street_address_2']=
      alumni_dashboard_get_field(t("Street Address 2"), 'textfield', FALSE,
				 $checked_state, "", '', 12);

    
    $sql ="select id, name from civicrm_country order by id=1094 desc, " .
      "id= 1228 desc, name asc";
    $results = db_query($sql);
    $options = array(0=>'- Select -');
    while ($result = $results->fetchObject()) {
      $options[$result->id] = $result->name;
    }

    $form['employment_grid_cells'][$set_id]['new_contact']['country'] =
      alumni_dashboard_get_field(t("Country"), 'select', FALSE,
				 $checked_state, "", '', 13, '', $options,
				 1094);
    
    $sql ="select id, name from civicrm_state_province ".
      "order by country_id=1094 desc, country_id=1228 desc, ".
      "country_id=1039 desc, country_id asc, name asc";
    $results = db_query($sql);
    $options = array(0=>'- Select -');
    while ($result = $results->fetchObject()) {
      $options[$result->id] = $result->name;
    }

    $form['employment_grid_cells'][$set_id]['new_contact']['state'] =
      alumni_dashboard_get_field(t("State"), 'select', FALSE,
				 array(), "", '', 14, '', $options);

    $sql="select id,value from civicrm_option_value where option_group_id=91";
    $results = db_query($sql);
    $options = array(0=>'- Select -');
    while ($result = $results->fetchObject()) {
      $options[$result->value] = $result->value;
    }

    $form['employment_grid_cells'][$set_id]['new_contact']['commune'] =
      alumni_dashboard_get_field(t("Commune"), 'select', FALSE,
    				 $checked_state, "", '', 15,
				 t("Only for Haitian Employers"), $options);

    $form['employment_grid_cells'][$set_id]['new_contact']['city'] =
      alumni_dashboard_get_field(t("City"), 'textfield', FALSE,
				 $checked_state, "", '', 16);
    
    $form['employment_grid_cells'][$set_id]['new_contact']['code'] =
      alumni_dashboard_get_field(t("Postal Code"), 'textfield', FALSE,
				 $checked_state, "", '', 17);


    $form['employment_grid_cells'][$set_id]['cell_end'] =
      array('#markup' => "</td>");
    
    $table = '';
       
    $form['employment_grid_cells'][$set_id]
      [$employee_fields['Job Title']] =
      array(
	    '#type' => 'textfield',
	    '#title' => t("New Job Title"),
	    '#required' => false,
	    '#description' => '',
	    '#prefix' => $cell,
	    '#suffix' => '</td>',
	    '#size' => 20,
	    );
    
    $form['employment_grid_cells'][$set_id]
      [$employee_fields['Salary']] =
      array(
	    '#type' => 'textfield',
	    '#required' => false,
	    '#title' => 'New Salary (Yearly)',
	    '#prefix' => $cell,
	    '#suffix' => '</td>',
	    '#size' => 10,
	    );
	
    $form['employment_grid_cells'][$set_id]
      [$employee_fields['Currency']] =
      array(
	    '#type' => 'select',
	    '#title' => t("New Currency"),
	    '#required' => false,
	    '#description' => '',
	    '#options' => array(
				0 => '-select-',
				'us'=>'US Dollars',
				'htg'=>'HTG',
				),
	    '#prefix' => $cell,
	    '#suffix' => '</td>',
	    );
    
    $form['employment_grid_cells'][$set_id]
      [$employee_fields['Start']] =
	  array(
		'#title' => 'New Start',
		'#type' => 'date_popup',
		'#required' => false,
		'#date_label_position' => 'within',
		'#size' => 15,
		'#date_format' => 'd M Y',
		'#timepicker' => FALSE,
		'#description' => '',
		'#prefix' => $cell,
		'#suffix' => '</td>',
		);

    $form['employment_grid_cells'][$set_id]
      [$employee_fields['End']] =
	  array(
		'#title' => 'New End',
		'#type' => 'date_popup',
		'#date_label_position' => 'within',
		'#size' => 15,
		'#date_format' => 'd M Y',
		'#timepicker' => FALSE,
		'#description' => '',
		'#prefix' => $cell,
		'#suffix' => '</td></tr>',
		);
    }
  
  $form['employment_grid_cells']['add_row_button'] = 
    array(
	  '#type' => 'submit',
	  '#value' => t('Add another Row'),
	  '#submit' => array('alumni_dashboard_add_another_row'),
	  '#ajax' =>
	  array(
		'callback' => 'alumni_dashboard_employment_grid_callback',
		'wrapper' => 'employment-grid-wrapper',
		),
	  '#prefix' => "<tr class='$row_class'><td colspan=5>&nbsp;</td><td>",
	  '#suffix' => "</td></tr>",
	  );
    $row_class = ($row_class == 'padded_odd') ? 'padded_even' : 'padded_odd';

    $form['employment_grid_cells']['submit_button'] = 
    array(
	  '#type' => 'submit',
	  '#value' => t('Update Employment History'),
	  '#prefix' => "<tr class='$row_class'><td colspan=6>",
	  '#suffix' => "</td></tr></table>",
	  );

  return $form;
}

function alumni_dashboard_employer_autocomplete($string) {
  $matches = array();
  $results =
    db_query(	     
	     "select id, display_name ". 
	     "from civicrm_contact c ".
	     "where contact_type='organization'  ". 
	     "and id not in " .
	     "(SELECT distinct contact_id from civicrm_group_contact ".
	     " WHERE group_id = 42 and status != 'Removed') ".
	     "and contact_sub_type not like '%Field_of_Study%'  ". 
	     "and contact_sub_type not like '%Secondary_School%'  ". 
	     "and contact_sub_type not like '%University_Department%'  ". 
	     "and contact_sub_type not like '%Facult_%' ". 
	     "and contact_sub_type not like '%Educational_Institution%'  ". 
	     "and display_name like '%".$string."%'  ". 
	     "order by display_name");
  
  while ($result = $results->fetchObject()) {
    $key = $result->display_name . ' (' . $result->id . ')';
    $matches[$key] = $result->display_name;
  }
  asort($matches);
  drupal_json_output($matches);
}
