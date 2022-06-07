# Well-known #

A [Backdrop CMS](https://backdropcms.org/) module which provides
some [well-known
services](https://en.wikipedia.org/wiki/Well-known_URI "Wikipedia").

The following *well-known* services are available:

* `change-password`: A service which can be used by password managers
  to find a website’s *change password* page. Read the draft W3C
  specification: [A Well-Known URL for Changing
  Passwords](https://w3c.github.io/webappsec-change-password-url/).

* `autoconfig/mail`: Autoconfiguration service for email clients like
  Thunderbird, Evolution, etc. Read more about [Thunderbird
  autoconfiguration](https://wiki.mozilla.org/Thunderbird:Autoconfiguration)
  and the associated [configuration file format](https://wiki.mozilla.org/Thunderbird:Autoconfiguration:ConfigFileFormat).

## Requirements ##

If you are using backdrop version 1.22.0 or later then there are no
special requirements.

However, if you are using backdrop version 1.21.4 or earlier then you
must replace your `.htaccess` file with the one provided by this
module at `htaccess/modified.htaccess`. This is because the original
`.htaccess` file does not allow backdrop to serve pages starting with
the `.well-known`path, see [issue
5583](https://github.com/backdrop/backdrop-issues/issues/5583#issue-1200228154).

**Note:** `htaccess/original.htaccess` is a copy of the default
`.htaccess` file from backdrop version 1.21.4 which
`modified.htaccess` is based on, it is only present for comparison
purposes.

## Installation ##

* Install this module in the usual way, see the [contributed
  modules](https://docs.backdropcms.org/documentation/contributed-modules)
  of the user guide for details.

* If you are using backdrop version 1.21.4 or earlier then you must
  replace your `.htaccess` file with the one provided by this module
  at `htaccess/modified.htaccess`, e.g. `cp
  PATH_TO_CONTRIB_MODULES/well_known/htaccess/modified.htaccess
  PATH_TO_DOCUMENT_ROOT/.htacess`.
  
* Visit the configuration page under Administration > Configuration > System >
  Well-known URIs (`admin/config/system/well-known`) and
  configure the services you require.

## Issues ##

Bugs and feature requests should be reported in [the Issue
Queue](https://github.com/backdrop-contrib/well_known/issues).

## Current Maintainers ##

* [Daniel J. R. May](https://github.com/danieljrmay).

## Credits ##

* Originally written for Backdrop CMS by [Daniel J. R. May](https://github.com/danieljrmay).

## License ##

This project is GPL v2 software. See the LICENSE.txt file in this
directory for complete text.

## Further Reading ##

* [Wikipedia](https://en.wikipedia.org/wiki/Well-known_URI) has a good
  list of the various *well-known* services.
* The [draft *change-password*
  specification](https://w3c.github.io/webappsec-change-password-url/).
* The [thunderbird *autoconfig/mail* project
  page](https://wiki.mozilla.org/Thunderbird:Autoconfiguration) and
  associated [configuration file format
  specification](https://wiki.mozilla.org/Thunderbird:Autoconfiguration:ConfigFileFormat).
