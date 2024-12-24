/**
 * @file Calculator.cpp
 * @brief Определение класса Calculator для выполнения расчетов.
 */
 
#include "Calculator.h"

Calculator::Calculator(std::vector<int64_t> inputVector) {
  try {
    int64_t result = 1;
    for (auto item : inputVector) {
      if (item == 0) {
        finalResult = 0;
        return;
      }

      if (result > 0 && item > 0 &&
          result > std::numeric_limits<int64_t>::max() / item) {
        throw boost::numeric::positive_overflow();
      }
      if (result > 0 && item < 0 &&
          item < std::numeric_limits<int64_t>::min() / result) {
        throw boost::numeric::negative_overflow();
      }
      if (result < 0 && item > 0 &&
          result < std::numeric_limits<int64_t>::min() / item) {
        throw boost::numeric::negative_overflow();
      }
      if (result < 0 && item < 0 &&
          result < std::numeric_limits<int64_t>::max() / item) {
            throw boost::numeric::positive_overflow();
          }

      result *= item;
    }
    finalResult = result;
  } catch (const boost::numeric::positive_overflow &) {
    finalResult = std::numeric_limits<int64_t>::max();
  } catch (const boost::numeric::negative_overflow &) {
    finalResult = std::numeric_limits<int64_t>::min();
  }
}

int64_t Calculator::sendResult() const { return finalResult; }
