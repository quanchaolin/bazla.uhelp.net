<?php

/**        
 * Function is passed an entity and will return a single value without 
 * throwing warnings                                                        
*/
function dorm_management_get_entity_single_value_field($entity,$field,$index){
  $value =
    (isset($entity->{$field}) &&
     isset($entity->{$field}[LANGUAGE_NONE]) &&
     isset($entity->{$field}[LANGUAGE_NONE][0])) ?
      $entity->{$field}[LANGUAGE_NONE][0][$index] : NULL;
  
  return $value;
}
