<?php

function reservations_resource_chart_views_default_views() {
  $view = new view();
  $view->name = 'reservations_daily_chart';
  $view->description = '';
  $view->tag = 'reservations';
  $view->base_table = 'node';
  $view->human_name = 'Reservations Resource Chart';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
							       3 => '3',
							       7 => '7',
							       6 => '6',
							       11 => '11',
							       4 => '4',
							       );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
									 'title' => 'title',
									 'name' => 'name',
									 'group_nid' => 'group_nid',
									 'field_reservations_date_value' => 'field_reservations_date_value',
									 'item_nid2' => 'item_nid2',
									 'status' => 'status',
									 'edit_node' => 'edit_node',
									 );
  $handler->display->display_options['style_options']['default'] = 'field_reservations_date_value';
  $handler->display->display_options['style_options']['info'] = array(
								      'title' => array(
										       'sortable' => 0,
										       'separator' => '',
										       ),
								      'name' => array(
										      'sortable' => 1,
										      'separator' => '',
										      ),
								      'group_nid' => array(
											   'separator' => '',
											   ),
								      'field_reservations_date_value' => array(
													       'sortable' => 1,
													       'separator' => '',
													       ),
								      'item_nid2' => array(
											   'separator' => '',
											   ),
								      'status' => array(
											'sortable' => 1,
											'separator' => '',
											),
								      'edit_node' => array(
											   'separator' => '',
											   ),
								      );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'text';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['content'] = '<div class="messages status">No reservations match this criteria</div>';
  $handler->display->display_options['empty']['text']['format'] = 'full_html';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  /* Field: Content: Author uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'node';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'Producer UID';
  /* Field: Content: Reservation Dates */
  $handler->display->display_options['fields']['field_reservations_date']['id'] = 'field_reservations_date';
  $handler->display->display_options['fields']['field_reservations_date']['table'] = 'field_data_field_reservations_date';
  $handler->display->display_options['fields']['field_reservations_date']['field'] = 'field_reservations_date';
  $handler->display->display_options['fields']['field_reservations_date']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_reservations_date']['settings'] = array(
											      'format_type' => 'short',
											      'fromto' => 'both',
											      'multiple_number' => '',
											      'multiple_from' => '',
											      'multiple_to' => '',
											      'show_repeat_rule' => 'show',
											      );
  /* Field: Reservations: Reserved items */
  $handler->display->display_options['fields']['item_nid2']['id'] = 'item_nid2';
  $handler->display->display_options['fields']['item_nid2']['table'] = 'reservations_reservation_detail';
  $handler->display->display_options['fields']['item_nid2']['field'] = 'item_nid2';
  /* Field: Reservations: Reservation status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'reservations_reservation';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Content: Inventory */
  $handler->display->display_options['fields']['field_reservations_inventory']['id'] = 'field_reservations_inventory';
  $handler->display->display_options['fields']['field_reservations_inventory']['table'] = 'field_data_field_reservations_inventory';
  $handler->display->display_options['fields']['field_reservations_inventory']['field'] = 'field_reservations_inventory';
  /* Contextual filter: Content: Reservation Dates -  start date (field_reservations_date) */
  $handler->display->display_options['arguments']['field_reservations_date_value']['id'] = 'field_reservations_date_value';
  $handler->display->display_options['arguments']['field_reservations_date_value']['table'] = 'field_data_field_reservations_date';
  $handler->display->display_options['arguments']['field_reservations_date_value']['field'] = 'field_reservations_date_value';
  $handler->display->display_options['arguments']['field_reservations_date_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_reservations_date_value']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['field_reservations_date_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_reservations_date_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_reservations_date_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_reservations_date_value']['granularity'] = 'day';
  $handler->display->display_options['arguments']['field_reservations_date_value']['granularity_reset'] = 0;
  /* Contextual filter: Content: Inventory (field_reservations_inventory) */
  $handler->display->display_options['arguments']['field_reservations_inventory_tid']['id'] = 'field_reservations_inventory_tid';
  $handler->display->display_options['arguments']['field_reservations_inventory_tid']['table'] = 'field_data_field_reservations_inventory';
  $handler->display->display_options['arguments']['field_reservations_inventory_tid']['field'] = 'field_reservations_inventory_tid';
  $handler->display->display_options['arguments']['field_reservations_inventory_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_reservations_inventory_tid']['default_argument_options']['argument'] = '804';
  $handler->display->display_options['arguments']['field_reservations_inventory_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_reservations_inventory_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_reservations_inventory_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_reservations_inventory_tid']['break_phrase'] = TRUE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
									 'reservations_reservation' => 'reservations_reservation',
									 );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'chart_block');

  // Add view to list of views to provide.
  $views[$view->name] = $view;

  // ...Repeat all of the above for each view the module should provide.

  // At the end, return array of default views.
  return $views;
  
}