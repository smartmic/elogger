/**
 *    elogger - conversion of VOLTCRAFTs ENERGY-LOGGER binary data logger files to human readable text
 *
 *    Copyright (C) 2014 - 2015  Martin Michel
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>./ elogger.cpp
 */
#include <fstream>
#include <iostream>
#include <cstring>
#include <ctime>

#include "measurement.h"

using namespace std;

char *Measurement::buffer;
struct tm
Measurement::ts;

int main(int argc, char *argv[]) {
  Measurement entry0;

  try {
    if (argc != 2) {
      throw "No distinct file specified.";
    }

    char *filename[sizeof(&argv[1])];
    *filename = argv[1];

    if (entry0.getBuffer(*filename) == 1) {
      throw "File parsing failed.";
    }

    bool start  = true;
    bool finish = false;

    while (finish == false) {
      if (start == true) {
        entry0.firstStamp();
        start = false;
      }
      else {
        entry0.getTimestamp();
      }

      entry0.getVoltage();
      entry0.getCurrent();
      entry0.getPF();
      cout << endl;
      entry0.addTimedelta(60);
      finish = entry0.endCriteria();
    }

    return(0);
  }
  catch (const char *str) {
    cout << "Exception: " << str << endl;
    return(1);
  }
}
