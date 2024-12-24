/**
 * @file Interface.h
 * @brief Определение класса UserInterface для работы с пользовательским интерфейсом приложения.
 *
 * Этот файл содержит определение класса UserInterface, который отвечает за
 * взаимодействие с пользователем и обработку командной строки.
 * @author Мочалов Ю.А.
 * @version 1.0
 * @date 24.12.2024
 * @copyright ИБСТ ПГУ
 */
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

/**
 * @class UserInterface
 * @brief Класс для обработки пользовательского интерфейса.
 *
 * Класс UserInterface отвечает за взаимодействие с пользователем,
 * включая обработку аргументов командной строки и настройку параметров
 * приложения.
 */
class UserInterface {
public:
    /**
     * @brief Основной метод интерфейса.
     *
     * Этот метод принимает аргументы командной строки и обрабатывает их,
     * настраивая параметры приложения.
     *
     * @param argc Количество аргументов командной строки.
     * @param argv Массив аргументов командной строки.
     * @return Возвращает код завершения (0 - успех, другой - ошибка).
     */
    int interface(int argc, const char **argv);

private:
    /**
     * @struct Params
     * @brief Структура для хранения параметров приложения.
     *
     * Эта структура хранит параметры, переданные через командную строку,
     * и предоставляет методы для проверки значений по умолчанию.
     */
    struct Params {
        string d; ///< Путь к файлу конфигурации.
        string l; ///< Путь к файлу логирования.
        int p;    ///< Порт для подключения к серверу.

        /**
         * @brief Проверка значения порта по умолчанию.
         *
         * @return true, если порт равен 33333; иначе false.
         */
        bool p_default() const { return (p == 33333); }

        /**
         * @brief Проверка значения пути к файлу конфигурации по умолчанию.
         *
         * @return true, если путь равен "/etc/vcalc.conf"; иначе false.
         */
        bool d_default() const { return (d == "/etc/vcalc.conf"); }

        /**
         * @brief Проверка значения пути к файлу логирования по умолчанию.
         *
         * @return true, если путь равен "/var/log/vcalc.log"; иначе false.
         */
        bool l_default() const { return (l == "/var/log/vcalc.log"); }
    } params; ///< Экземпляр структуры Params для хранения параметров.
};
