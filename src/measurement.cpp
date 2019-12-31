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

#include <array>
#include "measurement.h"

using namespace std;

Measurement::Measurement() {
}

Measurement::~Measurement() {
}

int Measurement::firstStamp(void)
{
  unsigned int i;
  array < unsigned int, 3 > startchar;
  array < unsigned int, 3 > specdatastart {
  224, 197, 234};

  unsigned int datecode;

  memset(&ts, 0, sizeof(tm));

  for (i = 0; i <= 2; ++i) {
    startchar[i] = static_cast < unsigned int >(*buffer & 0xFF);
//       cout << uppercase << hex << startchar[i] << " ";
    buffer++;
  }
  // cout << endl;
  if (startchar != specdatastart)
    throw "Provided file is not compliant to specification!";

  for (i = 3; i <= 7; i++) {
    datecode = static_cast < unsigned int >(*buffer & 0xFF);
    switch (i) {
      case 3:
        ts.tm_mon = datecode - 1;
      case 4:
        ts.tm_mday = datecode;
      case 5:
        ts.tm_year = datecode - 1900 + 2000;
      case 6:
        ts.tm_hour = datecode;
      case 7:
        ts.tm_min = datecode;
    }

    buffer++;
  }

  mktime(&ts);
  getTimestamp();
  return(0);
}

int Measurement::getTimestamp(void) {
  if (strftime(timestamp, sizeof(timestamp) - 1, "%Y-%m-%dT%H:%M", &ts) > 0) {
    cout << timestamp;
  }
  else {
    cerr << "strftime failed." << endl;
    return(1);
  }

  return(0);
}

int Measurement::addTimedelta(int deltasec) {
  time_t next = mktime(&ts) + deltasec;

  ts = *localtime(&next);
  return(0);
}

int Measurement::getVoltage(void) {
  int          i;
  unsigned int voltcode[2] = { 0, 0 };

  for (i = 0; i <= 1; i++) {
    voltcode[i] = static_cast <unsigned int>(*buffer & 0xFF);
    buffer++;
  }

  unsigned int volt = (voltcode[0] << 8 | voltcode[1]);
  voltage = (float)volt / 10;

  if (voltage > 108.0 && voltage < 300.0) {
    cout << " " << voltage;
  }
  else {
    cerr << "\ninvalid voltage at " << hex << &buffer << endl;
    return(1);
  }

  return(0);
}

int Measurement::getCurrent(void) {
  int          i;
  unsigned int currcode[2] = { 0, 0 };

  for (i = 0; i <= 1; i++) {
    currcode[i] = static_cast <unsigned int>(*buffer & 0xFF);
    buffer++;
  }

  unsigned int curr = (currcode[0] << 8 | currcode[1]);
  current = (float)curr / 1000;

  if (current >= 0.0) {
    cout << " " << current;
  }
  else {
    cerr << "\ninvalid current at " << hex << &buffer << endl;
    return(1);
  }

  return(0);
}

int Measurement::getPF(void) {
  unsigned int pf = 0;

  pf = static_cast <unsigned int>(*buffer & 0xFF);
  buffer++;
  cosphi = (float)pf / 100;

  if (cosphi >= 0.0 && cosphi <= 1.0) {
    cout << " " << cosphi;
  }
  else {
    cerr << "\ninvalid power factor at " << hex << &buffer << endl;
    return(1);
  }

  return(0);
}

void Measurement::saveEntry(void) {
}

int Measurement::getBuffer(char *filename) {
  ifstream           inputfile;
  ifstream::pos_type size;

  // alternative: int size with typecast (int)

  inputfile.open(filename, ios::in | ios::binary | ios::ate);

  if (inputfile.good()) {
    size   = inputfile.tellg();
    buffer = new char[size];
    inputfile.seekg(0, ios::beg);
    inputfile.read(buffer, size);
    inputfile.close();
    return(0);
  }
  else {
    return(1);
  }
}

bool Measurement::endCriteria(void) {
  char *preview = new char[4];

  memcpy(preview, buffer, 4);
  unsigned int checkcode[4] = { 0, 0, 0, 0 };

  for (int i = 0; i < 4; i++) {
    checkcode[i] = static_cast <unsigned int>(*preview & 0xFF);
    preview++;
  }

  unsigned int eof =
    (checkcode[0] << 24) | (checkcode[1] << 16) | (checkcode[2] << 8) |
    checkcode[3];

  if (eof == 0xFFFFFFFF) {
    return(true);
  }
  else {
    return(false);
  }
}
