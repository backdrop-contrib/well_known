<?php

/**
 * @file
 * Include file for the change-password service.
 */

/**
 * Form for the change-password admin page.
 *
 * @ingroup forms
 */
function well_known_change_password_form() {
  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable the <em>change-password</em> service'),
    '#default_value' => config_get('well_known.change_password', 'enabled'),
    '#description' => t('When enabled the URL <a href="@href">@text</a> will redirect to a page which allows a user to update their password.',
    array(
      '@href' => '/.well-known/change-password',
      '@text' => url('.well-known/change-password', array('absolute' => TRUE)),
    ),
    ),

  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Validation handler for the change-password form.
 *
 * @ingroup forms
 */
function well_known_change_password_form_validate($form, &$form_state) {
  if (!isset($form_state['values']['enabled'])) {
    form_set_error('enabled', t('The provided value is invalid.'));
  }
}

/**
 * Submit handler for the change-password form.
 *
 * @ingroup forms
 */
function well_known_change_password_form_submit($form, &$form_state) {
  config_set('well_known.change_password', 'enabled', boolval($form_state['values']['enabled']));
}

/**
 * Page callback for the /.well-known/change-password path.
 */
function well_known_change_password_page() {
  if (user_is_logged_in()) {
    backdrop_goto('user/' . $GLOBALS['user']->uid . '/edit');
  }
  else {
    backdrop_goto('user/login', array('query' => array('destination' => '.well-known/change-password')));
  }
}
