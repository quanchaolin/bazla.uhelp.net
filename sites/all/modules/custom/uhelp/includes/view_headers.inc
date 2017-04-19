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


function uhelp_view_headers_get_result_nids(
  $select_less_query, $query_args) {

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
