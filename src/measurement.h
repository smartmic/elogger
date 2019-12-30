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

#define N    18

class Measurement {
private:
  static char *buffer;
  static struct tm ts;
  char timestamp[N];
  float voltage;
  float current;
  float cosphi;
public:
  Measurement();
  ~Measurement();
  int getBuffer(char *filename);
  int firstStamp(void);
  int getTimestamp(void);
  int addTimedelta(int deltasec);
  int getVoltage(void);
  int getCurrent(void);
  int getPF(void);
  bool endCriteria(void);
  void saveEntry(void);
};
