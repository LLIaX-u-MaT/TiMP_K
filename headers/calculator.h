#pragma once

#include <boost/numeric/conversion/cast.hpp>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <vector>

class Calculator {
  int64_t results;

public:
  Calculator(std::vector<int64_t> input_data);
  int64_t send_res() const;
};