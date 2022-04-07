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
function _well_known_uris_change_password_form() {
    $form['enabled'] = array(
        '#type' => 'checkbox',
        '#title' => t('Enable the <code>/.well-known/change-password</code> URL for your site'),
        '#default_value' => config_get('well_known_uris.change_password', 'enabled'),
        '#description' => t('When enabled the <code>/.well-known/change-password</code> path will redirect you to the change password page.'),
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
function _well_known_uris_change_password_form_validate($form, &$form_state) {
    if (!isset($form_state['values']['enabled'])) {
        form_set_error('enabled', t('The provided value is invalid.'));
    }
}

/**
 * Submit handler for the change-password form.
 *
 * @ingroup forms
 */
function _well_known_uris_change_password_form_submit($form, &$form_state) {
    config_set('well_known_uris.change_password', 'enabled', boolval($form_state['values']['enabled']));
}

/**
 * Page callback for the /.well-known/change-password path.
 */
function _well_known_uris_change_password_page() {
    if (user_is_logged_in()) {
        backdrop_goto('user/' . $GLOBALS['user']->uid . '/edit');
    }
    else {
        backdrop_goto('user/password');
    }
}
