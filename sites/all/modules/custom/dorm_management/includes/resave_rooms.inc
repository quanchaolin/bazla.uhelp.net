<?php

/**        
 * will resave all nodes of type dorm room
*/
function alumni_dashboard_resave_room_nodes() {
  $form['dorm_room_fieldset'] = 
    array(
	  '#type' => 'fieldset',
	  );
  $form['dorm_room_fieldset']['submit_button'] = 
    array(
	  '#type' => 'submit',
	  '#value' => t('Resave Dorm Rooms'),
	  );
  return $form;

}
function alumni_dashboard_resave_room_nodes_submit() {
  $sql = "SELECT nid from node where type = 'dorm_bed'";
  $results = db_query($sql);
  while ($result = $results->fetchObject()) {
    $nid = $result->nid;
    $room = node_load($nid);
    node_save($room);
  }
}