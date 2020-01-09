# Energy logger data extraction

## Introduction

*elogger* will read binary files recorded by VOLTCRAFT ENERGY LOGGER 3500 or 4000
and outputs the physical data in ASCII text format for easy plotting or
postprocessing. The current implementation is limited to the binary **DATA** file type of the Energy Logger. 

This project is targeted to GNU/Linux or other Unix users who do not want to use the proprietary Windows-based data visualization program as offered by the vendor but prefer free (libre) software where possible. In case of the Energy Logger 4000, it is possible!

## Specification

The underlying specification can be found at [Conrad](http://www2.produktinfo.conrad.com/datenblaetter/125000-149999/125323-da-01-en-Datenprotokoll_SD_card_file_Formatv1_2.pdf). Here you will also find the details about the **DATA** and **INFORMATION** file types which the Energy Logger provides.

## Usage

To build and install the program, run

    ./configure
    make
    make install

``make install`` requires root privileges if you wish to install it under the default installation path */usr/local*. See ``./configure --help`` for alternative configurations.

Program invocation goes by simply calling:

    elogger <binfile>

## Status

This is a very early version and needs some more functionality and documentation.  Testing was done with an Energy Logger 4000.  Contributions are welcome!

## Alternatives

There are a number of other open-source project out which will basically do the
same. Check them out if they suit your needs better. 

http://wiki.td-er.nl/index.php?title=Energy_Logger_3500

http://cel4000.codeplex.com/

https://github.com/Lekensteyn/el4000

## Licence

Published under the GNU General Public License, see http://www.gnu.org/licenses/gpl.txt
