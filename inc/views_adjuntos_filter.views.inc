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
  if (!empty($view->exposed_raw_input['has_doc_attached'])) {
    $has_doc_attached = !empty($view->exposed_raw_input['has_doc_attached']) ? $view->exposed_raw_input['has_doc_attached'] : -1;

    if ($has_doc_attached == 0) { // No.
      $join = new views_join();
      $join->table = 'field_data_field_documentos_adjuntos';
      $join->field = 'entity_id';
      $join->left_table = 'node';
      $join->left_field = 'nid';
      $join->type = 'INNER';
      $join->extra = array(
        array(
          'field' => 'deleted',
          'value' => '1',
        )
      );
      $query->add_relationship('field_data_field_documentos_adjuntos', $join, 'node');
    }
    else if ($has_doc_attached == 1) { // Yes.
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


/**
 * Implements hook_search_api_views_query_alter().
 *
 * Unica manera de modificar la query si el filtre estar exposat.
 */
function views_adjuntos_filter_search_api_views_query_alter(&$view, &$query) {
  /*
   * IMPORTANTE: Esta funcion SOLO se ejecuta para las vistas de Search API.
   */
 
  if (!empty($view->exposed_raw_input['has_doc_attached'])) {
    $has_doc_attached = !empty($view->exposed_raw_input['has_doc_attached']) ? $view->exposed_raw_input['has_doc_attached'] : -1;

    /**
	   * IMPORTANT: Use field names that appear in admin/config/search/search_api/index/[INDEX_NAME]/fields
	   *
	   * NOTE: Search API stores dates as timestamps
	   *
	   * http://enzolutions.com/articles/2015/06/10/how-to-customize-a-search-api-filters-in-drupal-7/
	   * https://github.com/markaspot/mark-a-spot/blob/master/profiles/markaspot/modules/mark_a_spot/modules/markaspot_radar/markaspot_radar.module
	   */

    // TODO: Aun no se ha probado este codigo porque solo se ha usado en vistas normales.
    $main_filter = $query->createFilter('AND');
    if ($has_doc_attached == 0) { // No.
      $main_filter->condition('field_documentos_adjuntos', 'NULL' , 'IS');
    }
    else if ($has_doc_attached == 1) { // Yes.
      $main_filter->condition('field_documentos_adjuntos', 'NULL' , '!=');
    }

    $query->filter($main_filter);

    //dpm($query);
  }
}
