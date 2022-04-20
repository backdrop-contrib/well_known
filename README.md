# Well-known URIs #

A [Backdrop CMS](https://backdropcms.org/) module which provides
some [well-known
services](https://en.wikipedia.org/wiki/Well-known_URI "Wikipedia").

The following *well-known* services are available:

* `change-password`: A service which can be used by password managers to
  find the *change/reset password* page for a website. Read the draft W3C
  specification: [A Well-Known URL for Changing Passwords](https://w3c.github.io/webappsec-change-password-url/).

## Requirements ##

You must replace your `.htaccess` file with the one provided by this
module at `htaccess/modified.htaccess`. This will be required until a
fix for "[issue
5583](https://github.com/backdrop/backdrop-issues/issues/5583#issue-1200228154)"
has made its way into your version of backdrop.

## Installation ##

* Install this module in the usual way, see the [contributed
  modules](https://docs.backdropcms.org/documentation/contributed-modules)
  of the user guide for details.

* Replace your `.htaccess` file with the one provided by this module
  at `htaccess/modified.htaccess`, e.g. `cp
  PATH_TO_CONTRIB_MODULES/well_known_uris/htaccess/modified.htaccess
  PATH_TO_DOCUMENT_ROOT/.htacess`.
  
* Visit the configuration page under Administration > Configuration > System >
  Well-known URIs (`admin/config/system/well-known-uris`) and
  configure the services you require.

<!-- Do not include if you have not created a wiki page. 
## Documentation ##

Additional documentation is located in [the -->
<!-- Wiki](https://github.com/backdrop-contrib/foo-project/wiki/Documentation).

## Further reading ##

-   Learn more about the [security.txt standard](https://securitytxt.org/)
-   Read the [draft RFC](https://tools.ietf.org/html/draft-foudil-securitytxt-02)

-->

## Issues ##

Bugs and feature requests should be reported in [the Issue
Queue](https://github.com/danieljrmay/well_known_uris/issues).

## Current Maintainers ##

* [Daniel J. R. May](https://github.com/danieljrmay).

## Credits ##

* Originally written for Backdrop CMS by [Daniel J. R. May](https://github.com/danieljrmay).

## License ##

This project is GPL v2 software. See the LICENSE.txt file in this
directory for complete text.
