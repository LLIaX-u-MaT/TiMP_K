/**
 * @file Calculator.h
 * @brief Определение класса Calculator для выполнения расчетов.
 *
 * Данный класс предназначен для выполнения арифметических операций
 * над вектором целых чисел (int64_t) и хранения конечного результата.
 * @author Мочалов Ю.А.
 * @version 1.0
 * @date 24.12.2024
 * @copyright ИБСТ ПГУ
 */

#pragma once

#include <boost/numeric/conversion/cast.hpp>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <vector>

using namespace std;

/**
 * @class Calculator
 * @brief Класс для выполнения расчетов с вектором целых чисел.
 *
 * Этот класс принимает вектор целых чисел в качестве входных данных,
 * выполняет необходимые вычисления и предоставляет метод для
 * получения конечного результата.
 */
class Calculator {
    int64_t finalResult; ///< Хранит конечный результат вычислений.

public:
    /**
     * @brief Конструктор класса Calculator.
     * 
     * Принимает вектор целых чисел и выполняет необходимые вычисления,
     * чтобы установить значение finalResult.
     *
     * @param inputVector Вектор целых чисел для обработки.
     * @throws std::invalid_argument Если вектор пуст или содержит недопустимые значения.
     */
    Calculator(vector<int64_t> inputVector);

    /**
     * @brief Получить конечный результат вычислений.
     *
     * @return Возвращает значение finalResult.
     */
    int64_t sendResult() const;
};
