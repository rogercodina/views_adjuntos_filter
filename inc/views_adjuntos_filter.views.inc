<?php

/**
 * @file
 * Views integration.
 */

/**
 * Implements hook_views_query_alter().
 *
 * Unica manera de modificar la query si el filtre estar exposat.
 */
function views_adjuntos_filter_views_query_alter(&$view, &$query) {

  if (!empty($view->exposed_raw_input)) {
    $has_doc_attached = isset($view->exposed_raw_input['has_doc_attached']) ? $view->exposed_raw_input['has_doc_attached'] : -1;

    if ($has_doc_attached == 0) { // No.

      // Subquery.
      $subquery_result = db_query('SELECT distinct(d.entity_id) FROM {field_data_field_documentos_adjuntos} d where deleted=0');
      $result = array();
      foreach ($subquery_result as $record) {
        $result[] = $record->entity_id;
      }
      $in_values = implode(',', $result);

      // Query alteration.      
      $query->add_where_expression(1, "node.nid NOT IN(:in) ", array(':in' => $in_values));
      
    }
    else if ($has_doc_attached == 1) { // Yes.

      // Query alteration.
      $join = new views_join();
      $join->table = 'field_data_field_documentos_adjuntos';
      $join->field = 'entity_id';
      $join->left_table = 'node';
      $join->left_field = 'nid';
      $join->type = 'INNER';
      $join->extra = array(
        array(
          'field' => 'deleted',
          'value' => '0',
        )
      );
      $query->add_relationship('field_data_field_documentos_adjuntos', $join, 'node');
    }

    //dpm($query);
  }
}
