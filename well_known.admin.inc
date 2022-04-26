<?php

/**
 * @file
 * Admin page callbacks for the well-known module.
 */

/**
 * Page callback for the admin page.
 */
function well_known_admin_page() {
  module_load_include('inc', 'system', 'system.admin');

  $markup = t("<p>Well-known services provide standardized information at URLs of the form <code>@scheme://@hostname/.well-known/SUFFIX</code>, where <code>SUFFIX</code> is typically the name of the service. There are several <abbr title=\"Internet Assigned Numbers Authority\">IANA</abbr> registered <a href='https://en.wikipedia.org/wiki/Well-known_URI'>well-known services</a>, a selection of which can be enabled and configured below.</p>",
    array(
      '@scheme' => $_SERVER['REQUEST_SCHEME'],
      '@hostname' => $_SERVER['SERVER_NAME'],
    )
  );
  $markup .= system_admin_menu_block_page();

  return $markup;
}
