<?php

/**
 * @file
 * Module file for well_known_uris.
 */

/**
 * Page callback for the admin page.
 */
function _well_known_uris_admin_page() {
    module_load_include('inc', 'system', 'system.admin');

    $markup = t(
        "<p>Well-known URIs are URLs of the form <code>@scheme://@hostname/.well-known/SUFFIX</code>, "
        . "where <code>SUFFIX</code> is replaced with the name of a <em>well-known service</em>. "
        . "They provide pre-defined locations to look for standardized information required by a "
        . "<em>well-known service</em>.</p><p>You can learn more about "
        . "<a href='https://en.wikipedia.org/wiki/Well-known_URI'>well-known URIs at Wikipedia</a>.</p>",
        array(
            '@scheme' => $_SERVER['REQUEST_SCHEME'],
            '@hostname' => $_SERVER['SERVER_NAME']
        )
    );
    $markup .= system_admin_menu_block_page();

    return $markup;
}
