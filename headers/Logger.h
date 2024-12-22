#pragma once

#include "Errors.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

class Logger {
  static string getLocalDateTime(string s);
  string pathLogFile;

public:
  int writelog(string s);
  int setLogPath(string pathFile);
  Logger() { pathLogFile = " "; };
  Logger(string s) { pathLogFile = s; };
};
