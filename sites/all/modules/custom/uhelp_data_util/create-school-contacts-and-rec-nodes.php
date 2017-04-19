<?php 
//load spreadsheet into an array
 //   $filename = "help-rec-data-sample.csv";

 $filename = "/var/www/openflows/sites/all/modules/custom/uhelp_data_util/uhelp-recru-final2.csv";
  $csvArray = ImportCSV2Array($filename);

  civicrm_initialize();
//loop over array 


  foreach ($csvArray as $row){

    print_r($row[Nonecole]);
       



//set values for creating civi org contact 
//sub-contact type secondary school 

//clean and alter gps values
// so they are decimal, not hour min sec 

    $school_lat_clean = str_replace('*', '.', $row[CoordonneesGPS_Nord]);
    $school_lat_clean = str_replace(' ', '.', $school_lat_clean);   
    $school_lat_clean = rtrim($school_lat_clean, "'");

    $school_long_clean = str_replace('*', '.', $row[CoordonneesGPS_Ouest]);
    $school_long_clean = str_replace(' ', '.', $school_long_clean);
    $school_long_clean = rtrim($school_long_clean, "'");

    $school_lat_hms = explode(".",$school_lat_clean);
    $school_long_hms = explode(".",$school_long_clean);
    
//    $school_lat_hms = explode(".",$row[CoordonneesGPS_Nord]);
  //  $school_long_hms = explode(".",$row[CoordonneesGPS_Ouest]);
 
    
//print_r($school_lat_hms);
    $school_lat_dec = DMStoDEC($school_lat_hms[0],$school_lat_hms[1],$school_lat_hms[2]);
    $school_long_dec = "-".DMStoDEC($school_long_hms[0],$school_long_hms[1],$school_long_hms[2]);

    if ($school_lat_dec == 0){
       $school_lat_dec = "";
    }
    if ($school_long_dec == 0){
       $school_long_dec = "";
    }

//check if school exists. 
// if yes, store the cid 
// if no, create the record. 
// SKIPPING this check for now since we know all records are new 


// set values for custom fields 
// 78 is the vacation period 
// 79 is grades offered 



//$custom_78_values = array ("AM","PM");
//$custom_79_values = array ("Secondaire","Philo");

$row[Vacation] = str_replace(' ', '', $row[Vacation]);
$row[niveau] = str_replace(' ', '', $row[niveau]);
$custom_78_values = explode(",", $row[Vacation]);
$custom_79_values = explode(",", $row[niveau]);



    $school_data = array (
      'sequential' => 1,
      'contact_type' => "Organization",
      'contact_sub_type' => "Secondary_School",
      'organization_name' => $row[Nonecole],
      'street_address' =>  $row[Rue],
      'supplemental_address_1' => "",
      //   'supplemental_address_2' => $row[Commune],
      'city' => $row[Localite],
      'postal_code_suffix' => "",
      'postal_code' => "",
      'geo_code_1' => $school_lat_dec, //lat 
      'geo_code_2' => $school_long_dec, //long  
      'custom_78' => $custom_78_values,
      'custom_79' => $custom_79_values,
      'custom_45' =>  $row[Commune],
      'phone' => "",
      'email' => "",
      'state_province_id' =>  "2564",
      //'state_province' => "NI",
      'country' => "Haiti",
      );
   


//print_r($school_data);
 
 //create contact and store cid of school 
 
    $result = civicrm_api3('Contact', 'create', $school_data);

//print_r($result);

    $school_cid = $result[id];
 

//create values for haitian departments 
//for creating addresses 


//'state_province_id' => 10016, Artibonite
//'state_province_id' => 10017, Centre
// 'state_province_id' => 3008, Grand'Anse
//'state_province_id' => 10018, Nippes
//'state_province_id' => 2564, Nord
//'state_province_id' => 3009, Nord-Est
//'state_province_id' => 3010, Nord-Ouest
//'state_province_id' => 3011, Ouest
// 'state_province_id' => 3013, Sud-Est
//'state_province_id' => 3012, Sud

    $lowercase_department = strtolower($row[Department]);
    
    $state_province_id ="";
    if ($lowercase_department == "artibonite"){
      $state_province_id = 10016;
    }
    if ($lowercase_department == "centre"){
      $state_province_id = 10017;
    }
    if ($lowercase_department == "grand'anse"){
      $state_province_id = 3008;
    }
    if ($lowercase_department == "nippes"){
      $state_province_id = 10018;
    }
    if ($lowercase_department == "nord"){
      $state_province_id = 2564;
    }
    if ($lowercase_department == "sud"){
      $state_province_id = 3012;
    }
    if ($lowercase_department == "sud-est"){
      $state_province_id = 3013;
    }
    if ($lowercase_department == "ouest"){
      $state_province_id = 3011;
    }
    if ($lowercase_department == "nord-ouest"){
      $state_province_id = 3010;
    }
    if ($lowercase_department == "nord-est"){
      $state_province_id = 3009;
    }
    
    
    $result2 = civicrm_api3('Address', 'create', array(
      'contact_id' => $school_cid,
      'location_type_id' => 3,
      'street_address' =>  $row[Rue],
      'supplemental_address_1' => "",
      //      'supplemental_address_2' => $row[Commune],
      'country_id' => 1094,
      'state_province_id' => $state_province_id,
      'city' => $row[Localite],
      'custom_45' =>  $row[Commune],
      'commune' =>  $row[Commune],
    ));

    //    print_r($result2[id]);

    $result = civicrm_api3('Address', 'setvalue', array(
							'sequential' => 1,
							'value' =>  $row[Commune],
							//		'contact_id' => 3552,
							'id' => $result2[id],
							'field' => "custom_45",
							));

    //address_1_custom_45_206
    
 //set values for creating secondary school contact people 
 //create contacts 
 //and create relationship to school created above 
 
    if (!empty($row[Contact1_Nom])){
      $school_contact_1_data = array(
      'contact_type' => "Individual",
      'first_name' =>  $row[Contact1_Prenom],
      'middle_name' => "",
      'last_name' => $row[Contact1_Nom],
      'job_title' => $row[Contact1_Fonction],
      'street_address' => "",
      'supplemental_address_1' => "",
      'supplemental_address_2' => "",
      'city' => "",
      'postal_code_suffix' => "",
      'postal_code' => "",
      'phone' => $row[Contact1_Telephone],
      'email' => $row[Contact1_Email],
      'country' => "Haiti",
      );
    
//    print_r($school_contact_1_data);

//create contact and bring back cid 
      $result3 = civicrm_api3('Contact', 'create', $school_contact_1_data);

//print($row[Contact1_Nom]);
//print_r($result);
      $school_contact_id1 = $result3[id];

// create relationship between person and school 

      $result4 = civicrm_api3('Relationship', 'create', array(
        'sequential' => 1,
        'contact_id_a' => $school_contact_id1,
        'contact_id_b' => $school_cid,
        'relationship_type_id' => 38,
      ));



    }

    if (!empty($row[Contact2_Nom])){
      $school_contact_2_data = array(
        'contact_type' => "Individual",
        'first_name' =>  $row[Contact2_Prenom],  
        'middle_name' => "",
        'last_name' => $row[Contact2_Nom],
        'job_title' => $row[Contact2_Fonction],
        'street_address' => "",
        'supplemental_address_1' => "",
        'supplemental_address_2' => "",
        'city' => "",
        'postal_code_suffix' => "",
        'postal_code' => "",
        'phone' => $row[Contact2_Telephone],
        'email' => $row[Contact2_Email],
        'country' => "Haiti",
      );
    
//        print_r($school_contact_2_data);
//create contact and bring back cid 

      $result5 = civicrm_api3('Contact', 'create', $school_contact_2_data);
      $school_contact_id2 = $result5[id];

// create relationship between person and school 

      $result6 = civicrm_api3('Relationship', 'create', array(
        'sequential' => 1,
        'contact_id_a' => $school_contact_id2,
        'contact_id_b' => $school_cid,
        'relationship_type_id' => 38,
      ));
    
    }
    
    
    if (!empty($row[Contact3_Nom])){
      $school_contact_3_data = array(
      'contact_type' => "Individual",
      'first_name' =>  $row[Contact3_Prenom],
      'middle_name' => "",
      'last_name' => $row[Contact3_Nom],
      'job_title' => $row[Contact3_Fonction],
      'street_address' => "",
      'supplemental_address_1' => "",
      'supplemental_address_2' => "",
      'city' => "",
      'postal_code_suffix' => "",
      'postal_code' => "",
      'phone' => $row[Contact3_Telephone],
      'email' => $row[Contact3_Email],
//  'state_province_name' => "NI",
      'country' => "Haiti",
    );



//create contact and bring back cid 

    $result7 = civicrm_api3('Contact', 'create', $school_contact_3_data);
    $school_contact_id3 = $result7[id];

// create relationship between person and school 

    $result8 = civicrm_api3('Relationship', 'create', array(
      'sequential' => 1,
      'contact_id_a' => $school_contact_id3,
      'contact_id_b' => $school_cid,
      'relationship_type_id' => 38,
    ));

    }
//set values for creating recruitment content 

 



//take return value so we have the cid 



//create recruitement node 
// that should then trigger rules/funcitons 
//that create the activity on the contact we created 

    $node = new stdClass();
    $node->type = 'recruitment_event';
    node_object_prepare($node);
   
    $node->title    = "imported recruitment event";
    $node->uid = 1;
    $node->language = LANGUAGE_NONE;
  
  
// setting this set of values to 0 if empty because I was getting 
// an error if I left them unset and passed the null value in the array 
  
  
    if (empty($row[NombreGarcons_Philo]) || !is_numeric($row[NombreGarcons_Philo]) ){
      $node->field_philo_m[$node->language][0]['value'] = "0";
    }else{
      $node->field_philo_m[$node->language][0]['value'] = $row[NombreGarcons_Philo];
    }
  
    if (empty($row[NombreFilles_Philo]) || !is_numeric($row[NombreFilles_Philo]) ){
      $node->field_philo_f[$node->language][0]['value'] = "0";
    }else{
      $node->field_philo_f[$node->language][0]['value'] = $row[NombreFilles_Philo];
    }
    
    if (empty($row[NombreGarcons_Rheto]) || !is_numeric($row[NombreGarcons_Rheto])){
      $node->field_rheto_m[$node->language][0]['value'] = "0";
    }else{
      $node->field_rheto_m[$node->language][0]['value'] = $row[NombreGarcons_Rheto];
    }
    
    if (empty($row[NombreFilles_Rheto]) || !is_numeric($row[NombreFilles_Rheto])){
      $node->field_rheto_f[$node->language][0]['value'] = "0";
    }else{
      $node->field_rheto_f[$node->language][0]['value'] = $row[NombreFilles_Rheto];
    }
    
    if (empty($row[NombreFilles_Seconde]) || !is_numeric($row[NombreFilles_Seconde])){
      $node->field_seconde_f[$node->language][0]['value'] = "0";
    }else{
      $node->field_seconde_f[$node->language][0]['value'] = $row[NombreFilles_Seconde];
    }
    
    if (empty($row[NombreGarcons_Seconde]) || !is_numeric($row[NombreGarcons_Seconde])){
      $node->field_seconde_m[$node->language][0]['value'] = "0";
    }else{
      $node->field_seconde_m[$node->language][0]['value'] = $row[NombreGarcons_Seconde];
    }
    
    if (empty($row[NombreGarcons_3eme]) || !is_numeric($row[NombreGarcons_3eme])){
      $node->field_3eme_m[$node->language][0]['value'] = "0";
    }else{
      $node->field_3eme_m[$node->language][0]['value'] = $row[NombreGarcons_3eme];
    }
    
    if (empty($row[NombreFilles_3eme]) || !is_numeric($row[NombreFilles_3eme])){
      $node->field_3eme_f[$node->language][0]['value'] = "0";
    }else{
      $node->field_3eme_f[$node->language][0]['value'] = $row[NombreFilles_3eme];
    }
    
    if (empty($row[NombreFilles_9eme]) || !is_numeric($row[NombreFilles_9eme])){
      $node->field_9eme_f[$node->language][0]['value'] = "0";
    }else{
      $node->field_9eme_f[$node->language][0]['value'] = $row[NombreFilles_9eme];
    }
    
    if (empty($row[NombreGarcons_9eme]) || !is_numeric($row[NombreGarcons_9eme])){
      $node->field_9eme_m[$node->language][0]['value'] = "0";
    }else{
      $node->field_9eme_m[$node->language][0]['value'] = $row[NombreGarcons_9eme];
    }
  
// set the cid of the school contact for reference   
    $node->field_recruitment_school[$node->language][0]['contact_id'] = $school_cid;

//    print_r($school_cid);
  
  //// For date
  //$node->field_datetest[$node->language][0][value] = "2011-05-25T10:35:58";
  //// For datetime
  //$node->field_datetest[$node->language][0][value] = "2011-05-25 10:35:58";

// date of visit  
    if (!empty($row[Datedelavisite])){
      $node->field_recruitment_date_of_visit[$node->language][0]['value'] = $row[Datedelavisite]." ".$row[Heured_arrivee];
      $node->field_recruitment_date_of_visit[$node->language][0]['timezone'] = "America/New_York";
      $node->field_recruitment_date_of_visit[$node->language][0]['timezone_db']= "America/New_York";
      $node->field_recruitment_date_of_visit[$node->language][0]['date_type'] ="datetime";
    }else{
      $node->field_recruitment_date_of_visit[$node->language][0]['value'] = "2014-01-01 12:00:00";
      $node->field_recruitment_date_of_visit[$node->language][0]['timezone'] = "America/New_York";
      $node->field_recruitment_date_of_visit[$node->language][0]['timezone_db']= "America/New_York";
      $node->field_recruitment_date_of_visit[$node->language][0]['date_type'] ="datetime";
    }    
    //$node->field_recruitment_date_of_visit[$node->language][0]['value'] = $row[Datedelavisite];
    
	    
    
    
//    $node->field_r_school_details[$node->language][0]['value'] = "";
    
    if (empty($row[nombre_tota]) || !is_numeric($row[nombre_tota])){
      $node->field_r_approximate_total[$node->language][0]['value'] = "0";
    }else{
      $node->field_r_approximate_total[$node->language][0]['value'] = $row[nombre_tota];
    }
    
    $node->field_have_you_been_well_receive[$node->language][0]['value'] = $row[bienrecu];

    $node->field_r_if_no_why_not[$node->language][0]['value'] = $row[Commentaires_recu];
    $node->field_r_if_no_why_not[$node->language][0]['format']  = 'plain_text';

    $node->field_r_further_info[$node->language][0]['value'] = $row[Autresremarques];
    $node->field_r_further_info[$node->language][0]['format']  = 'plain_text';

    
  //$node->field_r_team_leader[$node->language][0]['value'] =
  
 
  
    if (!empty($row[Recruteur1_Nom])){
  
      $result9 = civicrm_api3('Contact', 'get', array(
        'sequential' => 1,
        'first_name' => $row[Recruiteur1_Prenom],
        'last_name' => $row[Recruteur1_Nom],
      ));
  //  print_r($result);

      //print_r($row[Recruiteur1_Prenom]);
      //print_r($row[Recruteur1_Nom]);

      if ($result9[count] == 1){
        $recruiter_cid = $result9[id];
    
        $node->field_r_recruiter_names[$node->language][0]['contact_id'] = $recruiter_cid;
      }
    }

    if (!empty($row[Recruteur2_Nom])){
      $result10 = civicrm_api3('Contact', 'get', array(
        'sequential' => 1,
        'first_name' => $row[Recruiteur2_Prenom],
        'last_name' => $row[Recruteur2_Nom],
      ));
  
      if ($result10[count] == 1){
        $recruiter_cid = $result10[id];

        $node->field_r_recruiter_names[$node->language][1]['contact_id'] =$recruiter_cid;
      }
    }


    if (!empty($row[Recruteur3_Nom])){

      $result11 = civicrm_api3('Contact', 'get', array(
        'sequential' => 1,
        'first_name' => $row[Recruiteur3_Prenom],
        'last_name' => $row[Recruteur3_Nom],
      ));
  
      if ($result11[count] == 1){
        $recruiter_cid = $result11[id];

        $node->field_r_recruiter_names[$node->language][2]['contact_id'] =$recruiter_cid;
      }
    }


    if (!empty($row[Recruteur4_Nom])){
      $result12 = civicrm_api3('Contact', 'get', array(
        'sequential' => 1,
        'first_name' => $row[Recruiteur4_Prenom],
        'last_name' => $row[Recruteur4_Nom],
      ));
  
      if ($result12[count] == 1){
        $recruiter_cid = $result12[id];

        $node->field_r_recruiter_names[$node->language][3]['contact_id'] =$recruiter_cid;
      }
    }
    






//  $node->body[$node->language][0]['value']   = $body_text;
//  $node->body[$node->language][0]['summary'] = text_summary($body_text);
//  $node->body[$node->language][0]['format']  = 'filtered_html';
 
//  $path = 'content/programmatically_created_node_' . date('YmdHis');
//  $node->path = array('alias' => $path);
//$node->field_fnordtext[$node->language][0]['value'] = "Fnord fnord fnord";
//$node->field_employees_full_time[$node->language][0]['value'] = "456"; //$business_info['BusinessEmployeesFT']; 

//print_r($node);

//    if($node = node_submit($node)) { // Prepare node for saving
      $node= node_submit($node);

        if (!empty($row[Whoenteredthisdata_Nom]) &&  !empty($row[Whoenteredthisdata_Prenom])){
      $result12 = civicrm_api3('Contact', 'get', array(
        'sequential' => 1,
        'first_name' => $row[Whoenteredthisdata_Prenom],
        'last_name' => $row[Whoenteredthisdata_Nom],
      ));
  
      if ($result12[count] == 1){
        $data_entry_person_cid = $result12[id];
        $result13 = civicrm_api3('UFMatch', 'get', array(
          'contact_id' => $data_entry_person_cid,
         ));
         
         if ($result13[count] == 1){
           $node->uid = $result13[id];
           $user=user_load($result13[id]);
           $username=$user->name;
           $node->name = $username;
         }
      }else{ 
           $node->uid = 1;
           $node->name = "uid1";
         }          
    }else{ 
           $node->uid = 1;
           $node->name = "uid1";
         }          
//     print_r($node);

      rules_invoke_event('node_insert', $node);
      node_save($node);
      


      echo "  Node with nid " . $node->nid . " saved!\n";
      $newnode = node_load($node->nid);
      node_save($newnode);
      unset($newnode);
//    }
  unset($node);
  $result ="";
  $result1 ="";
  $result2 ="";
  $result3 ="";
  $result4 ="";
  $result5 ="";
  $result6 ="";
  $result7 ="";
  $result8 ="";
  $result9 ="";
  $result10 ="";
  $result11="";
  $result12 ="";
    

   
  }   
   
/*  This PHP function will import CSV and convert it to an associative array based on the column headings in the first row. To use, simply call the function with a valid filename as the only parameter. The function will return an associative array of the import csv file contents.

example of usage:
$filename = "test.csv";
$csvArray = ImportCSV2Array($filename)
 
foreach ($csvArray as $row)
{
    echo $row['column1'];
    echo $row['column2'];
    echo $row['column3'];
}
 
*/
  
  
function ImportCSV2Array($filename){
  $row = 0;
  $col = 0;
 
  $handle = @fopen($filename, "r");
  if ($handle){
    while (($row = fgetcsv($handle, 4096)) !== false) {
      if (empty($fields)) {
        $fields = $row;
        continue;
      }
 
      foreach ($row as $k=>$value) {
        $results[$col][$fields[$k]] = $value;
      }
      $col++;
      unset($row);
    }
    if (!feof($handle)) {
      echo "Error: unexpected fgets() failn";
    }
  fclose($handle);
  }
 
  return $results;
}


function DMStoDEC($deg,$min,$sec){
// Converts DMS ( Degrees / minutes / seconds ) 
// to decimal format longitude / latitude
  return $deg+((($min*60)+($sec))/3600);
}    

function DECtoDMS($dec){
// Converts decimal longitude / latitude to DMS
// ( Degrees / minutes / seconds ) 

// This is the piece of code which may appear to 
// be inefficient, but to avoid issues with floating
// point math we extract the integer part and the float
// part by using a string function.

  $vars = explode(".",$dec);
  $deg = $vars[0];
  $tempma = "0.".$vars[1];

  $tempma = $tempma * 3600;
  $min = floor($tempma / 60);
  $sec = $tempma - ($min*60);

  return array("deg"=>$deg,"min"=>$min,"sec"=>$sec);
}    