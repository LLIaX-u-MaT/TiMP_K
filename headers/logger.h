#pragma once

#include "errors.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

class Logger {
  static std::string getCurrentDateTime(std::string s);
  std::string path_to_logfile;

public:
  int writelog(std::string s);
  int set_path(std::string path_file);
  Logger() { path_to_logfile = " "; };
  Logger(std::string s) { path_to_logfile = s; };
};