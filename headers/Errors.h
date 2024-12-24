/**
 * @file Errors.h
 * @brief Определение классов ошибок для обработки исключений в приложении.
 *
 * Данный файл содержит определения классов ошибок, которые используются для
 * обработки различных типов исключительных ситуаций в приложении.
 * @author Мочалов Ю.А.
 * @version 1.0
 * @date 24.12.2024
 * @copyright ИБСТ ПГУ
 */
#pragma once

#include <stdexcept>
#include <string>
#include <system_error>

using namespace std;

/**
 * @class dataBaseErr
 * @brief Класс для обработки ошибок базы данных.
 *
 * Этот класс наследуется от std::invalid_argument и используется для
 * представления ошибок, связанных с неправильными аргументами при
 * работе с базой данных.
 */
class dataBaseErr : public std::invalid_argument {
public:
    /**
     * @brief Конструктор для создания объекта dataBaseErr.
     *
     * @param s Сообщение об ошибке.
     */
    dataBaseErr(const string &s) : std::invalid_argument(s) {}
};

/**
 * @class criticalDataBaseErr
 * @brief Класс для обработки критических ошибок базы данных.
 *
 * Этот класс наследуется от dataBaseErr и используется для
 * представления критических ошибок, которые могут привести к
 * серьезным сбоям в работе приложения.
 */
class criticalDataBaseErr : public dataBaseErr {
public:
    /**
     * @brief Конструктор для создания объекта criticalDataBaseErr.
     *
     * @param s Сообщение об ошибке.
     */
    criticalDataBaseErr(const string &s) : dataBaseErr(s) {}
};

/**
 * @class logErr
 * @brief Класс для обработки ошибок логирования.
 *
 * Этот класс наследуется от std::invalid_argument и используется для
 * представления ошибок, связанных с процессом логирования в приложении.
 */
class logErr : public std::invalid_argument {
public:
    /**
     * @brief Конструктор для создания объекта logErr.
     *
     * @param message Сообщение об ошибке.
     */
    explicit logErr(const std::string &message) : std::invalid_argument(message) {}
};

/**
 * @class criticalErr
 * @brief Класс для обработки критических ошибок.
 *
 * Этот класс наследуется от std::runtime_error и используется для
 * представления критических ошибок, которые могут повлиять на
 * выполнение приложения.
 */
class criticalErr : public std::runtime_error {
public:
    /**
     * @brief Конструктор для создания объекта criticalErr.
     *
     * @param message Сообщение об ошибке.
     */
    explicit criticalErr(const std::string &message)
        : std::runtime_error(message) {}
};
