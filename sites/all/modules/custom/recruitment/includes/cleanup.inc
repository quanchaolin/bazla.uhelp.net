<?php
function recruitment_cleanup_form($form, &$form_state) {
  $relationships = recruitement_relationships();

  
  $form['cleanup_fieldset'] = 
    array(
	  '#type' => 'fieldset',
	  );



    
  $form['cleanup_fieldset']['submit_button'] = 
    array(
	  '#type' => 'submit',
	  '#prefix' => "There are " . count($relationships) .
	  " that can be cleaned up (adding end date + marking inactive)<br/> ",
	  '#value' => t('Cleanup Recruitment Relationships'),
	  );

  return $form;
}

function recruitment_cleanup_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $relationships = recruitement_relationships();

  foreach($relationships as $relationship) {
    $relationship['end_date'] = $relationship['start_date'];
    $relationship['is_active'] = 0;

    $result = civicrm_api3('Relationship', 'create',  $relationship);
  }
  
  global $relationships;
  $relationships = array();
}

function recruitement_relationships() {
  global $relationships;
  if ($relationships) {
    return $relationships;
  }
  $relationships = array();
  civicrm_initialize();
  $result = civicrm_api3('Relationship', 'get',
			 array(
			       'sequential' => 1,
			       'relationship_type_id' => 40,
			       'options' => array('limit' => 1000),
			       'end_date' => array('IS NULL' => 1),
			       ));

  if ($result && isset($result['values']) && $result['values']) {
    foreach($result['values'] as $k=>$value) {
      $relationships[] = $value;
    }
  }

  $result = civicrm_api3('Relationship', 'get',
			 array(
			       'sequential' => 1,
			       'relationship_type_id' => 39,
			       'options' => array('limit' => 1000),
			       'end_date' => array('IS NULL' => 1),
			       ));

  if ($result && isset($result['values']) && $result['values']) {
    foreach($result['values'] as $k=>$value) {
      $relationships[] = $value;
    }
  }
  return $relationships;
}