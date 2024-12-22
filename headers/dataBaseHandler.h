#pragma once

#include "errors.h"
#include "logger.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>

class BaseConnector {
private:
  std::map<std::string, std::string> data_base;

public:
  int baseConnection(std::string base_file = "/etc/vcalc.conf");
  std::map<std::string, std::string> get_data() { return data_base; }
};