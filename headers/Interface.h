#pragma once

#include "Calculator.h"
#include "DataBaseHandler.h"
#include "Errors.h"
#include "Logger.h"
#include "Server.h"

#include <boost/program_options.hpp>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class UserInterface {
public:
  int interface(int argc, const char **argv);

private:
  struct Params {
    string d;
    string l;
    int p;
    
    bool p_default() const { return (p == 33333); }
    bool b_default() const { return (d == "/etc/vcalc.conf"); }
    bool l_default() const { return (l == "/var/log/vcalc.log"); }
  } params;
};
