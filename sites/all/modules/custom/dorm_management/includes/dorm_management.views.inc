<?php

function dorm_management_views_default_views() {
  ////////////////////////////////////////////////////////////////////////
  //Dorm Admin Contacts
  $view = new view();
  $view->name = 'dorm_admin_contacts';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'civicrm_contact';
  $view->human_name = 'Dorm Admin Contacts';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Dorm Admin Contacts';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: CiviCRM Relationships: Relationship Type A-to-B */
  $handler->display->display_options['fields']['relationship_type']['id'] = 'relationship_type';
  $handler->display->display_options['fields']['relationship_type']['table'] = 'civicrm_relationship';
  $handler->display->display_options['fields']['relationship_type']['field'] = 'relationship_type';
  $handler->display->display_options['fields']['relationship_type']['label'] = '';
  $handler->display->display_options['fields']['relationship_type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['relationship_type']['element_type'] = 'strong';
  $handler->display->display_options['fields']['relationship_type']['element_label_colon'] = FALSE;
  /* Field: CiviCRM Contacts: Contact ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'civicrm_contact';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  /* Field: CiviCRM Contacts: Display Name */
  $handler->display->display_options['fields']['display_name']['id'] = 'display_name';
  $handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
  $handler->display->display_options['fields']['display_name']['field'] = 'display_name';
  $handler->display->display_options['fields']['display_name']['label'] = 'Name';
  $handler->display->display_options['fields']['display_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 1;
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['php']['alter']['text'] = '<strong>[php]:</strong> [display_name]';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
print  dorm_management_relationship_type_transform($row);
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Field: CiviCRM Email: Email Address */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'civicrm_email';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  $handler->display->display_options['fields']['email']['label'] = 'Email';
  $handler->display->display_options['fields']['email']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['email']['location_type'] = '0';
  $handler->display->display_options['fields']['email']['location_op'] = '0';
  $handler->display->display_options['fields']['email']['is_primary'] = 0;
  $handler->display->display_options['fields']['email']['link_to_user'] = '0';
  /* Field: CiviCRM Phone Details: Phone Number */
  $handler->display->display_options['fields']['phone']['id'] = 'phone';
  $handler->display->display_options['fields']['phone']['table'] = 'civicrm_phone';
  $handler->display->display_options['fields']['phone']['field'] = 'phone';
  $handler->display->display_options['fields']['phone']['label'] = 'Phone';
  $handler->display->display_options['fields']['phone']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['phone']['location_type'] = '0';
  $handler->display->display_options['fields']['phone']['location_op'] = '0';
  $handler->display->display_options['fields']['phone']['is_primary'] = 1;
  $handler->display->display_options['fields']['phone']['phone_type'] = '0';
  /* Contextual filter: CiviCRM Relationships: Contact ID B */
  $handler->display->display_options['arguments']['contact_id_b_']['id'] = 'contact_id_b_';
  $handler->display->display_options['arguments']['contact_id_b_']['table'] = 'civicrm_relationship';
  $handler->display->display_options['arguments']['contact_id_b_']['field'] = 'contact_id_b_';
  $handler->display->display_options['arguments']['contact_id_b_']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['contact_id_b_']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['contact_id_b_']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['contact_id_b_']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['contact_id_b_']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: CiviCRM Relationships: Is Relationship Active */
  $handler->display->display_options['filters']['is_active']['id'] = 'is_active';
  $handler->display->display_options['filters']['is_active']['table'] = 'civicrm_relationship';
  $handler->display->display_options['filters']['is_active']['field'] = 'is_active';
  $handler->display->display_options['filters']['is_active']['value'] = '1';
  $handler->display->display_options['filters']['is_active']['group'] = 1;
  /* Filter criterion: Global: PHP */
  $handler->display->display_options['filters']['php']['id'] = 'php';
  $handler->display->display_options['filters']['php']['table'] = 'views';
  $handler->display->display_options['filters']['php']['field'] = 'php';
  $handler->display->display_options['filters']['php']['group'] = 1;
  $handler->display->display_options['filters']['php']['use_php_setup'] = 0;
  $handler->display->display_options['filters']['php']['php_filter'] = 'if (!empty($row->end_date )) {
return TRUE;
}';
  /* Filter criterion: CiviCRM Relationships: Relationship Type A-to-B */
  $handler->display->display_options['filters']['relationship_type']['id'] = 'relationship_type';
  $handler->display->display_options['filters']['relationship_type']['table'] = 'civicrm_relationship';
  $handler->display->display_options['filters']['relationship_type']['field'] = 'relationship_type';
  $handler->display->display_options['filters']['relationship_type']['value'] = array(
										      5 => '5',
										      7 => '7',
										      10 => '10',
										      11 => '11',
										      12 => '12',
										      32 => '32',
										      33 => '33',
										      36 => '36',
										      38 => '38',
										      42 => '42',
										      );

  /* Display: Dorm address */
  $handler = $view->new_display('block', 'Dorm address', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Dorm Address and Details';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: CiviCRM Contacts: Contact ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'civicrm_contact';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  /* Field: CiviCRM Contacts: Display Name */
  $handler->display->display_options['fields']['display_name']['id'] = 'display_name';
  $handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
  $handler->display->display_options['fields']['display_name']['field'] = 'display_name';
  $handler->display->display_options['fields']['display_name']['label'] = '';
  $handler->display->display_options['fields']['display_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['display_name']['alter']['text'] = 'Building Name: [display_name]';
  $handler->display->display_options['fields']['display_name']['element_type'] = 'h3';
  $handler->display->display_options['fields']['display_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 1;
  /* Field: CiviCRM Email: Email Address */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'civicrm_email';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  $handler->display->display_options['fields']['email']['label'] = 'Email';
  $handler->display->display_options['fields']['email']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['email']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['email']['location_type'] = '0';
  $handler->display->display_options['fields']['email']['location_op'] = '0';
  $handler->display->display_options['fields']['email']['is_primary'] = 1;
  $handler->display->display_options['fields']['email']['link_to_user'] = '0';
  /* Field: CiviCRM Phone Details: Phone Number */
  $handler->display->display_options['fields']['phone']['id'] = 'phone';
  $handler->display->display_options['fields']['phone']['table'] = 'civicrm_phone';
  $handler->display->display_options['fields']['phone']['field'] = 'phone';
  $handler->display->display_options['fields']['phone']['label'] = 'Phone';
  $handler->display->display_options['fields']['phone']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['phone']['location_type'] = '0';
  $handler->display->display_options['fields']['phone']['location_op'] = '0';
  $handler->display->display_options['fields']['phone']['is_primary'] = 1;
  $handler->display->display_options['fields']['phone']['phone_type'] = '0';
  /* Field: CiviCRM Address: Full Street Address */
  $handler->display->display_options['fields']['street_address']['id'] = 'street_address';
  $handler->display->display_options['fields']['street_address']['table'] = 'civicrm_address';
  $handler->display->display_options['fields']['street_address']['field'] = 'street_address';
  $handler->display->display_options['fields']['street_address']['label'] = '';
  $handler->display->display_options['fields']['street_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['street_address']['location_type'] = '0';
  $handler->display->display_options['fields']['street_address']['location_op'] = '0';
  $handler->display->display_options['fields']['street_address']['is_primary'] = 0;
  $handler->display->display_options['fields']['street_address']['is_billing'] = 0;
  /* Field: CiviCRM Address: City / Suburb */
  $handler->display->display_options['fields']['city']['id'] = 'city';
  $handler->display->display_options['fields']['city']['table'] = 'civicrm_address';
  $handler->display->display_options['fields']['city']['field'] = 'city';
  $handler->display->display_options['fields']['city']['label'] = '';
  $handler->display->display_options['fields']['city']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['city']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['city']['location_type'] = '0';
  $handler->display->display_options['fields']['city']['location_op'] = '0';
  $handler->display->display_options['fields']['city']['is_primary'] = 0;
  $handler->display->display_options['fields']['city']['is_billing'] = 0;
  /* Field: CiviCRM Address: ZIP / Postal Code */
  $handler->display->display_options['fields']['postal_code']['id'] = 'postal_code';
  $handler->display->display_options['fields']['postal_code']['table'] = 'civicrm_address';
  $handler->display->display_options['fields']['postal_code']['field'] = 'postal_code';
  $handler->display->display_options['fields']['postal_code']['label'] = '';
  $handler->display->display_options['fields']['postal_code']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['postal_code']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['postal_code']['location_type'] = '0';
  $handler->display->display_options['fields']['postal_code']['location_op'] = '0';
  $handler->display->display_options['fields']['postal_code']['is_primary'] = 0;
  $handler->display->display_options['fields']['postal_code']['is_billing'] = 0;
  /* Field: CiviCRM Address: State/Province */
  $handler->display->display_options['fields']['state_province']['id'] = 'state_province';
  $handler->display->display_options['fields']['state_province']['table'] = 'civicrm_address';
  $handler->display->display_options['fields']['state_province']['field'] = 'state_province';
  $handler->display->display_options['fields']['state_province']['label'] = '';
  $handler->display->display_options['fields']['state_province']['exclude'] = TRUE;
  $handler->display->display_options['fields']['state_province']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['state_province']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['state_province']['location_type'] = '0';
  $handler->display->display_options['fields']['state_province']['location_op'] = '0';
  $handler->display->display_options['fields']['state_province']['is_primary'] = 0;
  $handler->display->display_options['fields']['state_province']['is_billing'] = 0;
  /* Field: CiviCRM Address: Country */
  $handler->display->display_options['fields']['country']['id'] = 'country';
  $handler->display->display_options['fields']['country']['table'] = 'civicrm_address';
  $handler->display->display_options['fields']['country']['field'] = 'country';
  $handler->display->display_options['fields']['country']['label'] = '';
  $handler->display->display_options['fields']['country']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['country']['alter']['text'] = '[state_province] [country]';
  $handler->display->display_options['fields']['country']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['country']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['country']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['country']['location_type'] = '0';
  $handler->display->display_options['fields']['country']['location_op'] = '0';
  $handler->display->display_options['fields']['country']['is_primary'] = 0;
  $handler->display->display_options['fields']['country']['is_billing'] = 0;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: CiviCRM Contacts: Contact ID */
  $handler->display->display_options['arguments']['id']['id'] = 'id';
  $handler->display->display_options['arguments']['id']['table'] = 'civicrm_contact';
  $handler->display->display_options['arguments']['id']['field'] = 'id';
  $handler->display->display_options['arguments']['id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  
  // Add view to list of views to provide.
  $views[$view->name] = $view;

  ////////////////////////////////////////////////////////////////////////
  //Dorm Building Room Assignments
  $view = new view();
  $view->name = 'dorm_building_room_assignments';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Dorm Building Room Assignments';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Bed Assignments';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
							       3 => '3',
							       5 => '5',
							       6 => '6',
							       12 => '12',
							       11 => '11',
							       7 => '7',
							       );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
									 'nid' => 'nid',
									 'title' => 'title',
									 'field_dorm_building' => 'field_dorm_building',
									 'field_dorm_room_capacity' => 'field_dorm_room_capacity',
									 'field_dorm_room_gender' => 'field_dorm_room_gender',
									 'field_dorm_room_location' => 'field_dorm_room_location',
									 'field_dorm_room_closets' => 'field_dorm_room_closets',
									 'field_dorm_room_morebeds' => 'field_dorm_room_morebeds',
									 'field_dorm_room_number' => 'field_dorm_room_number',
									 'php' => 'php',
									 );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
								      'nid' => array(
										     'sortable' => 0,
										     'default_sort_order' => 'asc',
										     'align' => '',
										     'separator' => '',
										     'empty_column' => 0,
										     ),
								      'title' => array(
										       'sortable' => 0,
										       'default_sort_order' => 'asc',
										       'align' => '',
										       'separator' => '',
										       'empty_column' => 0,
										       ),
								      'field_dorm_building' => array(
												     'sortable' => 0,
												     'default_sort_order' => 'asc',
												     'align' => '',
												     'separator' => '',
												     'empty_column' => 0,
												     ),
								      'field_dorm_room_capacity' => array(
													  'sortable' => 0,
													  'default_sort_order' => 'asc',
													  'align' => '',
													  'separator' => '',
													  'empty_column' => 0,
													  ),
								      'field_dorm_room_gender' => array(
													'sortable' => 0,
													'default_sort_order' => 'asc',
													'align' => '',
													'separator' => '',
													'empty_column' => 0,
													),
								      'field_dorm_room_location' => array(
													  'sortable' => 0,
													  'default_sort_order' => 'asc',
													  'align' => '',
													  'separator' => '',
													  'empty_column' => 0,
													  ),
								      'field_dorm_room_closets' => array(
													 'sortable' => 0,
													 'default_sort_order' => 'asc',
													 'align' => '',
													 'separator' => '',
													 'empty_column' => 0,
													 ),
								      'field_dorm_room_morebeds' => array(
													  'sortable' => 0,
													  'default_sort_order' => 'asc',
													  'align' => '',
													  'separator' => '',
													  'empty_column' => 0,
													  ),
								      'field_dorm_room_number' => array(
													'sortable' => 0,
													'default_sort_order' => 'asc',
													'align' => '',
													'separator' => '',
													'empty_column' => 0,
													),
								      'php' => array(
										     'align' => '',
										     'separator' => '',
										     'empty_column' => 0,
										     ),
								      );
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_dorm_room_location']['id'] = 'field_dorm_room_location';
  $handler->display->display_options['fields']['field_dorm_room_location']['table'] = 'field_data_field_dorm_room_location';
  $handler->display->display_options['fields']['field_dorm_room_location']['field'] = 'field_dorm_room_location';
  $handler->display->display_options['fields']['field_dorm_room_location']['label'] = '';
  $handler->display->display_options['fields']['field_dorm_room_location']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dorm_room_location']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dorm_room_location']['alter']['text'] = '([field_dorm_room_location])';
  $handler->display->display_options['fields']['field_dorm_room_location']['element_label_colon'] = FALSE;
  /* Field: Content: Room Number */
  $handler->display->display_options['fields']['field_dorm_room_number']['id'] = 'field_dorm_room_number';
  $handler->display->display_options['fields']['field_dorm_room_number']['table'] = 'field_data_field_dorm_room_number';
  $handler->display->display_options['fields']['field_dorm_room_number']['field'] = 'field_dorm_room_number';
  $handler->display->display_options['fields']['field_dorm_room_number']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_dorm_room_number']['alter']['text'] = '<a href="/node/[nid]"><strong>[field_dorm_room_number-value]</strong> [field_dorm_room_location]</a>';
  /* Field: Content: Building */
  $handler->display->display_options['fields']['field_dorm_building']['id'] = 'field_dorm_building';
  $handler->display->display_options['fields']['field_dorm_building']['table'] = 'field_data_field_dorm_building';
  $handler->display->display_options['fields']['field_dorm_building']['field'] = 'field_dorm_building';
  $handler->display->display_options['fields']['field_dorm_building']['label'] = '';
  $handler->display->display_options['fields']['field_dorm_building']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dorm_building']['element_label_colon'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_dorm_room_type']['id'] = 'field_dorm_room_type';
  $handler->display->display_options['fields']['field_dorm_room_type']['table'] = 'field_data_field_dorm_room_type';
  $handler->display->display_options['fields']['field_dorm_room_type']['field'] = 'field_dorm_room_type';
  /* Field: Content: Gender */
  $handler->display->display_options['fields']['field_dorm_room_gender']['id'] = 'field_dorm_room_gender';
  $handler->display->display_options['fields']['field_dorm_room_gender']['table'] = 'field_data_field_dorm_room_gender';
  $handler->display->display_options['fields']['field_dorm_room_gender']['field'] = 'field_dorm_room_gender';
  $handler->display->display_options['fields']['field_dorm_room_gender']['element_label_colon'] = FALSE;
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php_1']['id'] = 'php_1';
  $handler->display->display_options['fields']['php_1']['table'] = 'views';
  $handler->display->display_options['fields']['php_1']['field'] = 'php';
  $handler->display->display_options['fields']['php_1']['label'] = 'Room Info';
  $handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_1']['php_output'] = '<?php
  print dorm_management_room_capacity_numbers($row);
?>';
  $handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Beds';
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
print dorm_management_dorm_student_assignments($row);

?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Sort criterion: Content: Room Number (field_dorm_room_number) */
  $handler->display->display_options['sorts']['field_dorm_room_number_value']['id'] = 'field_dorm_room_number_value';
  $handler->display->display_options['sorts']['field_dorm_room_number_value']['table'] = 'field_data_field_dorm_room_number';
  $handler->display->display_options['sorts']['field_dorm_room_number_value']['field'] = 'field_dorm_room_number_value';
  /* Contextual filter: Content: Building (field_dorm_building) */
  $handler->display->display_options['arguments']['field_dorm_building_contact_id']['id'] = 'field_dorm_building_contact_id';
  $handler->display->display_options['arguments']['field_dorm_building_contact_id']['table'] = 'field_data_field_dorm_building';
  $handler->display->display_options['arguments']['field_dorm_building_contact_id']['field'] = 'field_dorm_building_contact_id';
  $handler->display->display_options['arguments']['field_dorm_building_contact_id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_dorm_building_contact_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_dorm_building_contact_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_dorm_building_contact_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_dorm_building_contact_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
									 'dorm_bed' => 'dorm_bed',
									 );

  /* Display: Dorm Room View Field */
  $handler = $view->new_display('block', 'Dorm Room View Field', 'block_1');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = '';
  $handler->display->display_options['fields']['php']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
print dorm_management_dorm_student_assignments($row);

?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';

  /* Display: Bed For Contact ID */
  $handler = $view->new_display('block', 'Bed For Contact ID', 'block_2');
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Bed Assignments (field_dorm_room_students) */
  $handler->display->display_options['relationships']['field_dorm_room_students_value']['id'] = 'field_dorm_room_students_value';
  $handler->display->display_options['relationships']['field_dorm_room_students_value']['table'] = 'field_data_field_dorm_room_students';
  $handler->display->display_options['relationships']['field_dorm_room_students_value']['field'] = 'field_dorm_room_students_value';
  $handler->display->display_options['relationships']['field_dorm_room_students_value']['delta'] = '-1';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Building */
  $handler->display->display_options['fields']['field_dorm_building']['id'] = 'field_dorm_building';
  $handler->display->display_options['fields']['field_dorm_building']['table'] = 'field_data_field_dorm_building';
  $handler->display->display_options['fields']['field_dorm_building']['field'] = 'field_dorm_building';
  $handler->display->display_options['fields']['field_dorm_building']['label'] = '';
  $handler->display->display_options['fields']['field_dorm_building']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dorm_building']['element_label_colon'] = FALSE;
  /* Field: Field collection item: Student */
  $handler->display->display_options['fields']['field_dorm_studentcontact']['id'] = 'field_dorm_studentcontact';
  $handler->display->display_options['fields']['field_dorm_studentcontact']['table'] = 'field_data_field_dorm_studentcontact';
  $handler->display->display_options['fields']['field_dorm_studentcontact']['field'] = 'field_dorm_studentcontact';
  $handler->display->display_options['fields']['field_dorm_studentcontact']['relationship'] = 'field_dorm_room_students_value';
  $handler->display->display_options['fields']['field_dorm_studentcontact']['label'] = 'Bed';
  /* Field: Field collection item: Bed # */
  $handler->display->display_options['fields']['field_dorm_students_bed_number']['id'] = 'field_dorm_students_bed_number';
  $handler->display->display_options['fields']['field_dorm_students_bed_number']['table'] = 'field_data_field_dorm_students_bed_number';
  $handler->display->display_options['fields']['field_dorm_students_bed_number']['field'] = 'field_dorm_students_bed_number';
  $handler->display->display_options['fields']['field_dorm_students_bed_number']['relationship'] = 'field_dorm_room_students_value';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Field collection item: Student (field_dorm_studentcontact) */
  $handler->display->display_options['arguments']['field_dorm_studentcontact_contact_id']['id'] = 'field_dorm_studentcontact_contact_id';
  $handler->display->display_options['arguments']['field_dorm_studentcontact_contact_id']['table'] = 'field_data_field_dorm_studentcontact';
  $handler->display->display_options['arguments']['field_dorm_studentcontact_contact_id']['field'] = 'field_dorm_studentcontact_contact_id';
  $handler->display->display_options['arguments']['field_dorm_studentcontact_contact_id']['relationship'] = 'field_dorm_room_students_value';
  $handler->display->display_options['arguments']['field_dorm_studentcontact_contact_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_dorm_studentcontact_contact_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_dorm_studentcontact_contact_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_dorm_studentcontact_contact_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_dorm_studentcontact_contact_id']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Content: Building (field_dorm_building) */
  $handler->display->display_options['arguments']['field_dorm_building_contact_id']['id'] = 'field_dorm_building_contact_id';
  $handler->display->display_options['arguments']['field_dorm_building_contact_id']['table'] = 'field_data_field_dorm_building';
  $handler->display->display_options['arguments']['field_dorm_building_contact_id']['field'] = 'field_dorm_building_contact_id';
  $handler->display->display_options['arguments']['field_dorm_building_contact_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_dorm_building_contact_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_dorm_building_contact_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_dorm_building_contact_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_dorm_building_contact_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
									 'dorm_bed' => 'dorm_bed',
									 );
  
  // Add view to list of views to provide.
  $views[$view->name] = $view;


  ////////////////////////////////////////////////////////////////////////
  //Dorm Room Search
  $view = new view();
  $view->name = 'dorm_room_search';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Dorm Room Search';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Dorm Room Search';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
							       3 => '3',
							       5 => '5',
							       6 => '6',
							       12 => '12',
							       11 => '11',
							       7 => '7',
							       4 => '4',
							       );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Content: Building (field_dorm_building) */
  $handler->display->display_options['relationships']['field_dorm_building_contact_id']['id'] = 'field_dorm_building_contact_id';
  $handler->display->display_options['relationships']['field_dorm_building_contact_id']['table'] = 'field_data_field_dorm_building';
  $handler->display->display_options['relationships']['field_dorm_building_contact_id']['field'] = 'field_dorm_building_contact_id';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Building */
  $handler->display->display_options['fields']['field_dorm_building']['id'] = 'field_dorm_building';
  $handler->display->display_options['fields']['field_dorm_building']['table'] = 'field_data_field_dorm_building';
  $handler->display->display_options['fields']['field_dorm_building']['field'] = 'field_dorm_building';
  /* Field: Content: Room Number */
  $handler->display->display_options['fields']['field_dorm_room_number']['id'] = 'field_dorm_room_number';
  $handler->display->display_options['fields']['field_dorm_room_number']['table'] = 'field_data_field_dorm_room_number';
  $handler->display->display_options['fields']['field_dorm_room_number']['field'] = 'field_dorm_room_number';
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_dorm_room_location']['id'] = 'field_dorm_room_location';
  $handler->display->display_options['fields']['field_dorm_room_location']['table'] = 'field_data_field_dorm_room_location';
  $handler->display->display_options['fields']['field_dorm_room_location']['field'] = 'field_dorm_room_location';
  /* Field: Content: Gender */
  $handler->display->display_options['fields']['field_dorm_room_gender']['id'] = 'field_dorm_room_gender';
  $handler->display->display_options['fields']['field_dorm_room_gender']['table'] = 'field_data_field_dorm_room_gender';
  $handler->display->display_options['fields']['field_dorm_room_gender']['field'] = 'field_dorm_room_gender';
  /* Field: Content: Capacity */
  $handler->display->display_options['fields']['field_dorm_room_capacity']['id'] = 'field_dorm_room_capacity';
  $handler->display->display_options['fields']['field_dorm_room_capacity']['table'] = 'field_data_field_dorm_room_capacity';
  $handler->display->display_options['fields']['field_dorm_room_capacity']['field'] = 'field_dorm_room_capacity';
  $handler->display->display_options['fields']['field_dorm_room_capacity']['settings'] = array(
											       'thousand_separator' => ' ',
											       'prefix_suffix' => 1,
											       );
  /* Field: Content: Available Beds */
  $handler->display->display_options['fields']['field_cmptd_available_beds']['id'] = 'field_cmptd_available_beds';
  $handler->display->display_options['fields']['field_cmptd_available_beds']['table'] = 'field_data_field_cmptd_available_beds';
  $handler->display->display_options['fields']['field_cmptd_available_beds']['field'] = 'field_cmptd_available_beds';
  /* Field: Content: Potential for Additional Beds */
  $handler->display->display_options['fields']['field_dorm_room_morebeds']['id'] = 'field_dorm_room_morebeds';
  $handler->display->display_options['fields']['field_dorm_room_morebeds']['table'] = 'field_data_field_dorm_room_morebeds';
  $handler->display->display_options['fields']['field_dorm_room_morebeds']['field'] = 'field_dorm_room_morebeds';
  /* Field: Content: Number of Closets */
  $handler->display->display_options['fields']['field_dorm_room_closets']['id'] = 'field_dorm_room_closets';
  $handler->display->display_options['fields']['field_dorm_room_closets']['table'] = 'field_data_field_dorm_room_closets';
  $handler->display->display_options['fields']['field_dorm_room_closets']['field'] = 'field_dorm_room_closets';
  $handler->display->display_options['fields']['field_dorm_room_closets']['settings'] = array(
											      'thousand_separator' => ' ',
											      'prefix_suffix' => 1,
											      );
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Bed Assignments';
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
print dorm_management_dorm_student_assignments($row);
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Building';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
											     2 => '2',
											     1 => 0,
											     3 => 0,
											     4 => 0,
											     5 => 0,
											     6 => 0,
											     7 => 0,
											     8 => 0,
											     9 => 0,
											     10 => 0,
											     11 => 0,
											     );
  $handler->display->display_options['filters']['title']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_field'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_dependent'] = 0;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
									 'dorm_bed' => 'dorm_bed',
									 );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Available Beds (field_cmptd_available_beds) */
  $handler->display->display_options['filters']['field_cmptd_available_beds_value']['id'] = 'field_cmptd_available_beds_value';
  $handler->display->display_options['filters']['field_cmptd_available_beds_value']['table'] = 'field_data_field_cmptd_available_beds';
  $handler->display->display_options['filters']['field_cmptd_available_beds_value']['field'] = 'field_cmptd_available_beds_value';
  $handler->display->display_options['filters']['field_cmptd_available_beds_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_cmptd_available_beds_value']['group'] = 1;
  $handler->display->display_options['filters']['field_cmptd_available_beds_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_cmptd_available_beds_value']['expose']['operator_id'] = 'field_cmptd_available_beds_value_op';
  $handler->display->display_options['filters']['field_cmptd_available_beds_value']['expose']['label'] = 'Minimum Number of Available Beds';
  $handler->display->display_options['filters']['field_cmptd_available_beds_value']['expose']['operator'] = 'field_cmptd_available_beds_value_op';
  $handler->display->display_options['filters']['field_cmptd_available_beds_value']['expose']['identifier'] = 'field_cmptd_available_beds_value';
  $handler->display->display_options['filters']['field_cmptd_available_beds_value']['expose']['remember_roles'] = array(
															2 => '2',
															1 => 0,
															3 => 0,
															4 => 0,
															5 => 0,
															6 => 0,
															7 => 0,
															8 => 0,
															9 => 0,
															10 => 0,
															11 => 0,
															);
  /* Filter criterion: Content: Capacity (field_dorm_room_capacity) */
  $handler->display->display_options['filters']['field_dorm_room_capacity_value']['id'] = 'field_dorm_room_capacity_value';
  $handler->display->display_options['filters']['field_dorm_room_capacity_value']['table'] = 'field_data_field_dorm_room_capacity';
  $handler->display->display_options['filters']['field_dorm_room_capacity_value']['field'] = 'field_dorm_room_capacity_value';
  $handler->display->display_options['filters']['field_dorm_room_capacity_value']['group'] = 1;
  $handler->display->display_options['filters']['field_dorm_room_capacity_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_dorm_room_capacity_value']['expose']['operator_id'] = 'field_dorm_room_capacity_value_op';
  $handler->display->display_options['filters']['field_dorm_room_capacity_value']['expose']['label'] = 'Capacity';
  $handler->display->display_options['filters']['field_dorm_room_capacity_value']['expose']['operator'] = 'field_dorm_room_capacity_value_op';
  $handler->display->display_options['filters']['field_dorm_room_capacity_value']['expose']['identifier'] = 'field_dorm_room_capacity_value';
  $handler->display->display_options['filters']['field_dorm_room_capacity_value']['expose']['remember_roles'] = array(
														      2 => '2',
														      1 => 0,
														      3 => 0,
														      4 => 0,
														      5 => 0,
														      6 => 0,
														      7 => 0,
														      8 => 0,
														      9 => 0,
														      10 => 0,
														      11 => 0,
														      );
  /* Filter criterion: Content: Gender (field_dorm_room_gender) */
  $handler->display->display_options['filters']['field_dorm_room_gender_value']['id'] = 'field_dorm_room_gender_value';
  $handler->display->display_options['filters']['field_dorm_room_gender_value']['table'] = 'field_data_field_dorm_room_gender';
  $handler->display->display_options['filters']['field_dorm_room_gender_value']['field'] = 'field_dorm_room_gender_value';
  $handler->display->display_options['filters']['field_dorm_room_gender_value']['group'] = 1;
  $handler->display->display_options['filters']['field_dorm_room_gender_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_dorm_room_gender_value']['expose']['operator_id'] = 'field_dorm_room_gender_value_op';
  $handler->display->display_options['filters']['field_dorm_room_gender_value']['expose']['label'] = 'Gender';
  $handler->display->display_options['filters']['field_dorm_room_gender_value']['expose']['operator'] = 'field_dorm_room_gender_value_op';
  $handler->display->display_options['filters']['field_dorm_room_gender_value']['expose']['identifier'] = 'field_dorm_room_gender_value';
  $handler->display->display_options['filters']['field_dorm_room_gender_value']['expose']['remember_roles'] = array(
														    2 => '2',
														    1 => 0,
														    3 => 0,
														    4 => 0,
														    5 => 0,
														    6 => 0,
														    7 => 0,
														    8 => 0,
														    9 => 0,
														    10 => 0,
														    11 => 0,
														    );
  /* Filter criterion: Content: Potential for Additional Beds (field_dorm_room_morebeds) */
  $handler->display->display_options['filters']['field_dorm_room_morebeds_value']['id'] = 'field_dorm_room_morebeds_value';
  $handler->display->display_options['filters']['field_dorm_room_morebeds_value']['table'] = 'field_data_field_dorm_room_morebeds';
  $handler->display->display_options['filters']['field_dorm_room_morebeds_value']['field'] = 'field_dorm_room_morebeds_value';
  $handler->display->display_options['filters']['field_dorm_room_morebeds_value']['group'] = 1;
  $handler->display->display_options['filters']['field_dorm_room_morebeds_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_dorm_room_morebeds_value']['expose']['operator_id'] = 'field_dorm_room_morebeds_value_op';
  $handler->display->display_options['filters']['field_dorm_room_morebeds_value']['expose']['label'] = 'Potential for Additional Beds?';
  $handler->display->display_options['filters']['field_dorm_room_morebeds_value']['expose']['operator'] = 'field_dorm_room_morebeds_value_op';
  $handler->display->display_options['filters']['field_dorm_room_morebeds_value']['expose']['identifier'] = 'field_dorm_room_morebeds_value';
  $handler->display->display_options['filters']['field_dorm_room_morebeds_value']['expose']['remember_roles'] = array(
														      2 => '2',
														      1 => 0,
														      3 => 0,
														      4 => 0,
														      5 => 0,
														      6 => 0,
														      7 => 0,
														      8 => 0,
														      9 => 0,
														      10 => 0,
														      11 => 0,
														      );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
									  0 => array(
										     'field' => 'field_dorm_building',
										     'rendered' => 1,
										     'rendered_strip' => 0,
										     ),
									  );
  $handler->display->display_options['style_options']['columns'] = array(
									 'nid' => 'nid',
									 'title' => 'title',
									 'field_dorm_building' => 'field_dorm_building',
									 'field_dorm_room_number' => 'field_dorm_room_number',
									 'field_dorm_room_location' => 'field_dorm_room_location',
									 'field_dorm_room_type' => 'field_dorm_room_type',
									 'field_dorm_room_gender' => 'field_dorm_room_gender',
									 'php_1' => 'php_1',
									 'php' => 'php',
									 );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
								      'nid' => array(
										     'sortable' => 0,
										     'default_sort_order' => 'asc',
										     'align' => '',
										     'separator' => '',
										     'empty_column' => 0,
										     ),
								      'title' => array(
										       'sortable' => 0,
										       'default_sort_order' => 'asc',
										       'align' => '',
										       'separator' => '',
										       'empty_column' => 0,
										       ),
								      'field_dorm_building' => array(
												     'sortable' => 0,
												     'default_sort_order' => 'asc',
												     'align' => '',
												     'separator' => '',
												     'empty_column' => 0,
												     ),
								      'field_dorm_room_number' => array(
													'sortable' => 0,
													'default_sort_order' => 'asc',
													'align' => '',
													'separator' => '',
													'empty_column' => 0,
													),
								      'field_dorm_room_location' => array(
													  'sortable' => 0,
													  'default_sort_order' => 'asc',
													  'align' => '',
													  'separator' => '',
													  'empty_column' => 0,
													  ),
								      'field_dorm_room_type' => array(
												      'sortable' => 0,
												      'default_sort_order' => 'asc',
												      'align' => '',
												      'separator' => '',
												      'empty_column' => 0,
												      ),
								      'field_dorm_room_gender' => array(
													'sortable' => 0,
													'default_sort_order' => 'asc',
													'align' => '',
													'separator' => '',
													'empty_column' => 0,
													),
								      'php_1' => array(
										       'align' => '',
										       'separator' => '',
										       'empty_column' => 0,
										       ),
								      'php' => array(
										     'align' => '',
										     'separator' => '',
										     'empty_column' => 0,
										     ),
								      );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: CiviCRM Address: Contact ID */
  $handler->display->display_options['fields']['contact_id']['id'] = 'contact_id';
  $handler->display->display_options['fields']['contact_id']['table'] = 'civicrm_address';
  $handler->display->display_options['fields']['contact_id']['field'] = 'contact_id';
  $handler->display->display_options['fields']['contact_id']['relationship'] = 'field_dorm_building_contact_id';
  $handler->display->display_options['fields']['contact_id']['label'] = '';
  $handler->display->display_options['fields']['contact_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['contact_id']['element_label_colon'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Building: Room Number';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Building */
  $handler->display->display_options['fields']['field_dorm_building']['id'] = 'field_dorm_building';
  $handler->display->display_options['fields']['field_dorm_building']['table'] = 'field_data_field_dorm_building';
  $handler->display->display_options['fields']['field_dorm_building']['field'] = 'field_dorm_building';
  $handler->display->display_options['fields']['field_dorm_building']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_dorm_building']['alter']['path'] = 'node/37/[contact_id]';
  $handler->display->display_options['fields']['field_dorm_building']['type'] = 'civicrm_contact_ref_plain';
  /* Field: Content: Room Number */
  $handler->display->display_options['fields']['field_dorm_room_number']['id'] = 'field_dorm_room_number';
  $handler->display->display_options['fields']['field_dorm_room_number']['table'] = 'field_data_field_dorm_room_number';
  $handler->display->display_options['fields']['field_dorm_room_number']['field'] = 'field_dorm_room_number';
  $handler->display->display_options['fields']['field_dorm_room_number']['exclude'] = TRUE;
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_dorm_room_location']['id'] = 'field_dorm_room_location';
  $handler->display->display_options['fields']['field_dorm_room_location']['table'] = 'field_data_field_dorm_room_location';
  $handler->display->display_options['fields']['field_dorm_room_location']['field'] = 'field_dorm_room_location';
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_dorm_room_type']['id'] = 'field_dorm_room_type';
  $handler->display->display_options['fields']['field_dorm_room_type']['table'] = 'field_data_field_dorm_room_type';
  $handler->display->display_options['fields']['field_dorm_room_type']['field'] = 'field_dorm_room_type';
  /* Field: Content: Gender */
  $handler->display->display_options['fields']['field_dorm_room_gender']['id'] = 'field_dorm_room_gender';
  $handler->display->display_options['fields']['field_dorm_room_gender']['table'] = 'field_data_field_dorm_room_gender';
  $handler->display->display_options['fields']['field_dorm_room_gender']['field'] = 'field_dorm_room_gender';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php_1']['id'] = 'php_1';
  $handler->display->display_options['fields']['php_1']['table'] = 'views';
  $handler->display->display_options['fields']['php_1']['field'] = 'php';
  $handler->display->display_options['fields']['php_1']['label'] = 'Room Info';
  $handler->display->display_options['fields']['php_1']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php_1']['php_output'] = '<?php
print dorm_management_room_capacity_numbers($row);
?>';
  $handler->display->display_options['fields']['php_1']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php_1']['php_click_sortable'] = '';
  /* Field: Global: PHP */
  $handler->display->display_options['fields']['php']['id'] = 'php';
  $handler->display->display_options['fields']['php']['table'] = 'views';
  $handler->display->display_options['fields']['php']['field'] = 'php';
  $handler->display->display_options['fields']['php']['label'] = 'Bed Assignments';
  $handler->display->display_options['fields']['php']['use_php_setup'] = 0;
  $handler->display->display_options['fields']['php']['php_output'] = '<?php
print dorm_management_dorm_student_assignments($row);
?>';
  $handler->display->display_options['fields']['php']['use_php_click_sortable'] = '0';
  $handler->display->display_options['fields']['php']['php_click_sortable'] = '';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Building (field_dorm_building) */
  $handler->display->display_options['sorts']['field_dorm_building_contact_id']['id'] = 'field_dorm_building_contact_id';
  $handler->display->display_options['sorts']['field_dorm_building_contact_id']['table'] = 'field_data_field_dorm_building';
  $handler->display->display_options['sorts']['field_dorm_building_contact_id']['field'] = 'field_dorm_building_contact_id';
  /* Sort criterion: Content: Room Number (field_dorm_room_number) */
  $handler->display->display_options['sorts']['field_dorm_room_number_value']['id'] = 'field_dorm_room_number_value';
  $handler->display->display_options['sorts']['field_dorm_room_number_value']['table'] = 'field_data_field_dorm_room_number';
  $handler->display->display_options['sorts']['field_dorm_room_number_value']['field'] = 'field_dorm_room_number_value';
  $handler->display->display_options['path'] = 'dorms/search';
  

  // Add view to list of views to provide.
  $views[$view->name] = $view;

  // ...Repeat all of the above for each view the module should provide.

  // At the end, return array of default views.
  return $views;

}
