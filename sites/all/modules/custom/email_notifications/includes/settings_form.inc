<?php

function email_notifications_settings_form($form, &$form_state) {
  $form['email_notifications_default_target'] =
    array(
	  '#title' => t("Default Target Email"),
	  '#type' => 'textfield',
	  '#default_value' => variable_get('email_notifications_default_target'),
	  '#description' => t("The default target email address. If a type is enabled ".
			      "below but no email address is given the default will be ".
			      "used"),
	  '#suffix' => '<hr>',
	  '#required' => TRUE
	  );

    $form['email_notifications_sender'] =
    array(
	  '#title' => t("Sender Email"),
	  '#type' => 'textfield',
	  '#default_value' => variable_get('email_notifications_sender'),
	  '#description' => t("The email address that will be the used for the email From"),
	  '#suffix' => '<hr>',
	  '#required' => TRUE
	  );

  $notification_types = array();
  drupal_alter("email_notifications_types", $notification_types);

  foreach($notification_types as $type) {
    $label = ucwords(str_replace("_", ' ', $type));
    $form[$type] = 
    array(
	  '#title' => $label,
	  '#type' => 'fieldset',
	  );

    $form[$type][$type.'_toggle'] =
      array(
	    '#title' => "<strong>Enable $label notifications</strong>",
	    '#type' => 'checkbox',
	    '#default_value' => variable_get($type.'_toggle'),
	    '#description' =>
	    "Check if you would like to have $label email notifications sent",
	    );
    
    $form[$type][$type.'_email'] =
      array(
	    '#title' => $label." Notification Destination Email Address",
	    '#type' => 'textfield',
	    '#default_value' => variable_get($type.'_email'),
	    '#description' => "The email address to send $label notifications",
	    );
    
  }

  return system_settings_form($form);
}