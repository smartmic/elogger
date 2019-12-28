# Energy logger data extraction

## Introduction

This tool will read binary files recorded by VOLTCRAFT ENERGY-LOGGER 3500 or 4000
and outputs the physical data in ASCII text format for easy plotting or
postprocessing. The current implementation is limited to the binary **DATA** file type of the Energy Logger.

## Specification

The underlying specification can be found at [Conrad](http://www2.produktinfo.conrad.com/datenblaetter/125000-149999/125323-da-01-en-Datenprotokoll_SD_card_file_Formatv1_2.pdf). Here you will also find the details about the **DATA** and **INFORMATION** file types which the Energy Logger provides.

## Usage

Run ``make`` on a GNU/Linux system (*BSD etc. not yet tested) and you will get an executable named **elogger** in *src/*.
To install it run ``make install`` as root and the executable will be installed in */usr/local/bin*. You can specify a different location with a prefix: ``make prefix=/usr install``.

The invocation is simply:

    elogger <binfile>

## Status

This is an very early version and needs some more functionality and documentation.

## Alternatives

There are a number of other open-source project out which will basically do the
same. Check them out if they suit your needs better. I wanted a compiled version
optimized for speed which can be deployed on servers.

http://wiki.td-er.nl/index.php?title=Energy_Logger_3500

http://cel4000.codeplex.com/

https://github.com/Lekensteyn/el4000

## Licence

Published under the GNU General Public License, see http://www.gnu.org/licenses/gpl.txt
