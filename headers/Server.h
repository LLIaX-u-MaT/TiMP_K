/**
 * @file Server.h
 * @brief Определение класса Server для работы с серверными функциями.
 *
 * Этот файл содержит определение класса Server, который предоставляет
 * функциональность для обработки соединений и вычисления SHA224 хешей.
 * @author Мочалов Ю.А.
 * @version 1.0
 * @date 24.12.2024
 * @copyright ИБСТ ПГУ
 */
#pragma once

#include "Calculator.h"
#include "Errors.h"
#include "Logger.h"

#include <arpa/inet.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cstring>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

/**
 * @class Server
 * @brief Класс для работы с серверными функциями.
 *
 * Класс Server предоставляет методы для вычисления SHA224 хешей и
 * обработки сетевых соединений.
 */
class Server {
public:
    /**
     * @brief Вычисление SHA224 хеша для заданной строки.
     *
     * Этот метод принимает строку, вычисляет ее SHA224 хеш и возвращает
     * его в виде шестнадцатеричной строки.
     *
     * @param input_str Входная строка для вычисления хеша.
     * @return Шестнадцатеричная строка, представляющая SHA224 хеш.
     */
    std::string sha224(const std::string &input_str);

    /**
     * @brief Установка соединения на заданном порту.
     *
     * Этот метод устанавливает соединение на указанном порту и обрабатывает
     * данные из файла, используя переданный логгер для ведения логов.
     *
     * @param port Порт для установки соединения.
     * @param dataFileName Карта, содержащая данные файлов с именами.
     * @param log Указатель на объект Logger для ведения логов.
     * @return Возвращает 0 при успешном соединении, иначе -1.
     */
    int connection(int port, std::map<std::string, std::string> dataFileName,
                   Logger *log);
};
