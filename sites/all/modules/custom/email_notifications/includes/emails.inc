<?php
/**        
*/
function email_notifications_alumni_employment($data, &$subject, &$msg) {
  dsm($data,"employ");
  $new_employer = $data['new_employer'];
  $existing_job = $data['existing_job'];
  $alumni_link = $data['alumni_link'];
  $alumni_name = $data['alumni_name'];  
  $employer_link = $data['employer_link'];
  $employer_name = $data['employer_name'];  
  $salary = $data['salary'];  
  $title = $data['title'];  
  $currency = $data['currency']; 
  $start_date = $data['start_date']; 
  $end_date = $data['end_date'];

  //are they updating a job's end date?
  if ($existing_job) {
    $subject = $alumni_name . " updated their job at ". $employer_name . ".";
    $msg = $alumni_name . " updated their job at ". $employer_name . ".";
    $new = '';

  }
  //they are adding a new job
  else {
    $subject = $alumni_name . " added a new job " . $employer_name . ".";
    $msg = $alumni_name . " updated their job at ". $employer_name . ".";
    if ($new_employer) {
      $new = "*\n*(New Employer added by $alumni_name)";
    }
  }
  $msg .= "\n\nTheir new job starts: ". $start_date;
  if ($end_date) {
    $msg .= "\nTheir new job ended: ". $end_date;
  }
  $msg .= "\nTheir new job is: ". $title;
  $msg .= "\nThey get paid: ". $salary . ' ' . $currency;
  $msg .= "\n\nAlumni Contact: " . $alumni_link;
  $msg .= "\n\nEmployer Contact: " . $employer_link . " " . $new;

}
/**        
*/
function email_notifications_alumni_milestone($data, &$subject, &$msg) {
  //all the available variable in $data
  $milestone = ucwords($data['milestone']);
  $details = $data['details'];
  $date = $data['date'];
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
