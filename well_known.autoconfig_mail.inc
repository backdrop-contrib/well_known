<?php

/**
 * @file
 * Include file for the autoconfig/mail service.
 */

/**
 * Form for the autoconfig/mail admin page.
 *
 * @ingroup forms
 */
function well_known_autoconfig_mail_form() {
  $config = config('well_known.autoconfig_mail');

  $form['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable the <em>autoconfig/mail</em> service for your domain'),
    '#default_value' => $config->get('enabled'),
    '#description' => t('When enabled email clients can obtain their configuration from <a href="@href">@text</a>.',
    array(
      '@href' => '/.well-known/autoconfig/mail/config-v1.1.xml',
      '@text' => url('.well-known/autoconfig/mail/config-v1.1.xml', array('absolute' => TRUE)),
    ),
    ),
  );

  $form['domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Domain'),
    '#default_value' => $config->get('domain'),
    '#description' => t('The email domain, this would be <kbd>example.org</kbd> for an email addresses of the form <kbd>your.name@example.org</kbd>.'),
    '#required' => TRUE,
  );

  $form['display_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Display name'),
    '#default_value' => $config->get('display_name'),
    '#description' => t('Todo.'),
    '#required' => TRUE,
  );

  $form['display_short_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Short display name'),
    '#default_value' => $config->get('display_short_name'),
    '#description' => t('Todo.'),
    '#required' => TRUE,
  );

  $form['incoming_server'] = array(
    '#type' => 'details',
    '#summary' => t('Incoming server'),
    '#details' => 'This is some help',
    '#open' => TRUE,
  );
  $form['incoming_server']['incoming_server_type'] = array(
    '#type' => 'select',
    '#title' => t('Protocol'),
    '#options' => array(
      'imap' => t('IMAP'),
      'pop3' => t('POP3'),
    ),
    '#default_value' => $config->get('incoming_server_type'),
    '#description' => t('Todo'),
    '#required' => TRUE,
  );
  $form['incoming_server']['incoming_server_hostname'] = _well_known_hostname_form_array($config->get('incoming_server_hostname'), t('Todo'));
  $form['incoming_server']['incoming_server_port'] = _well_known_port_form_array($config->get('incoming_server_port'), t('Todo'));
  $form['incoming_server']['incoming_server_socket_type'] = _well_known_socket_type_form_array($config->get('incoming_server_socket_type'), t('Todo'));
  $form['incoming_server']['incoming_server_username'] = _well_known_username_form_array($config->get('incoming_server_username'), t('Todo'));
  $form['incoming_server']['incoming_server_authentication'] = _well_known_authentication_form_array($config->get('incoming_server_authentication'), t('Todo'));

  $form['outgoing_server'] = array(
    '#type' => 'details',
    '#summary' => t('Outgoing server'),
    '#details' => 'This is some help',
    '#open' => TRUE,
  );
  $form['outgoing_server']['outgoing_server_hostname'] = _well_known_hostname_form_array($config->get('outgoing_server_hostname'), t('Todo'));
  $form['outgoing_server']['outgoing_server_port'] = _well_known_port_form_array($config->get('outgoing_server_port'), t('Todo'));
  $form['outgoing_server']['outgoing_server_socket_type'] = _well_known_socket_type_form_array($config->get('outgoing_server_socket_type'), t('Todo'));
  $form['outgoing_server']['outgoing_server_username'] = _well_known_username_form_array($config->get('outgoing_server_username'), t('Todo'));
  $form['outgoing_server']['outgoing_server_authentication'] = _well_known_authentication_form_array($config->get('outgoing_server_authentication'), t('Todo'));

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Validation handler for the autoconfig/mail form.
 *
 * @ingroup forms
 */
function well_known_autoconfig_mail_form_validate($form, &$form_state) {
  if (!isset($form_state['values']['enabled'])) {
    form_set_error('enabled', t('The provided value is invalid.'));
  }

  // @todo domain  checkdnsrr(string $hostname, string $type = "MX"): bool also
  // must match this site's domain shouldn't it.
  // @todo display_name
  // @todo display_short_name
  if (
    !isset($form_state['values']['incoming_server_type']) ||
    !in_array(
      $form_state['values']['incoming_server_type'],
      array('imap', 'pop3')
    )
  ) {
    form_set_error('incoming_server_type', t('The provided incoming server protocol value is invalid.'));
  }

  // @todo incoming_server_hostname
  if (!isset($form_state['values']['incoming_server_port'])) {
    form_set_error('incoming_server_port', t('You must provide an incoming server port.'));
  }
  elseif (
    !filter_var($form_state['values']['incoming_server_port'], FILTER_VALIDATE_INT) ||
    $form_state['values']['incoming_server_port'] < 1 ||
    $form_state['values']['incoming_server_port'] > 65535
  ) {
    form_set_error('incoming_server_port', t('The incoming server port must be an integer between 1 and 65535 not "@incoming_server_port".', array('@incoming_server_port' => $form_state['values']['incoming_server_port'])));
  }
}

/**
 * Submit handler for the autoconfig/mail form.
 *
 * @ingroup forms
 */
function well_known_autoconfig_mail_form_submit($form, &$form_state) {
  $config = config('well_known.autoconfig_mail');
  $config->set('enabled', boolval($form_state['values']['enabled']));
  $config->set('domain', $form_state['values']['domain']);
  $config->set('display_name', $form_state['values']['display_name']);
  $config->set('display_short_name', $form_state['values']['display_short_name']);
  $config->set('incoming_server_type', $form_state['values']['incoming_server_type']);
  $config->set('incoming_server_hostname', $form_state['values']['incoming_server_hostname']);
  $config->set('incoming_server_port', $form_state['values']['incoming_server_port']);
  $config->set('incoming_server_socket_type', $form_state['values']['incoming_server_socket_type']);
  $config->set('incoming_server_username', $form_state['values']['incoming_server_username']);
  $config->set('incoming_server_authentication', $form_state['values']['incoming_server_authentication']);
  $config->set('outgoing_server_hostname', $form_state['values']['outgoing_server_hostname']);
  $config->set('outgoing_server_port', $form_state['values']['outgoing_server_port']);
  $config->set('outgoing_server_socket_type', $form_state['values']['outgoing_server_socket_type']);
  $config->set('outgoing_server_username', $form_state['values']['outgoing_server_username']);
  $config->set('outgoing_server_authentication', $form_state['values']['outgoing_server_authentication']);
  $config->save();
}

/**
 * Page callback for the /.well-known/autoconfig/mail/config-v1.1.xml path.
 */
function well_known_autoconfig_mail_page() {
  $config = config('well_known.autoconfig_mail');

  $xml_elements = array(
    array(
      'key' => 'clientConfig',
      'attributes' => array('version' => '1.1'),
      'value' => array(
        array(
          'key' => 'emailProvider',
          'attributes' => array('id' => $config->get('domain')),
          'value' => array(
            'domain' => $config->get('domain'),
            'displayName' => $config->get('display_name'),
            'displayShortName' => $config->get('display_short_name'),
            array(
              'key' => 'incomingServer',
              'attributes' => array('type' => $config->get('incoming_server_type')),
              'value' => array(
                'hostname' => $config->get('incoming_server_hostname'),
                'port' => $config->get('incoming_server_port'),
                'socketType' => $config->get('incoming_server_socket_type'),
                'username' => $config->get('incoming_server_username'),
                'authentication' => $config->get('incoming_server_authentication'),
              ),
            ),
            array(
              'key' => 'outgoingServer',
              'attributes' => array('type' => 'smtp'),
              'value' => array(
                'hostname' => $config->get('outgoing_server_hostname'),
                'port' => $config->get('outgoing_server_port'),
                'socketType' => $config->get('outgoing_server_socket_type'),
                'username' => $config->get('outgoing_server_username'),
                'authentication' => $config->get('outgoing_server_authentication'),
              ),
            ),
          ),
        ),
      ),
    ),
  );

  $output = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
  $output .= format_xml_elements($xml_elements);

  backdrop_add_http_header('Content-Type', 'application/xml; charset=utf-8');
  echo $output;
  backdrop_page_footer();
}

/**
 * Returns a hostname textfield form array.
 */
function _well_known_hostname_form_array($default_value, $description) {
  return array(
    '#type' => 'textfield',
    '#title' => t('Hostname'),
    '#default_value' => $default_value,
    '#description' => $description,
    '#required' => TRUE,
  );
}

/**
 * Returns a TCP/IP port number form array.
 */
function _well_known_port_form_array($default_value, $description) {
  return array(
    '#type' => 'number',
    '#title' => t('Port'),
    '#default_value' => $default_value,
    '#min' => 1,
    '#max' => 65535,
    '#description' => $description,
    '#size' => 5,
    '#required' => TRUE,
  );
}

/**
 * Returns a socket type select form array.
 */
function _well_known_socket_type_form_array($default_value, $description) {
  return array(
    '#type' => 'select',
    '#title' => t('Socket type'),
    '#options' => array(
      'plain' => t('Plain'),
      'SSL' => t('SSL'),
      'STARTTLS' => t('STARTTLS'),
    ),
    '#default_value' => $default_value,
    '#description' => $description,
    '#required' => TRUE,
  );
}

/**
 * Returns a username textfield form array.
 */
function _well_known_username_form_array($default_value, $description) {
  return array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#default_value' => $default_value,
    '#description' => $description,
    '#required' => TRUE,
  );
}

/**
 * Returns an authentication select form array.
 */
function _well_known_authentication_form_array($default_value, $description) {
  return array(
    '#type' => 'select',
    '#title' => t('Authentication'),
    '#options' => array(
      'password-cleartext' => t('Plaintext password'),
      'password-encrypted' => t('Encrypted password'),
      'NTLM' => t('NTLM'),
      'GSSAPI' => t('GSSAPI'),
      'client-IP-address' => t('Client IP address'),
      'TLS-client-cert' => t('TLS client certificate'),
      'OAuth2' => t('OAuth2'),
      'none' => t('No authentication'),
    ),
    '#default_value' => $default_value,
    '#description' => $description,
    '#required' => TRUE,
  );
}
