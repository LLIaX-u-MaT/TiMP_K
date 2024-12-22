#pragma once

#include <stdexcept>
#include <string>
#include <system_error>

class criticalErr : public std::runtime_error {
public:
  criticalErr(const std::string &s) : std::runtime_error(s) {}
};

class nonCriticalErr : public std::runtime_error {
public:
  nonCriticalErr(const std::string s) : std::runtime_error(s) {}
};