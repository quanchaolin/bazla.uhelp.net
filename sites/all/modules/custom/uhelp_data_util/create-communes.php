<?php 
//load spreadsheet into an array
 //   $filename = "help-rec-data-sample.csv";

 $filename = "/var/www/openflows/sites/all/modules/custom/uhelp_data_util/help_communes.csv";
  $csvArray = ImportCSV2Array($filename);

  civicrm_initialize();
//loop over array 


  foreach ($csvArray as $row){

    print_r($row[Commune]);
   

    $result = civicrm_api3('OptionValue', 'create', array(
							  'sequential' => 1,
							  'option_group_id' => 91,
							  'value' => $row[Commune],
							  'label' => $row[Commune],
							  ));    

  }


//set values for creating civi org contact 
//sub-contact type secondary school 

//clean and alter gps values
// so they are decimal, not hour min sec 

   
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