<?php

class views_adjuntos_filter_handler_filter extends views_handler_filter {

  function can_expose() { return TRUE; }

  /**
   * Implements views_object#admin_summary().
   */
  function admin_summary() {
    return t('Exposed: ¿Tiene documento adjunto?');
  }

  /**
   * Options form subform for setting exposed filter options.
   */
  function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);

    $form['has_doc_attached'] = array(
       '#type' => 'select',
       '#title' => t('¿Tiene documento adjunto?'),
       '#options' => array(
          -1 => t('- Any -'),
          0 => t('No'),
          1 => t('Yes'),
       ),
       '#default_value' => !empty($form_state['values']['has_doc_attached'])
    );
  }

  /**
   * Alters Views query when filter is used.
   * Nomes s'executa si el filtre no es exposat.
   * Per aixo hem implementat el hook_views_query_alter a l'altre fitxer.
   */
  /*function query() {}*/

}
