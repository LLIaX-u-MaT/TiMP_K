#pragma once

#include <stdexcept>
#include <string>
#include <system_error>

using namespace std;

class criticalErr : public runtime_error {
public:
  criticalErr(const string &s) : runtime_error(s) {}
};

class nonCriticalErr : public runtime_error {
public:
  nonCriticalErr(const string s) : runtime_error(s) {}
};