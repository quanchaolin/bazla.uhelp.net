<?php

function email_notifications_send($type, $data) {
  $target = email_notifications_get_target_email($type);
  if (!$target) {
    //if the target doesn't exist than we will not send an email
    return;
  }
  
  $sender = variable_get('email_notifications_sender');
  if (!$sender) {
    drupal_set_message("Error Code #3498 no sender set! go to ".
		       l("the settings", "/admin/config/notifications"), 'error');
    return;
  }
  $subject = $msg = '';
  $function = 'email_notifications_' . $type;

  $msg = "<html><head></head><body>" . $msg . "</body></html>";
  
  $function($data, $subject, $msg);

  $headers =
    //    'From: ' . $sender . "\r\n" .
    'Reply-To: ' . $sender . "\r\n" .
    'X-Mailer: PHP/' . phpversion()  . "\r\n";
    ;
  
  mail($target, $subject, $msg, $headers);
 
}


function email_notifications_get_target_email($type) {
  $toggle = variable_get($type.'_toggle', FALSE);
  if (!$toggle) {
    return FALSE;
  }

  $target = variable_get($type.'_email', FALSE);

  if ($target) {
    return $target;
  }

  $target = variable_get('email_notifications_default_target');

  if (!$target) {
    drupal_set_message("Error Code #3733 no default target set! go to ".
		       l("the settings", "/admin/config/notifications"), 'error');
   
  }

  return $target;
}