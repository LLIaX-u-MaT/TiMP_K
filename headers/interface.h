#pragma once

#include "calculator.h"
#include "dataBaseHandler.h"
#include "errors.h"
#include "logger.h"
#include "server.h"

#include <boost/program_options.hpp>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class UserInterface {
public:
  int interface(int argc, const char **argv);

private:
  struct Params {
    std::string d;
    std::string l;
    int p;
    
    bool p_default() const { return (p == 33333); }
    bool b_default() const { return (d == "/etc/vcalc.conf"); }
    bool l_default() const { return (l == "/var/log/vcalc.log"); }
  } params;
};
