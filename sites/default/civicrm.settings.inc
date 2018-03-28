<?php
/**
 * This file specifies configuration that should not be version controlled.
 * For more documentation of these settings, see civicrm.settings.inc
 */

//define( 'CIVICRM_MAIL_LOG', '/var/www/justassociates.org/sites/all/files/civicrm/mail.log' );

/**
 * If you have multilingual site and you are using the "inherit CMS language"
 * configuration option, but wish to, for example, use fr_CA instead of the
 * default fr_FR (for French), set one or more of the constants below to an
 * appropriate regional value.
 */
//define('CIVICRM_LANGUAGE_MAPPING_ES', 'es_MX');


/**
  * -----------------------------------------------------------------------------------
  * Customizations for Overriding Server Directory and URL Settings                    |
  * changes necessary for production and testing sites
  **************************************************************************************
  */
  



# -------------- Upload Directories -------------------------------------
# Temporary Files (System Settings > Directories)
$civicrm_setting['Directory Preferences']['uploadDir'] ='/var/www/html/bazla-stage.openflows.com/sites/default/files/civicrm/upload/'; 

# Images (System Settings > Directories)
$civicrm_setting['Directory Preferences']['imageUploadDir'] ='/var/www/html/bazla-stage.openflows.com/sites/default/files/civicrm/persist/contribute/';
 
# Custom Files (System Settings > Directories)
$civicrm_setting['Directory Preferences']['customFileUploadDir'] = '/var/www/html/bazla-stage.openflows.com/sites/default/files/civicrm/custom/';

# Custom Templates (System Settings > Directories) - $civicrm_setting['Directory Preferences']['customTemplateDir'] = '/var/www/html/openflows/sites/all/overrides/civicrm_templates/';
# Custom PHP Path Directory (System Settings > Directories) - $civicrm_setting['Directory Preferences']['customPHPPathDir'] ='/var/www/html/openflows/sites/all/overrides/civicrm_php';

# -------------- Resource URLs -------------------------------------
# CiviCRM Resource URL (System Settings > Resource URLs)
$civicrm_setting['URL Preferences']['userFrameworkResourceURL'] = 'http://bazla-stage.openflows.com/sites/all/modules/contrib/civicrm';
  
# Image Upload URL (System Settings > Resource URLs)
$civicrm_setting['URL Preferences']['imageUploadURL'] = 'http://bazla-stage.openflows.com/sites/default/files/civicrm/custom/';

# Custom CiviCRM CSS URL (System Settings > Resource URLs) - 
# $civicrm_setting['URL Preferences']['customCSSURL'] = 'http://bazla-stage.openflows.com/sites/default/files/civicrm/custom';
# Extensions Directory (System Settings > Directories) - $civicrm_setting['Directory Preferences']['extensionsDir'] = ' ';

//require_once 'CRM/Core/ClassLoader.php';
//CRM_Core_ClassLoader::singleton()->register();
