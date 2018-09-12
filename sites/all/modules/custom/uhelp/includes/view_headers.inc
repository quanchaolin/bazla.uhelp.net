<?php 
/**
 * Functions in this include file will provide custom headers for views.
 * The headers will be built by subquerying the results from the view object
 * for sums and averages and what not.
 */


/**
 * builds a report table for the recruitment overview view
 */
function uhelp_view_headers_gradepoint() {
  $view = views_get_current_view();
  $results = $view->result;

  $total_credits = array();
  $total_grade = array();

  $overall_credits = 0;
  $overall_grade = 0; 

  foreach ($results as $view_data) {
    $node = node_load($view_data->nid);
    $grade = uhelp_view_headers_get_single_field_value($node, 
						       'field_eval_grade',
						       'value');
    
    $credits = uhelp_view_headers_get_single_field_value($node, 
							 'field_eval_credits',
							 'value');
    $credits = $credits ? $credits : 1;

    $class_nid = uhelp_view_headers_get_single_field_value($node, 
							 'field_eval_class',
							 'target_id');
    $class = $class_nid ? node_load($class_nid) : NULL;

    $period_tid = 
      uhelp_view_headers_get_single_field_value($class, 
						'field_academic_period',
						'tid');

    $term = taxonomy_term_load($period_tid);
    $period = $term->name;

    $total_credits[$period] = isset($total_credits[$period]) ?
      $total_credits[$period] : 0;
    $total_grade[$period] = isset($total_grade[$period]) ?
      $total_grade[$period] : 0;

    $total_credits[$period] += $credits;
    $total_grade[$period] += $grade*$credits;
    $overall_credits += $credits;
    $overall_grade += $grade*$credits;

  }

  $headers = array('Academic Period', 'Grade', 'Credits');
  $rows = array();
  
  foreach($total_credits as $period=>$credits) {
    $rows[] = array(
		    $period,
		    round($total_grade[$period]/ $credits, 2),
		    $credits
		    );
  }
  $rows[] = array(
		  'Overall',
		  round($overall_grade/ $overall_credits, 2),
		  $overall_credits
		  );

  $output = "<br/><br/><h2>Averages</h2>".  
    theme('table', array('header' => $headers, 'rows' => $rows));
  return $output;
  
}

function uhelp_view_headers_get_single_field_value($node, $field_name,
                                                  $index = 'value') { 
  if (isset($node->{$field_name})) {
    $field = $node->{$field_name};
    if (isset($field[LANGUAGE_NONE]) && isset($field[LANGUAGE_NONE][0])) {
      return $field[LANGUAGE_NONE][0][$index];
    }
  }
  return NULL;
}

/**
 * builds a report table for the recruitment overview view
 */
function uhelp_view_headers_recruitment_overview() {
  $view = views_get_current_view();
  $count_query = $view->build_info['count_query'];
  $count_query_string = $count_query->__toString();

  $select_less_query =substr($count_query_string,
			     strpos($count_query_string, "FROM"));
  $select_less_query =substr($select_less_query, 0, 
			     strpos($select_less_query, "ORDER"));
  $exposed_input = $view->exposed_input;

  $query_args = $count_query->getArguments();
  $result_nids =
    uhelp_view_headers_get_result_nids($select_less_query, $query_args);

  $sql = "
    SELECT sum(field_r_total_male_value) as gender_count
    FROM node n
    INNER JOIN field_data_field_r_total_male m on m.entity_id=n.nid
    WHERE n.nid in ( $result_nids )
    ";
  $male_count = db_query($sql)->fetchObject()->gender_count;
  
  $sql = "
    SELECT sum(field_r_total_female_value) as gender_count
    FROM node n
    INNER JOIN field_data_field_r_total_female g on g.entity_id=n.nid
    WHERE n.nid in ( $result_nids )
    ";
  $female_count = db_query($sql)->fetchObject()->gender_count;
  
  if ($exposed_input && 
      isset($exposed_input['field_recruitment_date_of_visit_value']) &&
      $exposed_input['field_recruitment_date_of_visit_value']) {
    $min_array = 
      isset($exposed_input['field_recruitment_date_of_visit_value']['min']) ?
      $exposed_input['field_recruitment_date_of_visit_value']['min'] : NULL;
    $max_array = 
      isset($exposed_input['field_recruitment_date_of_visit_value']['max']) ?
      $exposed_input['field_recruitment_date_of_visit_value']['max'] : NULL;
    $min = $min_array && $min_array['day'] && $min_array['month'] && 
      $min_array['year'] ? 
      $min_array['day'].'-'.$min_array['month'].'-'.$min_array['year'] : NULL;
    $max = $max_array && $max_array['day'] && $max_array['month'] && 
      $max_array['year'] ? 
      $max_array['day'].'-'.$max_array['month'].'-'.$max_array['year'] : NULL;
  }
  
  $header = array();
  $rows = array();
  $rows[0] = array();
  if ($min) {
    $header[] = "Start Date";
    $rows[0][] = $min;
  }
  if ($max) {
    $header[] = "End Date";
    $rows[0][] = $max;
  }

  $header[] = "Male Students";
  $header[] = "Female Students";
  $header[] = "Total Students";
  $rows[0][] = $male_count;
  $rows[0][] = $female_count;
  $rows[0][] = $male_count + $female_count;
  $output = "<br/><br/><h2>Totals</h2>".  
    theme('table', array('header' => $header, 'rows' => $rows));

  global $uhelp_recruitment_nids;
  $school_types = array('NA' => 0);
  foreach($uhelp_recruitment_nids as $nid) {
    $node = node_load($nid);
    $school_cid = 
      uhelp_view_headers_get_single_field_value($node,
						'field_recruitment_school', 
						'contact_id');

    if ($school_cid) {
      $result = civicrm_api3('Contact', 'get', array(
						     'sequential' => 1,
						     'return' => "custom_83",
						     'id' => $school_cid,
						     ));
      if ($result && isset($result['values']) && $result['values']) {
	$type = $result['values'][0]['custom_83'];
	$type = $type ? $type : 'NA';
	if (isset($school_types[$type])) {
	  $school_types[$type]++;
	}
	else {
	  $school_types[$type] = 1;
	}
      }
    }
    else {
      $school_types['NA']++;
    }
  }

  $header = array('Type', 'Count');

  $rows = array();
  $counter = 0;
  $total_schools = 0;
  foreach($school_types as $type=>$count) {
    $rows[$counter][] = $type;
    $rows[$counter][] = $count;
    $counter ++;
    $total_schools = $total_schools+$count;
  }
    $rows[$counter][] = "<strong>Total</strong>";
    $rows[$counter][] = "<strong>".$total_schools."<strong>";
 $output .= "<br/><br/><h2>Visits by Secondary School Types</h2>".  
   theme('table', array('header' => $header, 'rows' => $rows));

  return $output;
}


function uhelp_view_headers_get_result_nids($select_less_query, $query_args) {

  $ret = "";
  $query = "";
  $query .= "SELECT node.nid ";
  $query .= $select_less_query;
  
  $results = db_query($query, $query_args);
  
  $is_first = TRUE;
  global $uhelp_recruitment_nids;
  $uhelp_recruitment_nids = array();

  while ($result = $results->fetchObject()) {
    if ($is_first) {
      $is_first = FALSE;
    }
    else {
      $ret .= ", ";
    }
    $ret .= $result->nid;
    $uhelp_recruitment_nids[] = $result->nid;
  }

  return $ret;
}

function uhelp_view_headers_add_grade_view_field($row) {
    $sql = 
      "SELECT grade.field_eval_grade_value, grade.entity_id
       FROM field_data_field_eval_student stu
       INNER JOIN field_data_field_eval_class eval
       ON stu.entity_id = eval.entity_id
       INNER JOIN field_data_field_eval_grade grade
       ON grade.entity_id = eval.entity_id
        WHERE stu.field_eval_student_target_id = ".$row->uid."
       AND eval.field_eval_class_target_id = ".$row->nid; 

    $result = db_query($sql)->fetchObject();

    if (!$result) {
        $link = l(t("Add Grade"), "node/add/course-grade-or-evaluation", 
        array('query'=>array('field_eval_class'=>$row->nid,
        'field_eval_student'=>$row->uid,
        'destination'=>"node/".$row->nid)));
    }
    else {
        $link = l($result->field_eval_grade_value, 
        "node/".$result->entity_id."/edit",
            array('query'=>array('destination'=>"node/".$row->nid)));

    }
    return $link;
}

function uhelp_view_headers_add_grade_sp1_view_field($row) {
    $sql = 
      "SELECT grade.field_eval_grade_value, grade.entity_id
       FROM field_data_field_eval_student stu
       INNER JOIN field_data_field_eval_class eval
       ON stu.entity_id = eval.entity_id
       INNER JOIN field_data_field_eval_grade grade
       ON grade.entity_id = eval.entity_id
        WHERE stu.field_eval_student_target_id = ".$row->uid."
       AND eval.field_eval_class_target_id = ".$row->nid; 

    $result = db_query($sql)->fetchObject();

    if (!$result) {
        $link = l(t("Add Grade"), "node/add/course-grade-or-evaluation", 
        array('query'=>array('field_eval_class'=>$row->nid,
        'field_eval_student'=>$row->uid,
        'destination'=>"node/".$row->nid)));
    }
    else {
        $link = l($result->field_eval_grade_value, 
        "node/".$result->entity_id."/edit",
            array('query'=>array('destination'=>"node/".$row->nid)));

    }
    return $link;
}

function uhelp_view_headers_add_grade_sp2_view_field($row) {
    $sql = 
      "SELECT grade.field_eval_grade_value, grade.entity_id
       FROM field_data_field_eval_student stu
       INNER JOIN field_data_field_eval_class eval
       ON stu.entity_id = eval.entity_id
       INNER JOIN field_data_field_eval_grade grade
       ON grade.entity_id = eval.entity_id
        WHERE stu.field_eval_student_target_id = ".$row->uid."
       AND eval.field_eval_class_target_id = ".$row->nid; 
    
    $result = db_query($sql)->fetchObject();
    $result =  db_query_range($sql,1,1)->fetchObject();
    if (!$result) {
        $link = l(t("Add Grade"), "node/add/course-grade-or-evaluation", 
        array('query'=>array('field_eval_class'=>$row->nid,
        'field_eval_student'=>$row->uid,
        'destination'=>"node/".$row->nid)));
    }
    else {
        $link = l($result->field_eval_grade_value, 
        "node/".$result->entity_id."/edit",
            array('query'=>array('destination'=>"node/".$row->nid)));

    }
    return $link;
}


function uhelp_view_headers_get_alum_overview_contact_getter($alum_cid,$type_of_data) {

  if ($type_of_data == "current_salary") {
  
    $alum_data = "0";
  
    $result = civicrm_api3('Relationship', 'get', array(
      'sequential' => 1,
      'relationship_type_id' => 5,
      'contact_id_a' => $alum_cid,
      'is_active' => 1,
    ));
    if ($result['count'] != 0) {
//    $alum_data["ap_travay"] = "yes";

      $result2 = civicrm_api3('Contact', 'get', array(
      'debug' => 1,
      'sequential' => 1,
      'return' => array("custom_90", "custom_91", "custom_85", "custom_88"),
      'id' => $alum_cid,
//      'custom_85' => $result['values'][0]['contact_id_b'],
    ));
// we will need at some point to convert currencies so we can add and average
// example url for free api
// http://free.currencyconverterapi.com/api/v5/convert?q=HTG_USD&compact=y
//https://free.currencyconverterapi.com/api/v5/convert?q=USD_PHP,PHP_USD&compact=ultra&date=2017-12-31
    $alum_data = $result2;
    }
  return $result2;
  
  }
 
  if ($type_of_data == "degree") { 
      $alum_data = "Undergraduade";
      
      $result = civicrm_api3('Contact', 'get', array(
      'debug' => 1,
      'sequential' => 1,
      'return' => array("custom_92"),
      'id' => $alum_cid,
      'custom_92' => "masters",
      ));
      if ($result['count'] != 0) {
        $alum_data = "Masters";
      }
      $result = civicrm_api3('Contact', 'get', array(
      'debug' => 1,
      'sequential' => 1,
      'return' => array("custom_92"),
      'id' => $alum_cid,
      'custom_92' => "doctorate",
      ));
      if ($result['count'] != 0) {
        $alum_data = "Doctorate";
      }
    
  }    
    
  
  if ($type_of_data == "ap_travay") {
  // is there an active relationship of type 5
//    $alum_data["ap_travay"] = "no";
    $alum_data = "no";
    $result = civicrm_api3('Relationship', 'get', array(
      'sequential' => 1,
      'relationship_type_id' => 5,
      'contact_id_a' => $alum_cid,
      'is_active' => 1,
    ));
    if ($result['count'] != 0) {
//    $alum_data["ap_travay"] = "yes";
    $alum_data = "yes";
    }
  
  }
  
    if ($type_of_data == "employer") {
  // is there an active relationship of type 5
//    $alum_data["ap_travay"] = "no";
    $alum_data = "no employment data";
    $result = civicrm_api3('Relationship', 'get', array(
      'sequential' => 1,
      'relationship_type_id' => 5,
      'contact_id_a' => $alum_cid,
      'start_date' => array('IS NOT NULL' => 1),
      'options' => array('sort' => "start_date"),
    ));
    if ($result['count'] != 0) {
      $which_result = ($result['count'] -1);
      $most_recent_job = $result['values'][$which_result];
      
      $result2 = civicrm_api3('Contact', 'get', array(
      'sequential' => 1,
      'id' => $most_recent_job[contact_id_b],
    ));
      $alum_data=$result2['values'][0]['display_name'];
    
    }
  
  }
  
      if ($type_of_data == "job_title") {
  // is there an active relationship of type 5
//    $alum_data["ap_travay"] = "no";
    $alum_data = " ";
    $result = civicrm_api3('Relationship', 'get', array(
      'sequential' => 1,
      'relationship_type_id' => 5,
      'contact_id_a' => $alum_cid,
      'start_date' => array('IS NOT NULL' => 1),
      'options' => array('sort' => "start_date"),
    ));
    if ($result['count'] != 0) {
      $which_result = ($result['count'] -1);
      $most_recent_job = $result['values'][$which_result];
      $alum_data =$most_recent_job[description];
//    $alum_data["ap_travay"] = "yes";
          
    }
  
  }


    if ($type_of_data == "end_year") {
  // is there an active relationship of type 5
//    $alum_data["ap_travay"] = "no";
    $alum_data = "";
    $result = civicrm_api3('Relationship', 'get', array(
      'sequential' => 1,
      'relationship_type_id' => 50,
      'contact_id_a' => 1,
      'contact_id_b' =>$alum_cid,
//      'is_active' => 1,
    ));

    if ($result['count'] != 0) {
//    $alum_data["ap_travay"] = "yes";
    $alum_data = $result = substr($result[values][0]['end_date'], 0, 4);
    }
  
  }



  if ($type_of_data == "recent_activity") {

    $most_recent_activity_data = array();

    $most_recent_activity_data['meeting']['subject'] = "no data";
    $most_recent_activity_data['meeting']['time'] = "";
        
    $result_meeting = civicrm_api3('Activity', 'get', array(
      'debug' => 1,
      'sequential' => 1,
      'target_contact_id' => $alum_cid,
      'options' => array('sort' => "activity_date_time"),
      'activity_type_id' => "Meeting",
    ));

    if ($result_meeting['count'] != 0) {
      $which_result = ($result_meeting['count'] -1);
      $most_recent_meeting = $result_meeting['values'][$which_result];
    $most_recent_activity_data['meeting']['subject'] = $most_recent_meeting['subject'];
    $most_recent_activity_data['meeting']['time'] = date("M, Y", strtotime($most_recent_meeting['activity_date_time']));
    }
    


    $most_recent_activity_data['phone']['subject'] = "no data";
    $most_recent_activity_data['phone']['time'] = "";
        
    $result_phone = civicrm_api3('Activity', 'get', array(
      'debug' => 1,
      'sequential' => 1,
      'target_contact_id' => $alum_cid,
      'options' => array('sort' => "activity_date_time"),
      'activity_type_id' => "Phone Call",
    ));

    if ($result_phone['count'] != 0) {
      $which_result = ($result_phone['count'] -1);
      $most_recent_phone = $result_phone['values'][$which_result];
    $most_recent_activity_data['phone']['subject'] = $most_recent_phone['subject'];
    $most_recent_activity_data['phone']['time'] = date("M, Y", strtotime($most_recent_phone['activity_date_time']));
    }


    $most_recent_activity_data['event']['subject'] = "no data";
    $most_recent_activity_data['event']['time'] = "";
        
    $result_event = civicrm_api3('Activity', 'get', array(
      'debug' => 1,
      'sequential' => 1,
      'target_contact_id' => $alum_cid,
      'options' => array('sort' => "activity_date_time"),
      'activity_type_id' => "Event Registration",
    ));

    if ($result_event['count'] != 0) {
      $which_result = ($result_event['count'] -1);
      $most_recent_event = $result_event['values'][$which_result];
    $most_recent_activity_data['event']['subject'] = $most_recent_event['subject'];
    $most_recent_activity_data['event']['time'] = date("M, Y", strtotime($most_recent_event['activity_date_time']));
    }

    return $most_recent_activity_data;
  
  }


  if ($type_of_data == "alumni_status") {
  // is there an active relationship of type 5
//    $alum_data["ap_travay"] = "no";
    $alum_data = "";
    $result = civicrm_api3('Contact', 'get', array(
      'debug' => 1,
      'sequential' => 1,
      'tag' => 33,
      'id' => $alum_cid,
    )); 
    if ($result['count'] != 0) {
//    $alum_data["ap_travay"] = "yes";
    $alum_data = "A ";
    }

    $result = civicrm_api3('Contact', 'get', array(
      'debug' => 1,
      'sequential' => 1,
      'tag' => 34,
      'id' => $alum_cid,
    )); 
    if ($result['count'] != 0) {
//    $alum_data["ap_travay"] = "yes";
    $alum_data .= "B ";
    }
  
      $result = civicrm_api3('Contact', 'get', array(
      'debug' => 1,
      'sequential' => 1,
      'tag' => 35,
      'id' => $alum_cid,
    )); 
    if ($result['count'] != 0) {
//    $alum_data["ap_travay"] = "yes";
    $alum_data .= "C ";
    }
  
  
  }
  

  if ($type_of_data == "korem_status") {
  // is there an active relationship of type 5
//    $alum_data["ap_travay"] = "no";
    $alum_data = "";
    $result = civicrm_api3('Contact', 'get', array(
      'debug' => 1,
      'sequential' => 1,
      'tag' => 74,
      'id' => $alum_cid,
    )); 
    if ($result['count'] != 0) {
//    $alum_data["ap_travay"] = "yes";
    $alum_data = "Active KOREMIST ";
    }

    $result = civicrm_api3('Contact', 'get', array(
      'debug' => 1,
      'sequential' => 1,
      'tag' => 75,
      'id' => $alum_cid,
    )); 
    if ($result['count'] != 0) {
//    $alum_data["ap_travay"] = "yes";
    $alum_data .= "Deferred KOREMIST ";
    }
  
      $result = civicrm_api3('Contact', 'get', array(
      'debug' => 1,
      'sequential' => 1,
      'tag' => 73,
      'id' => $alum_cid,
    )); 
    if ($result['count'] != 0) {
//    $alum_data["ap_travay"] = "yes";
    $alum_data .= "Has not started KOREM contributions";
    }
  
  
  }
  
  
  
  if ($type_of_data == "education_status") {
  
    $alum_data = "no";
    $result = civicrm_api3('Relationship', 'get', array(
      'sequential' => 1,
      'relationship_type_id' => 50,
      'contact_id_b' => $alum_cid,
      'is_active' => 1,
    ));
    if ($result['count'] != 0) {
//    $alum_data["ap_travay"] = "yes";
    $alum_data = "yes";
    }
  
  
//  $alum_data["education_status"] = "enrolled";
  
  }
  
  if ($type_of_data == "ap_travay_nan_ayiti") {
 
    $alum_data = "no";
    $result = civicrm_api3('Relationship', 'get', array(
      'sequential' => 1,
      'relationship_type_id' => 5,
      'contact_id_a' => $alum_cid,
      'is_active' => 1,
    ));
    if ($result['count'] != 0) {
//  load employer 
//      dsm($result['values']);
      $employer_cid = $result['values'][0]['contact_id_b'];
      $is_in_haiti = civicrm_api3('Contact', 'get', array(
        'sequential' => 1,
        'id' => $employer_cid,
      ));
    
      if ($is_in_haiti['values'][0]['country_id'] == "1094") {
        $alum_data = "yes";
      }  
    }
   
  
//  $alum_data["working_in_haiti"] = "yes";
  
  
  }
  
  if ($type_of_data == "thesis_status") {
  
    $alum_data = "incomplete"; 
    $result = civicrm_api3('Contact', 'get', array(
      'debug' => 1,
      'sequential' => 1,
      'id' => $alum_cid,
      'tag' => 33,
    ));
    
    if ($result['count'] > 0) {
    $alum_data = "complete"; 
    }
  }

  return $alum_data;
}

function uhelp_view_headers_alumni_overview() {
  $view = views_get_current_view();
  $count_query = $view->build_info['count_query'];
  $count_query_string = $count_query->__toString();

  $select_less_query =substr($count_query_string,
			     strpos($count_query_string, "FROM"));
  $select_less_query =substr($select_less_query, 0, 
			     strpos($select_less_query, "ORDER"));
  $exposed_input = $view->exposed_input;

  $query_args = $count_query->getArguments();
//  dsm($view);
//  dsm($count_query);
  $view->query->limit = 100000;
  
//  dsm($count_query_string);
//   $view = views_get_view($view->vid);
//    $view->build($view->current_display);
  $view->query->set_limit(NULL); // reset the work done by the pager
  $view->query->set_offset(NULL);
  $pager = $view->display_handler->get_option('pager');
  $pager['type'] = 'none';
  $view->display_handler->set_option('pager', $pager);
  $view->query->pager->options['items_per_page'] = 0;
  $view->execute($view);
// dsm($view->result);
  //initialize counters 
  $pa_travay = 0;
  $wi_travay = 0;
  $total_salary = 0;
  $total_with_salary = 0;
  $pa_enrolled = 0;
  $wi_enrolled = 0;
  $wi_ayiti = 0;
  $pa_ayiti = 0;
  $incomplete_thesis = 0;
  $complete_thesis = 0;
  
  foreach ($view->result as $alum) {
//  dsm($alum);
  $ap_travay = uhelp_view_headers_get_alum_overview_contact_getter($alum->id,"ap_travay");
  $current_salary = uhelp_view_headers_get_alum_overview_contact_getter($alum->id,"current_salary");
  $education_status = uhelp_view_headers_get_alum_overview_contact_getter($alum->id,"education_status");
  $ap_travay_nan_ayiti = uhelp_view_headers_get_alum_overview_contact_getter($alum->id,"ap_travay_nan_ayiti");
  $thesis_status = uhelp_view_headers_get_alum_overview_contact_getter($alum->id,"thesis_status");
//   dsm($ap_travay);
   
    if ($ap_travay == "no") {
      $pa_travay++;
    }   
    if ($ap_travay == "yes") {
      $wi_travay++;
    } 
    
//    $total_salary = $total_salary+$current_salary;
    
    
    
    if ($education_status == "no") {
      $pa_enrolled++;
    }   
    if ($education_status == "yes") {
      $wi_enrolled++;
    } 
    
    if ($ap_travay_nan_ayiti == "no") {
      $pa_ayiti++;
    }   
    if ($ap_travay_nan_ayiti == "yes") {
      $wi_ayiti++;
    } 
    
    if ($thesis_status == "incomplete") {
      $incomplete_thesis++;
    }   
    if ($thesis_status == "complete") {
      $complete_thesis++;
    } 
    
//   dsm($current_salary);
    if ($current_salary["values"][0]["custom_90"] > 0) {
      $total_with_salary++;
      $total_salary = intval($total_salary) + intval($current_salary["values"][0]["custom_90"]);
//      dsm($total_salary);
//      dsm($total_with_salary);
    } 

//   dsm($education_status);
//   dsm($ap_travay_nan_ayiti);
//   dsm($thesis_status);
  }
//  dsm($pa_travay);
//  dsm($wi_travay);  
  
  
  
  
  $header = array();
  $rows = array();
  $rows[0] = array();
  $header[] = "completed thesis";
  $header[] = "employed";
  $header[] = "average current salary";
  $header[] = "enrolled in school";
  $header[] = "working in Haiti";
  $header[] = "total alum";
  $rows[0][] = $complete_thesis. " ( ". round(($complete_thesis*100)/$view->total_rows,2)."% )";
  $rows[0][] = $wi_travay. " ( ". round(($wi_travay*100)/$view->total_rows,2)."% )";
  $rows[0][] = "$".round($total_salary/$total_with_salary,2)." ( ".$total_with_salary." alumni with current salary records )";
  $rows[0][] = $wi_enrolled. " ( ". round(($wi_enrolled*100)/$view->total_rows,2)."% )";;
  $rows[0][] = $wi_ayiti. " ( ". round(($wi_ayiti*100)/$view->total_rows,2)."% )";;
  $rows[0][] = $view->total_rows;

  
//  dsm($count_query_string);
//dsm($rows);
  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  return $output;
}

 
