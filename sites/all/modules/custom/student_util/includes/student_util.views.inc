<?php

function student_util_views_default_views() {
  $views =  array();
  
  ////////////////////////////////////////////////////////////////////////
  //STUDENT YEARS
  $view = new view();
  $view->name = 'student_years';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'civicrm_contact';
  $view->human_name = 'Student Years';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Student Years';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
							       3 => '3',
							       17 => '17',
							       13 => '13',
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
  $handler->display->display_options['pager']['options']['items_per_page'] = '1000';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['content'] = 'Found @total students. ';
  /* Field: CiviCRM Contacts: Contact ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'civicrm_contact';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: CiviCRM Contacts: Display Name */
  $handler->display->display_options['fields']['display_name']['id'] = 'display_name';
  $handler->display->display_options['fields']['display_name']['table'] = 'civicrm_contact';
  $handler->display->display_options['fields']['display_name']['field'] = 'display_name';
  $handler->display->display_options['fields']['display_name']['label'] = 'Name';
  $handler->display->display_options['fields']['display_name']['link_to_civicrm_contact'] = 1;
  /* Field: CiviCRM Custom: Help Student Info: HELP Year */
  $handler->display->display_options['fields']['help_year_126']['id'] = 'help_year_126';
  $handler->display->display_options['fields']['help_year_126']['table'] = 'civicrm_value_help_student_info_33';
  $handler->display->display_options['fields']['help_year_126']['field'] = 'help_year_126';
  $handler->display->display_options['fields']['help_year_126']['precision'] = '0';
  /* Sort criterion: CiviCRM Custom: Help Student Info: HELP Year */
  $handler->display->display_options['sorts']['help_year_126']['id'] = 'help_year_126';
  $handler->display->display_options['sorts']['help_year_126']['table'] = 'civicrm_value_help_student_info_33';
  $handler->display->display_options['sorts']['help_year_126']['field'] = 'help_year_126';
  $handler->display->display_options['sorts']['help_year_126']['order'] = 'DESC';
  /* Filter criterion: CiviCRM Custom: Help Student Info: HELP Year */
  $handler->display->display_options['filters']['help_year_126']['id'] = 'help_year_126';
  $handler->display->display_options['filters']['help_year_126']['table'] = 'civicrm_value_help_student_info_33';
  $handler->display->display_options['filters']['help_year_126']['field'] = 'help_year_126';
  $handler->display->display_options['filters']['help_year_126']['operator'] = 'between';
  $handler->display->display_options['filters']['help_year_126']['value']['min'] = '0';
  $handler->display->display_options['filters']['help_year_126']['value']['max'] = '20';
  $handler->display->display_options['filters']['help_year_126']['exposed'] = TRUE;
  $handler->display->display_options['filters']['help_year_126']['expose']['operator_id'] = 'help_year_126_op';
  $handler->display->display_options['filters']['help_year_126']['expose']['label'] = 'HELP Year';
  $handler->display->display_options['filters']['help_year_126']['expose']['operator'] = 'help_year_126_op';
  $handler->display->display_options['filters']['help_year_126']['expose']['identifier'] = 'help_year_126';
  $handler->display->display_options['filters']['help_year_126']['expose']['remember_roles'] = array(
												     2 => '2',
												     1 => 0,
												     3 => 0,
												     4 => 0,
												     5 => 0,
												     17 => 0,
												     6 => 0,
												     7 => 0,
												     8 => 0,
												     9 => 0,
												     10 => 0,
												     11 => 0,
												     12 => 0,
												     13 => 0,
												     14 => 0,
												     15 => 0,
												     16 => 0,
												     18 => 0,
												     );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'student-years';
  
  // Add view to list of views to provide.
  $views[$view->name] = $view;

  // At the end, return array of default views.
  return $views;

}
