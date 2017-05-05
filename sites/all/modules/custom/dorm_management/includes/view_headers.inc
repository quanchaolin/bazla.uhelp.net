<?php 
/**
 * Functions in this include file will provide custom headers for views.
 * The headers will be built by subquerying the results from the view object
 * for sums and averages and what not.
 */


/**
 * builds a report table for the dorm_building_room_assignments
 */
function dorm_management_room_assignments_header() {
  $ret = '';
  $view = views_get_current_view();
  $results = $view->result;

  foreach ($results as $view_data) {

    $node = node_load($view_data->nid);
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

    $total_capacity += $capacity;
    $total_closets += $closets;
    $total_available += $actual_available;
    if ($capacity > 0) {
      $total_bathrooms += $bathrooms;
    }
    if (!$building_has_morebeds) {
      $building_has_morebeds = ($morebeds == 'Yes') ? TRUE : FALSE;
    }
    

  }
  $building_has_morebeds = $building_has_morebeds ? 'Yes' : 'No';
  $ret .=
      "Total Capacity: $total_capacity<br/>".
      "Total Available: $total_available<br/>".
      "Total Bathrooms: $total_bathrooms<br/>".
      "Total Closets: $total_closets<br/>".
      "Any More Beds? $building_has_morebeds<br/><br/>";

  return $ret;
}