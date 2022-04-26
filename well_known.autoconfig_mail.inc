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
    '#title' => t('Enable the <em>autoconfig/mail</em> service'),
    '#default_value' => $config->get('enabled'),
    '#description' => t('Allow email clients to obtain their configuration from <a href="@href">@text</a>.',
    array(
      '@href' => '/.well-known/autoconfig/mail/config-v1.1.xml',
      '@text' => url('.well-known/autoconfig/mail/config-v1.1.xml', array('absolute' => TRUE)),
    ),
    ),

  );

  $autoconfig_url = str_replace('://', '://autoconfig.', url('mail/config-v1.1.xml', array('absolute' => TRUE)));

  $form['help'] = array(
    '#type' => 'help',
    '#prefix' => '<p>',
    '#markup' => t('The autoconfig-mail standard also defines a URL of the form <code>http(s)://autoconfig.example.com/mail/config-v1.1.xml</code> as a location to download the same configuration file. This site will provide the configuration file at <a href="@autocong_href">@autoconfig_text</a> <strong>only</strong> if it is configured to respond to requests to the <code>@autoconfig_domain</code> domain which requires appropriate DNS enteries and webserver configuration.',
    array(
      '@autoconfig_href' => $autoconfig_url,
      '@autoconfig_text' => $autoconfig_url,
      '@autoconfig_domain' => 'autconfig.' . $_SERVER['SERVER_NAME'],
    ),
    ),
    '#suffix' => '<p>',
  );

  $form['domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Domain'),
    '#default_value' => $config->get('domain'),
    '#description' => t('This would be <em>example.org</em> for an email addresses of the form <em>your.name@example.org</em>, it must match a domain which can be used to access this site.'),
    '#required' => TRUE,
    '#size' => 32,
    '#maxlength' => 64,
  );

  $form['display_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Display name'),
    '#default_value' => $config->get('display_name'),
    '#description' => t('Human readable description of this email service.'),
    '#required' => TRUE,
    '#size' => 64,
    '#maxlength' => 64,
  );

  $form['display_short_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Short display name'),
    '#default_value' => $config->get('display_short_name'),
    '#description' => t('Short form of the display name.'),
    '#required' => TRUE,
    '#size' => 32,
    '#maxlength' => 32,
  );

  $form['incoming_server'] = array(
    '#type' => 'details',
    '#summary' => t('Incoming server'),
    '#details' => 'The email server which clients download messages from.',
    '#open' => TRUE,
  );

  $form['incoming_server']['incoming_server_type'] = array(
    '#type' => 'select',
    '#title' => t('Protocol'),
    '#options' => _well_known_incoming_server_type_options(),
    '#default_value' => $config->get('incoming_server_type'),
    '#description' => t('The protocol email clients should connect with.'),
    '#required' => TRUE,
  );

  $form['incoming_server']['incoming_server_hostname'] = _well_known_hostname_form_array(
    $config->get('incoming_server_hostname'),
    t('The fully qualified domain name of the server.')
  );

  $form['incoming_server']['incoming_server_port'] = _well_known_port_form_array(
    $config->get('incoming_server_port'),
    t('The TCP port which email clients should connect to.')
  );

  $form['incoming_server']['incoming_server_socket_type'] = _well_known_socket_type_form_array(
    $config->get('incoming_server_socket_type'),
    t('The encryption methodology email clients should use when connecting, <kbd>Plain</kbd> indicates no encryption.')
  );

  $form['incoming_server']['incoming_server_username'] = _well_known_username_form_array(
    $config->get('incoming_server_username'),
    t('The following placeholders can be used: <code>%EMAILADDRESS%</code> (full email address of the user), <code>%EMAILLOCALPART%</code> (the part of the email address before @), <code>%EMAILDOMAIN%</code> (the part of the email address after @).')
  );

  $form['incoming_server']['incoming_server_authentication'] = _well_known_authentication_form_array(
    $config->get('incoming_server_authentication'),
    t('The authentication method email clients should use when connecting.')
  );

  $form['outgoing_server'] = array(
    '#type' => 'details',
    '#summary' => t('Outgoing server'),
    '#details' => 'The email server which clients submit email to.',
    '#open' => TRUE,
  );

  $form['outgoing_server']['outgoing_server_hostname'] = _well_known_hostname_form_array(
    $config->get('outgoing_server_hostname'),
    t('The fully qualified domain name of the server.')
  );

  $form['outgoing_server']['outgoing_server_port'] = _well_known_port_form_array(
    $config->get('outgoing_server_port'),
    t('The TCP port which email clients should connect to.')
  );

  $form['outgoing_server']['outgoing_server_socket_type'] = _well_known_socket_type_form_array(
    $config->get('outgoing_server_socket_type'),
    t('The encryption methodology email clients should use when connecting, <kbd>Plain</kbd> indicates no encryption.')
  );

  $form['outgoing_server']['outgoing_server_username'] = _well_known_username_form_array(
    $config->get('outgoing_server_username'),
    t('The following placeholders can be used: <code>%EMAILADDRESS%</code> (full email address of the user), <code>%EMAILLOCALPART%</code> (the part of the email address before @), <code>%EMAILDOMAIN%</code> (the part of the email address after @).')
  );

  $form['outgoing_server']['outgoing_server_authentication'] = _well_known_authentication_form_array(
    $config->get('outgoing_server_authentication'),
    t('The authentication method email clients should use when connecting.')
  );

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

  if (!isset($form_state['values']['domain'])
  || filter_var($form_state['values']['domain'], FILTER_VALIDATE_DOMAIN, FILTER_FLAG_HOSTNAME) === FALSE) {
    form_set_error('domain', t('The provided domain is invalid.'));
  }

  if (!isset($form_state['values']['display_name'])
  || strlen($form_state['values']['display_name']) == 0
  || strlen($form_state['values']['display_name']) > 64) {
    form_set_error('display_name', t('The provided display name is invalid.'));
  }

  if (!isset($form_state['values']['display_short_name'])
  || strlen($form_state['values']['display_short_name']) == 0
  || strlen($form_state['values']['display_short_name']) > 64) {
    form_set_error('display_short_name', t('The provided display name is invalid.'));
  }

  if (!isset($form_state['values']['incoming_server_type'])
  || !in_array(
    $form_state['values']['incoming_server_type'],
    array_keys(_well_known_incoming_server_type_options())
  )) {
    form_set_error('incoming_server_type', t('The provided incoming server type is invalid.'));
  }

  if (!isset($form_state['values']['incoming_server_hostname'])
  || filter_var($form_state['values']['incoming_server_hostname'], FILTER_VALIDATE_DOMAIN, FILTER_FLAG_HOSTNAME) === FALSE) {
    form_set_error('incoming_server_hostname', t('The provided incoming server hostname is invalid.'));
  }

  if (!isset($form_state['values']['incoming_server_port'])
  || !_well_known_valid_port($form_state['values']['incoming_server_port'])) {
    form_set_error('incoming_server_port', t('The incoming server port must be an integer between 1 and 65535.'));
  }

  if (!isset($form_state['values']['incoming_server_socket_type'])
  || !in_array(
    $form_state['values']['incoming_server_socket_type'],
    array_keys(_well_known_server_socket_type_options())
  )) {
    form_set_error('incoming_server_type', t('The provided incoming server socket type is invalid.'));
  }

  if (!isset($form_state['values']['incoming_server_username'])
  || strlen($form_state['values']['incoming_server_username']) == 0
  || strlen($form_state['values']['incoming_server_username']) > 64) {
    form_set_error('incoming_server_username', t('The provided incoming server username is invalid.'));
  }

  if (!isset($form_state['values']['incoming_server_authentication'])
  || !in_array(
    $form_state['values']['incoming_server_authentication'],
    array_keys(_well_known_server_authentication_options())
  )) {
    form_set_error('incoming_server_authentication', t('The provided incoming server authentication is invalid.'));
  }

  if (!isset($form_state['values']['outgoing_server_hostname'])
  || filter_var($form_state['values']['outgoing_server_hostname'], FILTER_VALIDATE_DOMAIN, FILTER_FLAG_HOSTNAME) === FALSE) {
    form_set_error('outgoing_server_hostname', t('The provided outgoing server hostname is invalid.'));
  }

  if (!isset($form_state['values']['outgoing_server_port'])
  || !_well_known_valid_port($form_state['values']['outgoing_server_port'])) {
    form_set_error('outgoing_server_port', t('The outgoing server port must be an integer between 1 and 65535.'));
  }

  if (!isset($form_state['values']['outgoing_server_socket_type'])
  || !in_array(
    $form_state['values']['outgoing_server_socket_type'],
    array_keys(_well_known_server_socket_type_options())
  )) {
    form_set_error('outgoing_server_type', t('The provided outgoing server socket type is invalid.'));
  }

  if (!isset($form_state['values']['outgoing_server_username'])
  || strlen($form_state['values']['outgoing_server_username']) == 0
  || strlen($form_state['values']['outgoing_server_username']) > 64) {
    form_set_error('outgoing_server_username', t('The provided outgoing server username is invalid.'));
  }

  if (!isset($form_state['values']['outgoing_server_authentication'])
  || !in_array(
    $form_state['values']['outgoing_server_authentication'],
    array_keys(_well_known_server_authentication_options())
  )) {
    form_set_error('outgoing_server_authentication', t('The provided outgoing server authentication is invalid.'));
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
  /* The email client can provide an email address as a 'emailaddress' query
   * parameter. This can be used for advanced per email configuration, but this
   * has not been implemented yet. The following commented-out line is a
   * placeholder in case we ever want to implement this advanced feature in the
   * future.
   *
   * $provided_email_address = _well_known_provided_email_address();
   */

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
 * Return the options for the incoming server type.
 */
function _well_known_incoming_server_type_options() {
  return array(
    'imap' => t('IMAP'),
    'pop3' => t('POP3'),
  );
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
    '#size' => 32,
    '#maxlength' => 64,
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
    '#options' => _well_known_server_socket_type_options(),
    '#default_value' => $default_value,
    '#description' => $description,
    '#required' => TRUE,
  );
}

/**
 * Return the options for the socket type.
 */
function _well_known_server_socket_type_options() {
  return array(
    'plain' => t('Plain'),
    'SSL' => t('SSL'),
    'STARTTLS' => t('STARTTLS'),
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
    '#size' => 32,
    '#maxlength' => 64,
  );
}

/**
 * Returns an authentication select form array.
 */
function _well_known_authentication_form_array($default_value, $description) {
  return array(
    '#type' => 'select',
    '#title' => t('Authentication'),
    '#options' => _well_known_server_authentication_options(),
    '#default_value' => $default_value,
    '#description' => $description,
    '#required' => TRUE,
  );
}

/**
 * Return the options for the server authenticaiton method.
 */
function _well_known_server_authentication_options() {
  return array(
    'password-cleartext' => t('Plaintext password'),
    'password-encrypted' => t('Encrypted password'),
    'NTLM' => t('NTLM'),
    'GSSAPI' => t('GSSAPI'),
    'client-IP-address' => t('Client IP address'),
    'TLS-client-cert' => t('TLS client certificate'),
    'OAuth2' => t('OAuth2'),
    'none' => t('No authentication'),
  );
}

/**
 * Validate an TCP/UDP IP port number.
 */
function _well_known_valid_port($port) {
  if (filter_var($port, FILTER_VALIDATE_INT) && $port >= 1 && $port <= 65535) {
    return TRUE;
  }

  return FALSE;
}

/**
 * Return any valid email address provided by the GET request.
 *
 * If no email is provided or it is not valid then FALSE will be returned.
 */
function _well_known_provided_email_address() {
  $query_parameters = backdrop_get_query_parameters();

  if (isset($query_parameters['emailaddress']) && valid_email_address($query_parameters['emailaddress'])) {
    return $query_parameters['emailaddress'];
  }

  return FALSE;
}
