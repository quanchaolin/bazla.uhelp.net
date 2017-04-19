<?

/**
 * This is function called from the scheduler view header.
 * If a course nid is in the URL it will display a block of content that
 * will show the suggested scheduler slots for all the students who need to 
 * take the course.
 * At the end it will display links for seeing a suggested schedule for every
 * HELP COURSE
 */
function uhelp_class_scheduler_header() {
  $runtime = strtotime('now'); 
  $academic_term = uhelp_class_scheduler_upcoming_semester();
  $academic_term_name = $academic_term ? $academic_term->name: NULL;
  $academic_term_tid = $academic_term ? $academic_term->tid : NULL;

  $course_nid = arg(2);  
  
  if ($course_nid && is_int((int)$course_nid)) {
    $course = node_load($course_nid);
    $number_of_sessions = 
      uhelp_get_entity_single_value_field($course, 
					  'field_hc_number_of_sessions',
					  'value');

    $max = uhelp_get_entity_single_value_field($course, 
					       'field_hc_maximum_enrollment',
					       'value'); 

    $min = uhelp_get_entity_single_value_field($course, 
					       'field_hc_minium_enrollment',
					       'value'); 
    
    $ideal = uhelp_get_entity_single_value_field($course, 
						 'field_hc_ideal_enrollment',
						 'value'); 

    $length = uhelp_get_entity_single_value_field($course, 
						 'field_hc_session_length',
						 'value'); 

    
    $ret = 
      "<div class='help-scheduler-box'>".
      "<h2><strong>Course: </strong> ". $course->title."</h2>".
      "<h3><strong>Semester: </strong> ". $academic_term_name."</h3>".
      "<h3><strong>Sessions Per Week: </strong> ". $number_of_sessions."</h3>".
        "<h3><strong>Course Length: </strong> ". $length."</h3>".
      "<h3><strong>Minimum Enrollment: </strong> ". $min."</h3>".
      "<h3><strong>Maximum Enrollment: </strong> ". $max."</h3>".
      "<h3><strong>IdealEnrollment: </strong> ". $ideal."</h3>".
      l(t("(Edit Course)"),"node/$course_nid/edit",
	array('query' => array('destination'=>"admin/helpr-class-scheduler/".
			       $course->nid)))."</div>";
  }
  else {
    $course = NULL;
    $ret = "";
  }
  $has_course = (isset($course) && $course) ? TRUE : FALSE;
  if ($has_course) {
    $slot_block = uhelp_class_scheduler_slot_block($course);
    $ret .= $slot_block;
  }
  else {

  }


  $results = db_query("SELECT nid, title FROM node where type='help_course'".
                      " order by nid");
  $content = '';
  while ($course = $results->fetchObject()) {
    $content .= 
      l($course->title, "admin/helpr-class-scheduler/".$course->nid)."<br/>";
  }
  $content .= l(t("See all Students"), "admin/helpr-class-scheduler/")."<br/>";

  $ret .= "<div class='help-scheduler-box'>".
    uhelp_scheduler_collapse_block("<h2>Find Other Course Schedules</h2>", 
				   $content, $has_course).
    "</div>";

  $ret .= "<br/><br/><br/><h2>Raw View Data</h2>";
  drupal_set_message("Execution time in minutes: ".
		     (strtotime('now') - $runtime)/60);

  return $ret;
}


function uhelp_class_scheduler_slot_block($course) {
  $view = views_get_current_view();
  $students = $view->result;

  if (!count($students)) {
    return "<div class='help-scheduler-box'>".
      "<h3>No students to schedule!</h3></div>";
  }
  $max_enrollment_count = 
    uhelp_get_entity_single_value_field($course, 'field_hc_maximum_enrollment',
					'value'); 
  $min_enrollment_count = 
    uhelp_get_entity_single_value_field($course, 'field_hc_minium_enrollment',
					'value'); 

  $ideal_enrollment_count = 
    uhelp_get_entity_single_value_field($course, 'field_hc_ideal_enrollment',
					'value'); 
  
  $ret = "";

  $number_of_sessions = 
    uhelp_get_entity_single_value_field($course, 'field_hc_number_of_sessions',
					'value');
  $days = array('Monday' => array('Wednesday', 'Thursday', 'Friday'), 
		'Tuesday' => array('Thursday', 'Friday'), 
		'Wednesday' => array('Friday'), 
		'Thursday' => array(), 
		'Friday' => array());
  $available_slots = array();
  
  if ($number_of_sessions ==2) {
    foreach ($days as $day=>$followup_days) {
      for ($i=HELP_CLASS_EARLIEST_TIME; $i<=HELP_CLASS_LATEST_TIME; $i++) {
	$time = $i.":00";
	uhelp_scheduler_double_slot_insert($day, $time, $followup_days,
					   $course, $students,  
					   $available_slots);

	$time = $i.":30";
	uhelp_scheduler_double_slot_insert($day, $time, $followup_days,
						$course, $students,  
						$available_slots);

      }
    }//finished goign through all slots
  }
  else {
    foreach ($days as $day=>$followup_days) {
      for ($i=HELP_CLASS_EARLIEST_TIME; $i<=HELP_CLASS_LATEST_TIME; $i++) {
	$time = $i.":00";
	uhelp_scheduler_single_slot_insert($day, $time, $course, $students,
					   $available_slots);
	$time = $i.":30";
	uhelp_scheduler_single_slot_insert($day, $time, $course, $students,
					   $available_slots);

      }
    }
  }

  $slot_counts = array();
  $student_slots = array();
  $student_slot_count = array();
  $slot_students = array();
  $all_slots = array();

  //loop through the avaialbe slots, make sure all students have been 
  //scheduled once.
  $slotted_students = array();
  foreach($available_slots as $day_index=>$day_slots) {
    foreach($day_slots as $time_index=>$time_students) {
      if (strpos($day_index, "|") > 0) {
	$days = explode("|", $day_index);
	$times = explode("|", $time_index);
	$slot_name = $days[0]."--".$times[0]."|".$days[1]."--".$times[1];
      }
      else {
	$slot_name = $day_index."--".$time_index;
      }

      $all_slots[] = $slot_name;

      $slot_counts[$slot_name] = 0;

      foreach($time_students as $student) {
	$slot_counts[$slot_name] ++;
	$slotted_students[] = $student->id;
	$student_slots[$student->id] = isset($student_slots[$student->id]) ?
	  $student_slots[$student->id] : array();
	$student_slots[$student->id][] = $slot_name;

	$student_slot_count[$student->id] = 
	  isset($student_slot_count[$student->id]) ?
	  $student_slot_count[$student->id] : 0;
	$student_slot_count[$student->id] ++;

	$slot_students[$slot_name] = isset($slot_students[$slot_name]) ?
	  $slot_students[$slot_name] : array();
	$slot_students[$slot_name][] = $student->id;
      }
    }
  }

  $_SESSION['UHELP_SCHEDULER_ALL_SLOTS'] = $all_slots;

  $student_ids = array();
  foreach($students as $student) {
    $student_ids[] = $student->id;
  }

  $slotted_students = array_unique($slotted_students);
  $unslotted_students = array_diff($student_ids,$slotted_students);

  arsort($slot_counts);
  asort($student_slot_count);

  if ($unslotted_students) {
    foreach($unslotted_students as $cid) {
      $msg = "Can't schedule a class for cid: $cid";
      drupal_set_message($msg, 'error');
    }
  }

  $counter = 0;
  $removed_slots = array();
  $successes = array();
  $failures = array();

  $max_attempts = count($slot_students);

  drupal_set_message("Found $max_attempts potential slots");
  $max_attempts = 2*$max_attempts;  

  $throttle = HELP_CLASS_SCHEDULE_THROTTLE;

  $max_attempts = $max_attempts < $throttle ? $max_attempts : $throttle;
  drupal_set_message("Filling $max_attempts schedules");

  while ($counter < $max_attempts) {
    $schedule = array();
    $scheduled_students = array();

    uhelp_scheduler_fill_class_for_student($student_slot_count,
					   $slot_counts,
					   $slot_students,
					   $unslotted_students,
					   $scheduled_students,
					   $student_ids,
					   $ideal_enrollment_count,
					   $min_enrollment_count,
					   $max_enrollment_count,
					   $schedule,
					   $student_slot_count,
					   $student_slots
					   );
    
    $unscheduled_students = array_diff($student_ids,$scheduled_students);

    //FIXME #4492 CHECK TO SEE IF WE HAVE MAXIMUM OVERLAPS
    $too_many_overlaps = FALSE;


    if ($counter < count($slot_counts)) {
      reset($schedule);
      $slot_to_move = key($schedule);
      $weight = $counter*-1;
      $slot_counts[$slot_to_move] = $weight;
      arsort($slot_counts);
    }
    else {
      $shuffle_keys = array_keys($slot_counts);
      shuffle($shuffle_keys);

      $tmp_array = array();
      foreach($shuffle_keys as $key) {
	$tmp_array[$key] = $slot_counts[$key];
      }
      $slot_counts = $tmp_array;
    }
  
    if ((count($unscheduled_students) > 0) || $too_many_overlaps) {
      $unsched_array = array();
      foreach ($unscheduled_students as $unsched_cid) {
	$unsched_array[$unsched_cid] = 
	  uhelp_class_scheduler_student_info($unsched_cid);
      }
      $schedule['Unscheduled'] = $unsched_array;
      $failures[] = $schedule;
    }
    else {
      $successes[] = $schedule;
    }
    $counter ++;
  } 
  
  $ret .= uhelp_scheduler_results_block($successes,
				       $failures,
				       $slot_students,
				       $student_slots);

  return $ret;
}

function uhelp_scheduler_results_block($successes,
				       $failures,
				       $slot_students,
				       $student_slots) {
  ctools_add_js('collapsible-div');
  ctools_add_css('collapsible-div');

  $_SESSION['UHELP_SCHEDULER_CACHE'] = array($successes,
					     $failures,
					     $slot_students,
					     $student_slots);
  $ret = '';

  //////////////////////////////////////////////////////////////////////////
  //DISPLAY THE CHART OF THE SUCCESSES
  $rows = array();

  usort($successes, 'uhelp_class_scheduler_schedule_compare');
  $throttle = 100;
  $loop_counter = 0;
  foreach ($successes as $counter => $schedule) {
      $loop_counter++;
      if ($throttle<=$loop_counter) {
          break;
      }
    $row_values = array();
    $row_values[] = array('data'=> "#".($counter+1));
    uksort($schedule, 'uhelp_class_scheduler_slot_compare');

    foreach ($schedule as $slot=>$students) {
      uksort($students, 'uhelp_class_scheduler_student_compare');
      $s_rows = array();
      $cids = array();
      foreach($students as $cid=>$student_data) {
	$cids[] = $cid;
	$student_links = 
	  l($student_data['display_name'], "civicrm/contact/view",
	    array('query'=>array('cid'=>$cid)))." (".
	  l($student_data['username'], "node/38/".$student_data['uid']).")";
	$s_values = array();
	$s_values[] = array('data'=> $student_links);
	$s_rows[] = $s_values;
      }
      $all_slot_students = $slot_students[$slot];
      $list = "";
      foreach ($all_slot_students as $other_cid) {
	if (!in_array($other_cid, $cids)) {
	  $student_data = uhelp_class_scheduler_student_info($other_cid);
	  $list .= "<br/>". 
	  l($student_data['display_name'], "civicrm/contact/view",
	    array('query'=>array('cid'=>$cid)))." (".
	  l($student_data['username'], "node/38/".$student_data['uid']).")";

	}
      }
      $data = uhelp_scheduler_collapse_block("Other Students", $list, TRUE);
      $s_values = array();
      $s_values[] = array('data'=> $data);
      $s_rows[] = $s_values;

      $s_table = theme('table', array('header'=>array(),
				      'rows'=>$s_rows,
				      'attributes'=>array()));
      
      $slot = str_replace('|', '<br/>', $slot);
      $heading = $slot." (".count($students).")";
      $data = uhelp_scheduler_collapse_block($heading, $s_table, TRUE);
      $row_values[] = array('data'=>$data);

      

    }
    $rows[] = $row_values;
  }

  if ($rows) {
    $success_table = theme('table', array('header'=>array(),
					  'rows'=>$rows,
					  'attributes'=>array()));
    $ret .= "<div class='help-scheduler-box'>".
    uhelp_scheduler_collapse_block("<h2>".t("Filled Schedules").
				   " (".count($successes).")</h2>", 
				   $success_table, TRUE)."</div>";
  }
  else {
    $ret .= "<div class='help-scheduler-box'>".
      uhelp_scheduler_collapse_block("<h2>".t("Filled Schedules").
				     " (0)</h2>", "NONE!", TRUE)."</div>";
  }


  //////////////////////////////////////////////////////////////////////////
  //DISPLAY THE CHART OF THE FAILURES
  $rows = array();
  usort($failures, 'uhelp_class_scheduler_schedule_compare');
  $throttle = 100;
  $loop_counter = 0;
  foreach ($failures as $counter => $schedule) {
      $loop_counter++;
      if ($throttle<=$loop_counter) {
          break;
      }
    uksort($schedule, 'uhelp_class_scheduler_slot_compare');
    $row_values = array();
    $row_values[] = array('data'=> "#".($counter+1));
    foreach ($schedule as $slot=>$students) {
      uksort($students, 'uhelp_class_scheduler_student_compare');
      $s_rows = array();
      $cids = array();
      foreach($students as $cid=>$student_data) {
	$cids[] = $cid;
	$student_links = 
	  l($student_data['display_name'], "civicrm/contact/view",
	    array('query'=>array('cid'=>$cid)))." (".
	  l($student_data['username'], "node/38/".$student_data['uid']).")";

	$s_values = array();
	$s_values[] = array('data'=> $student_links);
	$s_rows[] = $s_values;
      }
      $all_slot_students = isset($slot_students[$slot]) ?
	$slot_students[$slot] : array();

      $list = "";
      foreach ($all_slot_students as $other_cid) {
	if (!in_array($other_cid, $cids)) {
	  $student_data = uhelp_class_scheduler_student_info($other_cid);
	  $list .= "<br/>". 
	  l($student_data['display_name'], "civicrm/contact/view",
	    array('query'=>array('cid'=>$other_cid)))." (".
	  l($student_data['username'], "node/38/".$student_data['uid']).")";

	}
      }
      if ($list) {
	$data = uhelp_scheduler_collapse_block("Other Students", $list, TRUE);
	$s_values = array();
	$s_values[] = array('data'=> $data);
	$s_rows[] = $s_values;
      }
      $s_table = "";
      $s_table = theme('table', array('header'=>array(),
				      'rows'=>$s_rows,
				      'attributes'=>array()));
      
      $slot = str_replace('|', '<br/>', $slot);
      $heading = $slot." (".count($students).")";
      $data = uhelp_scheduler_collapse_block($heading, $s_table, TRUE);
      $row_values[] = array('data'=>$data);

      

    }
    $rows[] = $row_values;
  }

  if ($rows) {
    $failure_table = theme('table', array('header'=>array(),
					  'rows'=>$rows,
					  'attributes'=>array()));
    $ret .= "<div class='help-scheduler-box'>".
    uhelp_scheduler_collapse_block("<h2>".t("Unfilled Schedules").
				   " (".count($failures).")</h2>", 
				   $failure_table, TRUE)."</div>";
  }
  else {
    $ret .= "<div class='help-scheduler-box'>".
      uhelp_scheduler_collapse_block("<h2>".t("Unfilled Schedules").
				     " (0)</h2>", "NONE!", TRUE)."</div>";
  }

  //////////////////////////////////////////////////////////////////////////
  //DISPLAY THE CHART OF ALL APPLICABLE STUDENTS
  $content = "";
  uksort($student_slots, 'uhelp_class_scheduler_student_compare');
  foreach ($student_slots as $cid => $slots) {
    $student_data = uhelp_class_scheduler_student_info($cid);
    $student_info = 
      "Name: ".l($student_data['display_name'], "civicrm/contact/view",
		 array('query'=>array('cid'=>$cid)))." ($cid)<br/>".
      "Username:".l($student_data['username'], "node/38/".
		    $student_data['uid']);

    $rows = array();
    foreach ($slots as $slot) {

      $row_values = array();
      $row_values[] = array('data' => $slot);
      $rows[] = $row_values;
    }
    $table = theme('table', array('header'=>array(),
				  'rows'=>$rows,
				  'attributes'=>array()));


    $rows = array();
    global $semester_schedule;

    if (isset($semester_schedule[$cid])) {
        $rows = array();
        foreach ($semester_schedule[$cid] as $schedule_info) {
            $row_values = array();
            $row_data = l($schedule_info['title'], "node/".
            $schedule_info['nid'])."<br />".$schedule_info['start']."-".
            $schedule_info['end']."-".$schedule_info['dow']."-";

            $row_values[] = array('data' => $row_data);
            $rows[] = $row_values;
        }
        $schedule_table = theme('table', array('header'=>array(),
        'rows'=>$rows,
        'attributes'=>array()));

        $student_schedule = 
            uhelp_scheduler_collapse_block("Schedule", $schedule_table);
    }
    else {
        $student_schedule = "";
    }

    
			  

    $content .= "<div class='help-scheduler-box'>".$student_info.
      uhelp_scheduler_collapse_block("Open Slots", $table).
      $student_schedule."</div>";
  }

  $ret .= "<div class='help-scheduler-box'>".
    uhelp_scheduler_collapse_block("<h2>".t("Eligible Students")." (".
				   count($student_slots).")</h2>", 
				   $content)."</div>";

  //////////////////////////////////////////////////////////////////////////
  //DISPLAY THE CHART OF ALL AVAILALBE SLOTS
  $content = "";
  foreach ($slot_students as $slot => $students) {
    $student_links = "";
    $rows = array();
    foreach ($students as $cid) {
      $student_data = uhelp_class_scheduler_student_info($cid);
      $row_values = array();
      $row_values[] = array('data' =>  
			    l($student_data['display_name'], 
			      "civicrm/contact/view",
			      array('query'=>array('cid'=>$cid)))." (".
			    l($student_data['username'], "node/38/".
			      $student_data['uid']).")".
			    "<br/>");
      $rows[] = $row_values;
    }
    $table = theme('table', array('header'=>array(),
				  'rows'=>$rows,
				  'attributes'=>array()));

			  

    $content .= "<div class='help-scheduler-box'>".
      uhelp_scheduler_collapse_block("<div>".$slot." (".
				     count($students).")</div>",
				     $table)."</div>";
  }

  $ret .= "<div class='help-scheduler-box'>".
    uhelp_scheduler_collapse_block("<h2>".t("Available Slots")."</h2>", 
				   $content)."</div>";

  

  
  return $ret;
}

function uhelp_scheduler_collapse_block($heading, $content, $collapse=TRUE) {
  $options = array('handle' => $heading,
                   'content' => $content,
                   'collapsed' => $collapse);
  return "<div>".
    theme('ctools_collapsible',$options)."</div>";
}
/**
 * this function will fill up a schedule by iterating over the set of 
 * student cids who ned to take the course. it will find an available
 * class time for each cid. The class time will be checked to make sure 
 * that enough students can fill the class--the min_enrollment_count on 
 * the course. it will fill it up with up to the ideal amount for the 
 * course
 */
function uhelp_scheduler_fill_class_for_student($student_slot_count,
						$slot_counts,
						$slot_students,
						$unslotted_students,
						&$scheduled_students,
						$student_ids,
						$ideal_enrollment_count,
						$min_enrollment_count,
						$max_enrollment_count,
						&$schedule,
						&$student_slot_count,
						$student_slots){

  foreach($student_slot_count as $cid=>$count) {
    if ($count >= 0 && !in_array($cid, $unslotted_students) &&
	!in_array($cid, $scheduled_students)) {
      
      $potential_slot_students = array($cid => $cid);
    
      //loop through slots with the most popular first
      foreach($slot_counts as $slot => $slot_count) {
	$students = isset($slot_students[$slot]) ? 
	  $slot_students[$slot] : array();
	if (in_array($cid, $students)) {
	  //we have found a potential slot
      
	  //now find other students to add to the slot
	  $unscheduled_students = array_diff($student_ids,$scheduled_students);
	  
	  foreach($unscheduled_students as $inner_cid) {
	    if ($cid != $inner_cid && 
		!in_array($inner_cid, $unslotted_students) &&
		in_array($inner_cid, $slot_students[$slot])) {
	      //we have found another student to add
	      $potential_slot_students[$inner_cid] = $inner_cid;
	      if (count($potential_slot_students) >= $ideal_enrollment_count) {
		break;
	      }
	    }
	  }
	  //we have finished adding the extra students to the slotj
      
	  //if we have enough students for the slot, we add it to scheduled
	  if (count($potential_slot_students) >= $min_enrollment_count) {
	    $schedule[$slot] = isset($schedule[$slot]) ? 
	      $schedule[$slot] : array();
	    foreach($potential_slot_students as $scheduled_cid) {
	      $schedule[$slot][$scheduled_cid] = 
		uhelp_class_scheduler_student_info($scheduled_cid);
	      $scheduled_students[] = $scheduled_cid;
	    }
	    //remove this student from future scheduling
	    unset($slot_students[$slot]);
	    $potential_slot_students = array();
	    break;
	  }
	  else {
	    $potential_slot_students = array();
	  }
	}
      }
    }
  }
  $unscheduled_students = array_diff($student_ids,$scheduled_students);
  foreach ($unscheduled_students as $cid) {
    foreach ($schedule as $slot=>$students) {
      if (isset($student_slots[$cid]) &&
	  in_array($slot, $student_slots[$cid])) {
	$schedule[$slot][$cid] = uhelp_class_scheduler_student_info($cid);
	$scheduled_students[] = $cid;
	break;
      }
    }
  }

}

function uhelp_class_scheduler_student_info($cid) {

  global $student_data;
  
  $student = $student_data[$cid];
  $ret = array(
	       'uid' => $student->users_civicrm_uf_match_uid,
	       'display_name' => $student->civicrm_contact_display_name,
	       'username' => $student->users_civicrm_uf_match_name,
	       );
  return $ret;
  
}
/**
 * This function is called from a php filter on the scheduler view
 * It will find the course from the URL 
 * The student will be filtered unless:
 * 1. the date entered HELP field on student shows them to be a  3rd year 
 * student and the course is ENGLISH SEL, which is for every 3rd year student
 * 2. The Course Level (field_hc_level) is sql to the level field on student 
   (field_it_level or field_english_level or field_leadership_level)
 */
function uhelp_class_scheduler_filter($row) {
  global $course;

  $course_nid = arg(2);
  
  if (!$course_nid || !is_int((int)$course_nid)) {
    return FALSE;
  }
  
  $course = $course ? $course : node_load($course_nid);

  $help_start_date = strtotime($row->helpr_enrollment_date_69);
  $year = ceil((strtotime('now') - $help_start_date) / (365*24*60*60));

  /*
  //SEL classs is a special class, that will always be 3rd year
  if ($course->nid == UHELP_ENGLISH_SEL_CLASS_COURSE_ID) {
      if (!$row->helpr_enrollment_date_69) {
	
	drupal_set_message($row->display_name . " is missing HELP enrollment ".
			   "which is required to schedule for English SEL",
			   'warning');
		return TRUE;
      }
      
    if ($year == 3) {
      return FALSE;
    }
    else {
      return TRUE;
    }
  }
*/
  $user = $row->uid ? user_load($row->uid) : NULL;
  if (!$user) {
    drupal_set_message("Missing User! Error Code 343232", 'error');
    return TRUE;
  }

  $type_tid = 
    uhelp_get_entity_single_value_field($course, 'field_course_type','tid');

  if ($type_tid == UHELP_CLASS_TYPE_ENGLISH_TID) {
    //only english SEL class is for year 3, so if we are year 3 we will skip
    //because SEL is handled above
    if ($year == 3) {
      return TRUE;
    }
    $field = 'field_english_level';    
  }
  else if ($type_tid == UHELP_CLASS_TYPE_LEADERSHIP_TID) {
    $field = 'field_leadership_level';    
  }
  else if ($type_tid == UHELP_CLASS_TYPE_IT_TID) {
    $field = 'field_it_level';    
  }

  if (!$field) {
    return TRUE;
  }

  $student_level = uhelp_get_entity_single_value_field($user, $field, 'tid');
  $course_level = 
    uhelp_get_entity_single_value_field($course, 'field_hc_level', 'tid');

  if ($student_level != $course_level) {
    return TRUE;
  }

  //FIXME 1928: LOOK TO SEE IF STUDENT HAS ALREADY TAKEN THIS COURSE
  return FALSE;
}

function uhelp_class_scheduler_is_student_available($student, $time, 
                                                    $day, $course) {
  //fixme 9838, make real
  $contact_id = $student->id;
  $course_length = uhelp_get_entity_single_value_field($course, 
						       'field_hc_session_length',
						       'value');
  $availability_info = 
    uhelp_class_scheduler_availability_info($course_length);

  global $semester_schedule;

  global $first_time;
 
  //if student has no classes they are availabiel
  if (!isset($availability_info[$contact_id])) {
      return TRUE;
  }

  $first_time = isset($first_time) ? FALSE : TRUE;
  if (FALSE && $first_time) {
    dsm($student, 'student');
    dsm($time, 'time');
    dsm($day, 'day');
    dsm($semester_schedule, 'schedule');
    dsm($course, 'course');
    dsm($course_length, 'course_length');
    dsm($availability_info, 'avail info');
    dsm(in_array($time, $availability_info[$contact_id][$day]));
  }

  return in_array($time, $availability_info[$contact_id][$day]);

  //$chance = 30;
  //return rand(1,100) <= (int)$chance;
}

function uhelp_scheduler_single_slot_insert($day, $time, 
					    $course, $students,
					    &$available_slots) {
  global $student_data;
  $student_data = isset($student_data) ? $student_data : array();

  $min_enrollment_count = 
    uhelp_get_entity_single_value_field($course, 'field_hc_minium_enrollment',
					'value'); 
  foreach ($students as $student) {
      if (uhelp_class_scheduler_is_student_available($student, $time, $day,
      $course)) {

      $available_slots[$day] = isset($available_slots[$day]) ? 
	$available_slots[$day] : array();
      $available_slots[$day][$time] = 
	isset($available_slots[$day][$time]) ? 
	$available_slots[$day][$time] : array();
      $available_slots[$day][$time];
      $available_slots[$day][$time][] = $student;
    }
    $student_data[$student->id] = $student;
  }
  //if we don't have the minimum enrollment for this slot, we remove it
  //from the avaialble slots array
  if (isset($available_slots[$day][$time]) &&
      count($available_slots[$day][$time]) < 
      $min_enrollment_count) {
    unset($available_slots[$day][$time]);
    if (!$available_slots[$day]) {
      unset($available_slots[$day]);
    }
  }
}

function uhelp_scheduler_double_slot_insert($day, $time, $followup_days,
						 $course, $students,  
						 &$available_slots){ 
  global $student_data;
  $student_data = isset($student_data) ? $student_data : array();

  $min_enrollment_count = 
    uhelp_get_entity_single_value_field($course, 'field_hc_minium_enrollment',
					'value'); 
  
  foreach ($followup_days as $followup_day) {
    $day_index = $day."|".$followup_day;
    for ($j=HELP_CLASS_EARLIEST_TIME; $j<=HELP_CLASS_LATEST_TIME; $j++) {
      $followup_time = $j.":00";
      
      foreach ($students as $student) {
	$student_data[$student->id] = $student;
	if (uhelp_class_scheduler_is_student_available($student,
						                           $time,
                                                   $day,
						                           $course) &&
	    uhelp_class_scheduler_is_student_available($student,
                                                   $followup_time,
                                                   $day,
						                           $course)) {
	  $time_index = $time.'|'.$followup_time;
	  $available_slots[$day_index] = isset($available_slots[$day_index]) ? 
	    $available_slots[$day_index] : array();
	  $available_slots[$day_index][$time_index] = 
	    isset($available_slots[$day_index][$time_index]) ? 
	    $available_slots[$day_index][$time_index] : array();
	  $available_slots[$day_index][$time_index];
	  $available_slots[$day_index][$time_index][] = $student;
	}
      }

      //if we don't have the minimum enrollment for this slot, we remove it
      //from the avaialble slots array
      if (isset($time_index) &&
	  isset($available_slots[$day_index][$time_index]) &&
	  count($available_slots[$day_index][$time_index]) < 
	  $min_enrollment_count) {
	unset($available_slots[$day_index][$time_index]);
	if (!$available_slots[$day_index]) {
	  unset($available_slots[$day_index]);
	}
      }
      $followup_time = $j.":30";
      
      foreach ($students as $student) {
	if (uhelp_class_scheduler_is_student_available($student,
                               $time,$day,
						       $course) &&
	    uhelp_class_scheduler_is_student_available($student,
        $followup_time,$day,
						       $course)) {
	  $time_index = $time.'|'.$followup_time;
	  $available_slots[$day_index] = isset($available_slots[$day_index]) ? 
	    $available_slots[$day_index] : array();
	  $available_slots[$day_index][$time_index] = 
	    isset($available_slots[$day_index][$time_index]) ? 
	    $available_slots[$day_index][$time_index] : array();
	  $available_slots[$day_index][$time_index];
	  $available_slots[$day_index][$time_index][] = $student;
	}
      }
      if (isset($available_slots[$day_index][$time_index]) &&
	  count($available_slots[$day_index][$time_index]) < 
	  $min_enrollment_count) {
	unset($available_slots[$day_index][$time_index]);
	if (!$available_slots[$day_index]) {
	  unset($available_slots[$day_index]);
	}
      }
    }
  }
}
function uhelp_class_scheduler_upcoming_semester() {
  $now = strtotime('now');

  $month = date('m', $now);
  $year = date('Y', $now);

  if ($month <= 2) {
    $season = 'Spring';
  }
  else if ($month <= 6) {
    $season = 'Summer';
  }
  else {
    $season = 'Fall';
  }

  $term_name = $season." ".$year;
  $term = taxonomy_get_term_by_name($term_name, 
				    UHELP_ACADEMIC_PERIOD_VOCABULARY_NAME);
  
  if ($term) {
    $term = array_shift($term);
    return $term;
  }
  return NULL;
}
function uhelp_class_scheduler_year_field($row) {
  $help_start_date = strtotime($row->helpr_enrollment_date_69);
  $year = $help_start_date ? 
    ceil((strtotime('now') - $help_start_date) / (365*24*60*60)) : 
    "Missing Enrollment Date!";
  return $year;
}

function uhelp_class_scheduler_slot_compare($a, $b) {
  $all_slots = $_SESSION['UHELP_SCHEDULER_ALL_SLOTS'];
  $slot_rankings = array_flip($all_slots);
  $a_rank = isset($slot_rankings[$a]) ? $slot_rankings[$a] : 0;
  $b_rank = isset($slot_rankings[$b]) ? $slot_rankings[$b] : 0;

  if ($a_rank == $b_rank) {
    return 0;  
  }
  return ($a_rank < $b_rank) ? -1 : 1;
 
}

function uhelp_class_scheduler_schedule_compare($a, $b) {
  $all_slots = $_SESSION['UHELP_SCHEDULER_ALL_SLOTS'];
  $slot_rankings = array_flip($all_slots);

  uksort($a, 'uhelp_class_scheduler_slot_compare');
  foreach ($a as $a_slot=>$a_students) {
    break;
  }
  unset($a[$a_slot]);
  reset($a);

  uksort($b, 'uhelp_class_scheduler_slot_compare');
  foreach ($b as $b_slot=>$b_students) {
    break;
  }
  unset($b[$b_slot]);
  reset($b);
	
  $a_rank = isset($slot_rankings[$a_slot]) ? $slot_rankings[$a_slot] : 0;
  $b_rank = isset($slot_rankings[$b_slot]) ? $slot_rankings[$b_slot] : 0;
	
  if ($a_rank != $b_rank) { 
    return ($a_rank < $b_rank) ? -1 : 1;
  }

  foreach ($a as $a_slot=>$a_students) {
    break;
  }  
  unset($a[$a_slot]);
  reset($a);

  foreach ($b as $b_slot=>$b_students) {
    break;
  }
  unset($b[$b_slot]);
  reset($b);

  $a_rank = isset($slot_rankings[$a_slot]) ? $slot_rankings[$a_slot] : 0;
  $b_rank = isset($slot_rankings[$b_slot]) ? $slot_rankings[$b_slot] : 0;

  if ($a_rank != $b_rank) { 
    return ($a_rank < $b_rank) ? -1 : 1;
  }

  foreach ($a as $a_slot=>$a_students) {
    break;
  }
  unset($a[$a_slot]);
  reset($a);

  foreach ($b as $b_slot=>$b_students) {
    break;
  }
  unset($b[$b_slot]);
  reset($b);

  $a_rank = isset($slot_rankings[$a_slot]) ? $slot_rankings[$a_slot] : 0;
  $b_rank = isset($slot_rankings[$b_slot]) ? $slot_rankings[$b_slot] : 0;

  if ($a_rank != $b_rank) { 
    return ($a_rank < $b_rank) ? -1 : 1;
  }

  foreach ($a as $a_slot=>$a_students) {
    break;
  }
  unset($a[$a_slot]);
  reset($a);
  
  foreach ($b as $b_slot=>$b_students) {
    break;
  }
  unset($b[$b_slot]);
  reset($b);

  $a_rank = isset($slot_rankings[$a_slot]) ? $slot_rankings[$a_slot] : 0;
  $b_rank = isset($slot_rankings[$b_slot]) ? $slot_rankings[$b_slot] : 0;

  if ($a_rank != $b_rank) { 
    return ($a_rank < $b_rank) ? -1 : 1;
  }

  foreach ($a as $a_slot=>$a_students) {
    break;
  }
  unset($a[$a_slot]);
  reset($a);

  foreach ($b as $b_slot=>$b_students) {
    break;
  }
  unset($b[$b_slot]);
  reset($b);

  $a_rank = isset($slot_rankings[$a_slot]) ? $slot_rankings[$a_slot] : 0;
  $b_rank = isset($slot_rankings[$b_slot]) ? $slot_rankings[$b_slot] : 0;

  if ($a_rank != $b_rank) { 
    return ($a_rank < $b_rank) ? -1 : 1;
  }
  return 0;  
}

function uhelp_class_scheduler_student_compare($a, $b) {
  $a_data = uhelp_class_scheduler_student_info($a);
  $b_data = uhelp_class_scheduler_student_info($b);
  $a_name = isset($a_data['display_name']) ? 
    strtolower(trim($a_data['display_name'])) : "";
  $b_name = isset($b_data['display_name']) ? 
    strtolower(trim($b_data['display_name'])) : "";

  if ($a_name == $b_name) {
    return 0;  
  }
  return ($a_name < $b_name) ? -1 : 1;
}

function uhelp_class_scheduler_availability_info($course_length = 1.5) {
 global $student_availability_array;
 global $semester_schedule;

 $buffer = $course_length/.5;

 if (!isset($student_availability_array)) {
   $semester_schedule = isset($semester_schedule) ? 
     $semester_schedule : uhelp_class_scheduler_semester_schedule();

   foreach($semester_schedule as $contact_id=>$schedule) {
     $student_available_slots =
       uhelp_class_scheduler_initial_available_slots();
          
     foreach ($schedule as $class_nid=>$class_info) {
       $dow = $class_info['dow'];
       $length = $class_info['length'];
       $time_parts = explode(":", $class_info['start']);
       $hour = $time_parts[0];
       $minute = $time_parts[1];
       
       //round start time back to nearest half hour
       $minute =  ($minute > 0 && $minute < 30) ? "00" : $minute;
       $minute =  ($minute > 30 && $minute < 60) ? "30" : $minute;

       $start_time = $hour.":".$minute;

       $time_parts = explode(":", $class_info['end']);
       $hour = $time_parts[0];
       $minute = $time_parts[1];
       
       //round start time forward to nearest half hour
       $minute =  ($minute > 0 && $minute < 30) ? "30" : $minute;
       $minute =  ($minute > 30 && $minute < 60) ? "60" : $minute;

       if ($minute == "60") {
	 $minute = "00";
	 $hour ++;
       }

       $end_time = $hour.":".$minute;

       if (in_array($start_time, $student_available_slots[$dow])) {
	 $start_index = 
	   array_search($start_time, $student_available_slots[$dow])+1-$buffer;
	 $start_index = ($start_index < 0) ? 0 : $start_index;

	 $end_index = ceil($length/.5) + $buffer + $start_index;
	 
	 for ($i = $start_index; $i < $end_index; $i++) {
	   if (isset($student_available_slots[$dow]) &&
	       isset($student_available_slots[$dow][$i])) {
	     unset($student_available_slots[$dow][$i]);
	   }
	 }
       }
     }
     $student_availability_array[$contact_id] = $student_available_slots;
   }
 }
 return $student_availability_array;
}
function uhelp_class_scheduler_initial_available_slots() {
  $ret = array();

  $days = array('Monday',
		'Tuesday',
		'Wednesday',
		'Thursday',
		'Friday',
		'Saturday',
		'Sunday');

  foreach($days as $dow) {
    for ($i=0; $i<=23; $i++) {
      $ret[$dow] = isset($ret[$dow]) ? $ret[$dow] : array();
      $time = $i.":00";
      $ret[$dow][] = $time;

      $time = $i.":30";
      $ret[$dow][] = $time;
    }
  }
  return $ret;
}

function uhelp_class_scheduler_semester_schedule() {
  civicrm_initialize();
  global $semester_schedule;
 
  if (!isset($semester_schedule)) {
    $semester_schedule = array();
    $view = views_get_view('class_times');
    $view->execute('block_1'); 
    $results = $view->result;
    //FIXME SET THROTTLE TO A HIGHER NUMBER FOR PRODU CTION
    $throttle = 1000000;
    $counter = 0;
    foreach ($results as $result) {
      $counter++;

      $students = isset($result->field_field_enrolled_students) ?
        $result->field_field_enrolled_students : array();

      //get class timing information
      $schedule_field = $result->field_field_class_schedule[0]['raw'];

      $start_timestamp = strtotime($schedule_field['value']) +
	date('Z',strtotime($schedule_field['value']));

      $end_timestamp = strtotime($schedule_field['value2']) +
	date('Z',strtotime($schedule_field['value2']));

      $start = date('G:i', $start_timestamp);
      $end = date('G:i', $end_timestamp);
      $dow = date('l', $start_timestamp);
      $length = ($end_timestamp - $start_timestamp)/(60*60);
      $class = 
        $result->_field_data['node_field_data_field_class_session_class_nid']
          ['entity'];

      $class_info = array(
          'session_nid' => $result->nid,
              'nid' => $class->nid,
			  'title' => $class->title,
			  'start' => $start, 
			  'end' => $end, 
			  'dow' => $dow,
			  'length' => $length,
			  );

      foreach ($students as $i => $value) {
        $uid = $value['raw']['target_id'];
      
        //get student contact id
        $params = array(
          'version' => 3,
          'sequential' => 1,
          'uf_id' => $uid,
        );
        $api_result = civicrm_api('UFMatch', 'get', $params);
        $contact_id = $api_result['values'][0]['contact_id'];

        //if no student array, create it in $semester_schedule
        $semester_schedule[$contact_id] = 
          isset($semester_schedule[$contact_id]) ?
          $semester_schedule[$contact_id] : array();

        $semester_schedule[$contact_id][$class_info['session_nid']] = 
            $class_info;
        //create array of course info, id, start, end, title, dow
        
      }

      if ($counter >= $throttle) {
        
        break;
      }
    }
  }
  
  return $semester_schedule;
}