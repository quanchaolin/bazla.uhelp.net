<?php 
/**
 *  This is for the computed field on the Recruitment Event 
 *  content type (Machine name: recruitment_event)
 *  that calculates the total number of students that 
 *  showed up to the event
 */

function computed_field_field_r_total_students_compute(&$entity_field, $entity_type, $entity, $field, $instance, $langcode, $items) {
  $philo_m = $entity->field_philo_m[LANGUAGE_NONE][0]['value'];
  $rheto_m = $entity->field_rheto_m[LANGUAGE_NONE][0]['value'];
  $seconde_m = $entity->field_seconde_m[LANGUAGE_NONE][0]['value'];
  $tre_eme_m = $entity->field_3eme_m[LANGUAGE_NONE][0]['value'];
  $nine_eme_m = $entity->field_9eme_m[LANGUAGE_NONE][0]['value'];
  $student_total_male = $philo_m + $rheto_m + $seconde_m + $tre_eme_m + $nine_eme_m;

  $philo_f = $entity->field_philo_f[LANGUAGE_NONE][0]['value'];
  $rheto_f = $entity->field_rheto_f[LANGUAGE_NONE][0]['value'];
  $seconde_f = $entity->field_seconde_f[LANGUAGE_NONE][0]['value'];
  $tre_eme_f = $entity->field_3eme_f[LANGUAGE_NONE][0]['value'];
  $nine_eme_f = $entity->field_9eme_f[LANGUAGE_NONE][0]['value'];
  $student_total_female = $philo_f + $rheto_f + $seconde_f + $tre_eme_f + $nine_eme_f;


  $student_total= $student_total_male + $student_total_female;
  $entity_field[0]['value'] = $student_total;
  return $student_total;
}

function computed_field_field_r_total_female_compute(&$entity_field, $entity_type, $entity, $field, $instance, $langcode, $items) {


    $philo_f = $entity->field_philo_f[LANGUAGE_NONE][0]['value'];
    $rheto_f = $entity->field_rheto_f[LANGUAGE_NONE][0]['value'];
    $seconde_f = $entity->field_seconde_f[LANGUAGE_NONE][0]['value'];
    $tre_eme_f = $entity->field_3eme_f[LANGUAGE_NONE][0]['value'];
    $nine_eme_f = $entity->field_9eme_f[LANGUAGE_NONE][0]['value'];
    $student_total_female = $philo_f + $rheto_f + $seconde_f + $tre_eme_f + $nine_eme_f;


    $entity_field[0]['value'] = $student_total_female;
    return $student_total_female;
}


function computed_field_field_r_total_male_compute(&$entity_field, $entity_type, $entity, $field, $instance, $langcode, $items) {

    $philo_m = $entity->field_philo_m[LANGUAGE_NONE][0]['value'];
    $rheto_m = $entity->field_rheto_m[LANGUAGE_NONE][0]['value'];
    $seconde_m = $entity->field_seconde_m[LANGUAGE_NONE][0]['value'];
    $tre_eme_m = $entity->field_3eme_m[LANGUAGE_NONE][0]['value'];
    $nine_eme_m = $entity->field_9eme_m[LANGUAGE_NONE][0]['value'];
    $student_total_male = $philo_m + $rheto_m + $seconde_m + $tre_eme_m + $nine_eme_m;


    $entity_field[0]['value'] = $student_total_male;
    return $student_total_male;
}