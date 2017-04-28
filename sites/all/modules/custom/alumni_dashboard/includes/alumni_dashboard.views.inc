<?php

function alumni_dashboard_views_default_views() {
  ////////////////////////////////////////////////////////////////////////
  //ALUMNI AVAILABLE JOBS
  $view = new view();
  $view->name = 'alumni_available_jobs';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Alumni Available Jobs';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Alumni Available Jobs';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
									 'title' => 'title',
									 'field_internship_applicatn_dates' => 'field_internship_applicatn_dates',
									 'body' => 'body',
									 );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
								      'title' => array(
										       'sortable' => 0,
										       'default_sort_order' => 'asc',
										       'align' => '',
										       'separator' => '',
										       'empty_column' => 0,
										       ),
								      'field_internship_applicatn_dates' => array(
														  'sortable' => 0,
														  'default_sort_order' => 'asc',
														  'align' => '',
														  'separator' => '',
														  'empty_column' => 0,
														  ),
								      'body' => array(
										      'sortable' => 0,
										      'default_sort_order' => 'asc',
										      'align' => '',
										      'separator' => '',
										      'empty_column' => 0,
										      ),
								      );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Application Dates */
  $handler->display->display_options['fields']['field_internship_applicatn_dates']['id'] = 'field_internship_applicatn_dates';
  $handler->display->display_options['fields']['field_internship_applicatn_dates']['table'] = 'field_data_field_internship_applicatn_dates';
  $handler->display->display_options['fields']['field_internship_applicatn_dates']['field'] = 'field_internship_applicatn_dates';
  $handler->display->display_options['fields']['field_internship_applicatn_dates']['settings'] = array(
												       'format_type' => 'short',
												       'fromto' => 'both',
												       'multiple_number' => '',
												       'multiple_from' => '',
												       'multiple_to' => '',
												       'show_repeat_rule' => 'show',
												       );
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'Description';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
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
									 'internship' => 'internship',
									 );
  /* Filter criterion: Content: Type (field_int_emp_type) */
  $handler->display->display_options['filters']['field_int_emp_type_value']['id'] = 'field_int_emp_type_value';
  $handler->display->display_options['filters']['field_int_emp_type_value']['table'] = 'field_data_field_int_emp_type';
  $handler->display->display_options['filters']['field_int_emp_type_value']['field'] = 'field_int_emp_type_value';
  $handler->display->display_options['filters']['field_int_emp_type_value']['value'] = array(
											     'full-time' => 'full-time',
											     'part-time' => 'part-time',
											     );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'dashboard/alumni/available-jobs';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Available Jobs';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  
  // Add view to list of views to provide.
  $views[$view->name] = $view;

  ////////////////////////////////////////////////////////////////////////
  //ALUMNI MILESTONES
  $view = new view();
  $view->name = 'alumni_milestones';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'civicrm_contact';
  $view->human_name = 'Alumni MIlestones';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Achievements and MIlestones';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Footer: Global: Unfiltered text */
  $handler->display->display_options['footer']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['footer']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['content'] = 'Add and Update your <a href="/dashboard/alumni/milestones?destination=dashboard/alumni">Achievements and Milestones!</a>';
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'Add your <a href="dashboard/alumni/milestones?destination=dashboard/alumni">Achievements and Milestones!</a>';
  /* Relationship: CiviCRM Contacts: Drupal ID */
  $handler->display->display_options['relationships']['drupal_id']['id'] = 'drupal_id';
  $handler->display->display_options['relationships']['drupal_id']['table'] = 'civicrm_contact';
  $handler->display->display_options['relationships']['drupal_id']['field'] = 'drupal_id';
  $handler->display->display_options['relationships']['drupal_id']['required'] = TRUE;
  /* Field: CiviCRM Contacts: Contact ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'civicrm_contact';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: CiviCRM Custom: Life/Civic Milestones: Milestone */
  $handler->display->display_options['fields']['milestone_92']['id'] = 'milestone_92';
  $handler->display->display_options['fields']['milestone_92']['table'] = 'civicrm_value_life_civic_milestones_27';
  $handler->display->display_options['fields']['milestone_92']['field'] = 'milestone_92';
  /* Field: CiviCRM Custom: Life/Civic Milestones: Details */
  $handler->display->display_options['fields']['details_94']['id'] = 'details_94';
  $handler->display->display_options['fields']['details_94']['table'] = 'civicrm_value_life_civic_milestones_27';
  $handler->display->display_options['fields']['details_94']['field'] = 'details_94';
  /* Field: CiviCRM Custom: Life/Civic Milestones: Date */
  $handler->display->display_options['fields']['date_93']['id'] = 'date_93';
  $handler->display->display_options['fields']['date_93']['table'] = 'civicrm_value_life_civic_milestones_27';
  $handler->display->display_options['fields']['date_93']['field'] = 'date_93';
  $handler->display->display_options['fields']['date_93']['date_format'] = 'custom';
  $handler->display->display_options['fields']['date_93']['custom_date_format'] = 'd M Y';
  /* Sort criterion: CiviCRM Custom: Life/Civic Milestones: Date */
  $handler->display->display_options['sorts']['date_93']['id'] = 'date_93';
  $handler->display->display_options['sorts']['date_93']['table'] = 'civicrm_value_life_civic_milestones_27';
  $handler->display->display_options['sorts']['date_93']['field'] = 'date_93';
  $handler->display->display_options['sorts']['date_93']['order'] = 'DESC';
  /* Contextual filter: CiviCRM Drupal match table: Drupal User ID */
  $handler->display->display_options['arguments']['uf_id']['id'] = 'uf_id';
  $handler->display->display_options['arguments']['uf_id']['table'] = 'civicrm_uf_match';
  $handler->display->display_options['arguments']['uf_id']['field'] = 'uf_id';
  $handler->display->display_options['arguments']['uf_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uf_id']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uf_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uf_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uf_id']['summary_options']['items_per_page'] = '25';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  

  // Add view to list of views to provide.
  $views[$view->name] = $view;

  ////////////////////////////////////////////////////////////////////////
  //ALUMNI UPCOMING EVENT
  $view = new view();
  $view->name = 'upcoming_events';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'civicrm_event';
  $view->human_name = 'Upcoming Alumni Events';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Upcoming Alumni Events';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
									 'title' => 'title',
									 'start_date' => 'start_date',
									 'summary' => 'summary',
									 'id' => 'id',
									 'text_link' => 'text_link',
									 );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
								      'title' => array(
										       'sortable' => 0,
										       'default_sort_order' => 'asc',
										       'align' => '',
										       'separator' => '',
										       'empty_column' => 0,
										       ),
								      'start_date' => array(
											    'sortable' => 0,
											    'default_sort_order' => 'asc',
											    'align' => '',
											    'separator' => '',
											    'empty_column' => 0,
											    ),
								      'summary' => array(
											 'sortable' => 0,
											 'default_sort_order' => 'asc',
											 'align' => '',
											 'separator' => '',
											 'empty_column' => 0,
											 ),
								      'id' => array(
										    'sortable' => 0,
										    'default_sort_order' => 'asc',
										    'align' => '',
										    'separator' => '',
										    'empty_column' => 0,
										    ),
								      'text_link' => array(
											   'align' => '',
											   'separator' => '',
											   'empty_column' => 0,
											   ),
								      );
  /* Field: CiviCRM Events: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'civicrm_event';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Event Title';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_civicrm_event'] = 'page';
  /* Field: CiviCRM Events: Start Date */
  $handler->display->display_options['fields']['start_date']['id'] = 'start_date';
  $handler->display->display_options['fields']['start_date']['table'] = 'civicrm_event';
  $handler->display->display_options['fields']['start_date']['field'] = 'start_date';
  $handler->display->display_options['fields']['start_date']['date_format'] = 'custom';
  $handler->display->display_options['fields']['start_date']['custom_date_format'] = 'd M Y';
  /* Field: CiviCRM Events: Summary */
  $handler->display->display_options['fields']['summary']['id'] = 'summary';
  $handler->display->display_options['fields']['summary']['table'] = 'civicrm_event';
  $handler->display->display_options['fields']['summary']['field'] = 'summary';
  /* Field: CiviCRM Events: Event ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'civicrm_event';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  /* Field: CiviCRM Events: Text Link */
  $handler->display->display_options['fields']['text_link']['id'] = 'text_link';
  $handler->display->display_options['fields']['text_link']['table'] = 'civicrm_event';
  $handler->display->display_options['fields']['text_link']['field'] = 'text_link';
  $handler->display->display_options['fields']['text_link']['label'] = 'Register';
  $handler->display->display_options['fields']['text_link']['link_to_civicrm_event'] = 'register';
  /* Sort criterion: CiviCRM Events: Start Date */
  $handler->display->display_options['sorts']['start_date']['id'] = 'start_date';
  $handler->display->display_options['sorts']['start_date']['table'] = 'civicrm_event';
  $handler->display->display_options['sorts']['start_date']['field'] = 'start_date';
  /* Filter criterion: CiviCRM Events: Start Date */
  $handler->display->display_options['filters']['start_date']['id'] = 'start_date';
  $handler->display->display_options['filters']['start_date']['table'] = 'civicrm_event';
  $handler->display->display_options['filters']['start_date']['field'] = 'start_date';
  $handler->display->display_options['filters']['start_date']['operator'] = '>=';
  $handler->display->display_options['filters']['start_date']['value']['value'] = 'now';
  $handler->display->display_options['filters']['start_date']['value']['type'] = 'offset';
  /* Filter criterion: CiviCRM Custom: event tags: Event Audience */
  $handler->display->display_options['filters']['event_audience_125']['id'] = 'event_audience_125';
  $handler->display->display_options['filters']['event_audience_125']['table'] = 'civicrm_value_event_tags_32';
  $handler->display->display_options['filters']['event_audience_125']['field'] = 'event_audience_125';
  $handler->display->display_options['filters']['event_audience_125']['value'] = array(
										       1 => '1',
										       );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'upcoming-events';

  /* Display: Student event page */
  $handler = $view->new_display('page', 'Student event page', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Upcoming Student Events';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: CiviCRM Events: Event Type */
  $handler->display->display_options['filters']['event_type']['id'] = 'event_type';
  $handler->display->display_options['filters']['event_type']['table'] = 'civicrm_event';
  $handler->display->display_options['filters']['event_type']['field'] = 'event_type';
  $handler->display->display_options['filters']['event_type']['value'] = array(
									       7 => '7',
									       8 => '8',
									       4 => '4',
									       5 => '5',
									       6 => '6',
									       10 => '10',
									       );
  /* Filter criterion: CiviCRM Events: Start Date */
  $handler->display->display_options['filters']['start_date']['id'] = 'start_date';
  $handler->display->display_options['filters']['start_date']['table'] = 'civicrm_event';
  $handler->display->display_options['filters']['start_date']['field'] = 'start_date';
  $handler->display->display_options['filters']['start_date']['operator'] = '>=';
  $handler->display->display_options['filters']['start_date']['value']['value'] = 'now';
  $handler->display->display_options['filters']['start_date']['value']['type'] = 'offset';
  $handler->display->display_options['path'] = 'studentevents';
  
  // Add view to list of views to provide.
  $views[$view->name] = $view;

  ////////////////////////////////////////////////////////////////////////
  //ALUMNI  EMPLOYMENT HISTORY
  $view = new view();
  $view->name = 'alumni_employment_history';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'civicrm_contact';
  $view->human_name = 'Alumni Employment History';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Employment History';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
									 'id' => 'id',
									 'employer_85' => 'employer_85',
									 'job_title_86' => 'job_title_86',
									 'start_date_87' => 'start_date_87',
									 'end_date_88' => 'start_date_87',
									 );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
								      'id' => array(
										    'sortable' => 0,
										    'default_sort_order' => 'asc',
										    'align' => '',
										    'separator' => '',
										    'empty_column' => 0,
										    ),
								      'employer_85' => array(
											     'sortable' => 0,
											     'default_sort_order' => 'asc',
											     'align' => '',
											     'separator' => '',
											     'empty_column' => 0,
											     ),
								      'job_title_86' => array(
											      'sortable' => 0,
											      'default_sort_order' => 'asc',
											      'align' => '',
											      'separator' => '',
											      'empty_column' => 0,
											      ),
								      'start_date_87' => array(
											       'sortable' => 0,
											       'default_sort_order' => 'asc',
											       'align' => '',
											       'separator' => ' - ',
											       'empty_column' => 0,
											       ),
								      'end_date_88' => array(
											     'sortable' => 0,
											     'default_sort_order' => 'asc',
											     'align' => '',
											     'separator' => '',
											     'empty_column' => 0,
											     ),
								      );
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* Footer: Global: Unfiltered text */
  $handler->display->display_options['footer']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['footer']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['content'] = 'Add and Update your <a href="/dashboard/alumni/employment?destination=dashboard/alumni">Employment History!</a>';
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'Add your <a href="dashboard/alumni/employment?destination=dashboard/alumni">Employment History!</a>';
  /* Relationship: CiviCRM Contacts: Drupal ID */
  $handler->display->display_options['relationships']['drupal_id']['id'] = 'drupal_id';
  $handler->display->display_options['relationships']['drupal_id']['table'] = 'civicrm_contact';
  $handler->display->display_options['relationships']['drupal_id']['field'] = 'drupal_id';
  /* Field: CiviCRM Contacts: Contact ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'civicrm_contact';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: CiviCRM Custom: Employment History: Employer */
  $handler->display->display_options['fields']['employer_85']['id'] = 'employer_85';
  $handler->display->display_options['fields']['employer_85']['table'] = 'civicrm_value_employment_history_26';
  $handler->display->display_options['fields']['employer_85']['field'] = 'employer_85';
  /* Field: CiviCRM Custom: Employment History: Job title */
  $handler->display->display_options['fields']['job_title_86']['id'] = 'job_title_86';
  $handler->display->display_options['fields']['job_title_86']['table'] = 'civicrm_value_employment_history_26';
  $handler->display->display_options['fields']['job_title_86']['field'] = 'job_title_86';
  /* Field: CiviCRM Custom: Employment History: Start Date */
  $handler->display->display_options['fields']['start_date_87']['id'] = 'start_date_87';
  $handler->display->display_options['fields']['start_date_87']['table'] = 'civicrm_value_employment_history_26';
  $handler->display->display_options['fields']['start_date_87']['field'] = 'start_date_87';
  $handler->display->display_options['fields']['start_date_87']['label'] = 'Start';
  $handler->display->display_options['fields']['start_date_87']['date_format'] = 'custom';
  $handler->display->display_options['fields']['start_date_87']['custom_date_format'] = 'd M Y';
  /* Field: CiviCRM Custom: Employment History: End Date */
  $handler->display->display_options['fields']['end_date_88']['id'] = 'end_date_88';
  $handler->display->display_options['fields']['end_date_88']['table'] = 'civicrm_value_employment_history_26';
  $handler->display->display_options['fields']['end_date_88']['field'] = 'end_date_88';
  $handler->display->display_options['fields']['end_date_88']['date_format'] = 'custom';
  $handler->display->display_options['fields']['end_date_88']['custom_date_format'] = 'd M Y';
  /* Sort criterion: CiviCRM Custom: Employment History: Start Date */
  $handler->display->display_options['sorts']['start_date_87']['id'] = 'start_date_87';
  $handler->display->display_options['sorts']['start_date_87']['table'] = 'civicrm_value_employment_history_26';
  $handler->display->display_options['sorts']['start_date_87']['field'] = 'start_date_87';
  $handler->display->display_options['sorts']['start_date_87']['order'] = 'DESC';
  /* Contextual filter: CiviCRM Drupal match table: Drupal User ID */
  $handler->display->display_options['arguments']['uf_id']['id'] = 'uf_id';
  $handler->display->display_options['arguments']['uf_id']['table'] = 'civicrm_uf_match';
  $handler->display->display_options['arguments']['uf_id']['field'] = 'uf_id';
  $handler->display->display_options['arguments']['uf_id']['relationship'] = 'drupal_id';
  $handler->display->display_options['arguments']['uf_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uf_id']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uf_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uf_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uf_id']['summary_options']['items_per_page'] = '25';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  
  // Add view to list of views to provide.
  $views[$view->name] = $view;


  ////////////////////////////////////////////////////////////////////////
  //ALUMNI CONTACT INFO
  $view = new view();
  $view->name = 'alumni_contact_info';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'civicrm_contact';
  $view->human_name = 'Alumni Contact Info';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Contact Info';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['content'] = '<a href=\'/content/alumni-update-contact-details\'>Update Contact Info</a>';
  $handler->display->display_options['footer']['area']['format'] = 'filtered_html';
  /* Field: CiviCRM Contacts: Contact ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'civicrm_contact';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  /* Field: CiviCRM Address: Full Street Address */
  $handler->display->display_options['fields']['street_address']['id'] = 'street_address';
  $handler->display->display_options['fields']['street_address']['table'] = 'civicrm_address';
  $handler->display->display_options['fields']['street_address']['field'] = 'street_address';
  $handler->display->display_options['fields']['street_address']['label'] = '';
  $handler->display->display_options['fields']['street_address']['exclude'] = TRUE;
  $handler->display->display_options['fields']['street_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['street_address']['location_type'] = '0';
  $handler->display->display_options['fields']['street_address']['location_op'] = '0';
  $handler->display->display_options['fields']['street_address']['is_primary'] = 1;
  /* Field: CiviCRM Address: City / Suburb */
  $handler->display->display_options['fields']['city']['id'] = 'city';
  $handler->display->display_options['fields']['city']['table'] = 'civicrm_address';
  $handler->display->display_options['fields']['city']['field'] = 'city';
  $handler->display->display_options['fields']['city']['label'] = '';
  $handler->display->display_options['fields']['city']['exclude'] = TRUE;
  $handler->display->display_options['fields']['city']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['city']['alter']['text'] = '[city], ';
  $handler->display->display_options['fields']['city']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['city']['location_type'] = '0';
  $handler->display->display_options['fields']['city']['location_op'] = '0';
  $handler->display->display_options['fields']['city']['is_primary'] = 1;
  /* Field: CiviCRM Custom: Address Details: Commune */
  $handler->display->display_options['fields']['commune_45']['id'] = 'commune_45';
  $handler->display->display_options['fields']['commune_45']['table'] = 'civicrm_value_address_details_14';
  $handler->display->display_options['fields']['commune_45']['field'] = 'commune_45';
  $handler->display->display_options['fields']['commune_45']['label'] = '';
  $handler->display->display_options['fields']['commune_45']['exclude'] = TRUE;
  $handler->display->display_options['fields']['commune_45']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['commune_45']['alter']['text'] = '[commune_45], ';
  $handler->display->display_options['fields']['commune_45']['element_label_colon'] = FALSE;
  /* Field: CiviCRM Address: State/Province */
  $handler->display->display_options['fields']['state_province']['id'] = 'state_province';
  $handler->display->display_options['fields']['state_province']['table'] = 'civicrm_address';
  $handler->display->display_options['fields']['state_province']['field'] = 'state_province';
  $handler->display->display_options['fields']['state_province']['label'] = '';
  $handler->display->display_options['fields']['state_province']['exclude'] = TRUE;
  $handler->display->display_options['fields']['state_province']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['state_province']['location_type'] = '0';
  $handler->display->display_options['fields']['state_province']['location_op'] = '0';
  $handler->display->display_options['fields']['state_province']['is_primary'] = 1;
  $handler->display->display_options['fields']['state_province']['prov_display'] = '2';
  /* Field: CiviCRM Address: Postal Code */
  $handler->display->display_options['fields']['postal_code']['id'] = 'postal_code';
  $handler->display->display_options['fields']['postal_code']['table'] = 'civicrm_address';
  $handler->display->display_options['fields']['postal_code']['field'] = 'postal_code';
  $handler->display->display_options['fields']['postal_code']['label'] = '';
  $handler->display->display_options['fields']['postal_code']['exclude'] = TRUE;
  $handler->display->display_options['fields']['postal_code']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['postal_code']['location_type'] = '0';
  $handler->display->display_options['fields']['postal_code']['location_op'] = '0';
  $handler->display->display_options['fields']['postal_code']['is_primary'] = 1;
  /* Field: CiviCRM Address: Country */
  $handler->display->display_options['fields']['country']['id'] = 'country';
  $handler->display->display_options['fields']['country']['table'] = 'civicrm_address';
  $handler->display->display_options['fields']['country']['field'] = 'country';
  $handler->display->display_options['fields']['country']['label'] = '';
  $handler->display->display_options['fields']['country']['exclude'] = TRUE;
  $handler->display->display_options['fields']['country']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['country']['location_type'] = '0';
  $handler->display->display_options['fields']['country']['location_op'] = '0';
  $handler->display->display_options['fields']['country']['is_primary'] = 1;
  $handler->display->display_options['fields']['country']['country_display'] = '2';
  /* Field: CiviCRM Email: Email Address */
  $handler->display->display_options['fields']['email']['id'] = 'email';
  $handler->display->display_options['fields']['email']['table'] = 'civicrm_email';
  $handler->display->display_options['fields']['email']['field'] = 'email';
  $handler->display->display_options['fields']['email']['label'] = '';
  $handler->display->display_options['fields']['email']['exclude'] = TRUE;
  $handler->display->display_options['fields']['email']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['email']['location_type'] = '0';
  $handler->display->display_options['fields']['email']['location_op'] = '0';
  $handler->display->display_options['fields']['email']['is_primary'] = 1;
  /* Field: CiviCRM Phone Details: Phone */
  $handler->display->display_options['fields']['phone']['id'] = 'phone';
  $handler->display->display_options['fields']['phone']['table'] = 'civicrm_phone';
  $handler->display->display_options['fields']['phone']['field'] = 'phone';
  $handler->display->display_options['fields']['phone']['label'] = '';
  $handler->display->display_options['fields']['phone']['exclude'] = TRUE;
  $handler->display->display_options['fields']['phone']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['phone']['location_type'] = '0';
  $handler->display->display_options['fields']['phone']['location_op'] = '0';
  $handler->display->display_options['fields']['phone']['is_primary'] = 1;
  $handler->display->display_options['fields']['phone']['phone_type'] = '0';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<table><tr><td>Address:<br/>[street_address]<br/>[commune_45][city][state_province] [postal_code]<br/>[country]</td>
<td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>
<td>Email: [email]<br/>Phone: [phone]</td></tr></table>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Contextual filter: CiviCRM Drupal match table: Drupal User ID */
  $handler->display->display_options['arguments']['uf_id']['id'] = 'uf_id';
  $handler->display->display_options['arguments']['uf_id']['table'] = 'civicrm_uf_match';
  $handler->display->display_options['arguments']['uf_id']['field'] = 'uf_id';
  $handler->display->display_options['arguments']['uf_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uf_id']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uf_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uf_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uf_id']['summary_options']['items_per_page'] = '25';
  
  $views[$view->name] = $view;

  ////////////////////////////////////////////////////////////////////////
  //ALUMNI
  $view = new view();
  $view->name = 'alumni_status';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'civicrm_contact';
  $view->human_name = 'Alumni Status';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Status';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
									 'id' => 'id',
									 );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
								      'id' => array(
										    'sortable' => 0,
										    'default_sort_order' => 'asc',
										    'align' => '',
										    'separator' => '',
										    'empty_column' => 0,
										    ),
								      );
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['content'] = '<a href=\'/content/alumni-status\'>Update Contact Info</a>';
  $handler->display->display_options['footer']['area']['format'] = 'filtered_html';
  /* Field: CiviCRM Contacts: Contact ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'civicrm_contact';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  /* Field: CiviCRM Custom: Alumni Status: Current Status */
  $handler->display->display_options['fields']['current_status_128']['id'] = 'current_status_128';
  $handler->display->display_options['fields']['current_status_128']['table'] = 'civicrm_value_alumni_status_34';
  $handler->display->display_options['fields']['current_status_128']['field'] = 'current_status_128';
  /* Field: CiviCRM Custom: Alumni Status: What am I looking for */
  $handler->display->display_options['fields']['what_am_i_looking_for_129']['id'] = 'what_am_i_looking_for_129';
  $handler->display->display_options['fields']['what_am_i_looking_for_129']['table'] = 'civicrm_value_alumni_status_34';
  $handler->display->display_options['fields']['what_am_i_looking_for_129']['field'] = 'what_am_i_looking_for_129';
  /* Contextual filter: CiviCRM Drupal match table: Drupal User ID */
  $handler->display->display_options['arguments']['uf_id']['id'] = 'uf_id';
  $handler->display->display_options['arguments']['uf_id']['table'] = 'civicrm_uf_match';
  $handler->display->display_options['arguments']['uf_id']['field'] = 'uf_id';
  $handler->display->display_options['arguments']['uf_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uf_id']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uf_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uf_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uf_id']['summary_options']['items_per_page'] = '25';
  

  $views[$view->name] = $view;

  // ...Repeat all of the above for each view the module should provide.

  // At the end, return array of default views.
  return $views;

}
