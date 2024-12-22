#pragma once

#include "Errors.h"
#include "Logger.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class BaseConnector {
private:
  map<string, string> dataBase;

public:
  int baseConnection(string baseFile = "/etc/vcalc.conf");
  map<string, string> get_data() { return dataBase; }
};
