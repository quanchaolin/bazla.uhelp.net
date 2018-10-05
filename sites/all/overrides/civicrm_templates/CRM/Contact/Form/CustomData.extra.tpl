

{literal}
<script>


  (function($) {

/**
 *  we could provide a set of fields per milestone type
 *  but here we have a number of fields to show only for the awards
 */


    function optionalFLDs(o,fldparent) {
      var fldclass = '.' + fldparent + 'fld';
        if (o === 'show') {
          $(fldclass).show();
        } else {
          $(fldclass).hide();
        }
    }

       // show / hide the fields on initial view
        if ($('[data-crm-custom="Life_Civic_Milestones:Milestone"] :selected').text() === 'Award') {
          optionalFLDs('show','award');
        } else {
          optionalFLDs('hide','award');
        }
       // toggle optional fields
       $('[data-crm-custom="Life_Civic_Milestones:Milestone"]').on('change', function() {
            if ( this.value == 'award') {
              optionalFLDs('show','award');
            }
            else {
              optionalFLDs('hide','award');
            }
          });
  })(CRM.$);



</script>{/literal}.


