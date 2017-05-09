<?php
/**        
*/
function email_notifications_alumni_employment($data, &$subject, &$msg) {
  dsm($data,"employ");
}
/**        
*/
function email_notifications_alumni_milestone($data, &$subject, &$msg) {
  //all the available variable in $data
  $milestone = ucwords($data['milestone']);
  $details = $data['details'];
  $date = $data ['date'];
  $alumni_link = $data['alumni_link'];
  $alumni_name = $data['alumni_name'];

  $subject = $alumni_name . " had a " . $milestone;
  
  $msg = $alumni_name . ' added a "' . $milestone . '" milestone that occured on '. $date;
  $msg .= "\n\n" . $alumni_link;
  if ($details) {
    $msg .= "\n\n Details: " . $details;
  }
}

/**        
*/
function email_notifications_alumni_status($data, &$subject, &$msg) {
  $status = $data['status'];    
  $looks = $data['looks'];
  $date = $data ['date'];
  $alumni_link = $data['alumni_link'];
  $alumni_name = $data['alumni_name'];

  $subject = $alumni_name . " changed their status.";
  
  $msg = $alumni_name . ' changed their status on '. $date;
  $msg .= "\n\nCurrent Status: " . $status;
  $msg .= "\n\nCurrently Looking For: " . $looks;  
}
/**        
*/
function email_notifications_alumni_address($data, &$subject, &$msg) {
  $street = $data['street'];
  $street2 = $data['street2'];
  $city = $data['city'];
  $state = $data['state'];
  $country = $data['country'];
  $code = $data['code']; 
  $phone = $data['phone'];
  $email = $data['email'];
  $commune = $data['commune'];
  $alumni_link = $data['alumni_link'];
  $alumni_name = $data['alumni_name']; 
  $date = $data['date'];

  $subject = $alumni_name . ' has updated their contact info.';

  $msg = $alumni_name . ' updated their contact info on ' . $date . '.';
  $msg .= "\n\n". $alumni_link;
  $msg .= "\n\n". $street;
  $msg .= "\n". $street2;
  $msg .= "\n". $city;
  $msg .= "\n". $commune;
  $msg .= "\n". $state;
  $msg .= "\n". $country;
  $msg .= "\n". $email;
  $msg .= "\n". $phone;
}
