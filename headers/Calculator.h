#pragma once

#include <boost/numeric/conversion/cast.hpp>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <vector>

using namespace std;

class Calculator {
  int64_t finalResult;

public:
  Calculator(vector<int64_t> input_data);
  int64_t sendResult() const;
};