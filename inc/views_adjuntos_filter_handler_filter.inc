<?php

class views_adjuntos_filter_handler_filter extends views_plugin_exposed_form_basic {

  /**
   * Implements views_handler_filter#can_expose().
   */
  function can_expose() {
    return TRUE;
  }

  /**
   * Implements views_handler_filter#is_a_group().
   */
  function is_a_group() {
    return FALSE;
  }

  function is_exposed() {
    return TRUE;
  }

  function access() {
    return TRUE;
  }

  function pre_query() {}

  /**
   * Check to see if input from the exposed filters should change
   * the behavior of this filter.
   */
  function accept_exposed_input($input) {
    return FALSE; 
  }

  /**
   * Returns TRUE if users can select multiple groups items of a
   * grouped exposed filter.
   */
  function multiple_exposed_input() {
    return FALSE;
  }

  function store_exposed_input($input, $status) {}

  /**
   * Exposed filter rendering.
   */
  function exposed_form(&$form, &$form_state) {

    $form['has_doc_attached'] = array(
       '#type' => 'select',
       '#title' => t('¿Tiene documento adjunto?'),
       '#options' => array(
          -1 => t('- Any -'),
          0 => t('No'),
          1 => t('Yes'),
       ),
       //'#default_value' => $form_state['values'],
    );
  }

  /**
   * Exposed filter validation.
   */
  function exposed_validate(&$form, &$form_state) {
    
  }

  /**
   * Exposed filter submit.
   */
  function exposed_submit(&$form, &$form_state) {
    
  }

  /**
   * Tell the renderer about our exposed form. This only needs to be
   * overridden for particularly complex forms. And maybe not even then.
   *
   * @return array|null
   *   For standard exposed filters. An array with the following keys:
   *   - operator: The $form key of the operator. Set to NULL if no operator.
   *   - value: The $form key of the value. Set to NULL if no value.
   *   - label: The label to use for this piece.
   *   For grouped exposed filters. An array with the following keys:
   *   - value: The $form key of the value. Set to NULL if no value.
   *   - label: The label to use for this piece.
   */
  function exposed_info() {
    return array(
      'operator' => NULL,
      'value' => 'has_doc_attached',
      'label' => '¿Tiene documento adjunto?',
      'description' => '',
    );
  }

  /**
   * Add this filter to the query.
   *
   * See hook_views_query_alter.
   */
  /*function query() { //$this->query... }*/

}
