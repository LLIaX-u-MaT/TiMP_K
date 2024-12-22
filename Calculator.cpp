#include "Calculator.h"

Calculator::Calculator(vector<int64_t> input_data) {
  try {
    int64_t result = 1;
    for (auto elem : input_data) {
      if (result > numeric_limits<int64_t>::max() / elem) {
        throw boost::numeric::positive_overflow();
      }
      result *= elem;
    }
    if (result > numeric_limits<int64_t>::max()) {
      finalResult = numeric_limits<int64_t>::max();
    } else {
      finalResult = static_cast<int64_t>(result);
    }
  } catch (boost::numeric::positive_overflow &) {
    finalResult = numeric_limits<int64_t>::max();
  }
}

int64_t Calculator::sendResult() const { return finalResult; }