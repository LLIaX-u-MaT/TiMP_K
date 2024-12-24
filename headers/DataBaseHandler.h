/**
 * @file DataBaseHandler.h
 * @brief Определение класса BaseConnector для работы с конфигурационными
 * файлами.
 *
 * Данный класс предназначен для подключения к базе данных,
 * загружая данные из конфигурационного файла.
 * @author Мочалов Ю.А.
 * @version 1.0
 * @date 24.12.2024
 * @copyright ИБСТ ПГУ
 */
#pragma once

#include "Errors.h"
#include "Logger.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

/**
 * @class BaseConnector
 * @brief Класс для подключения к базе данных через конфигурационный файл.
 *
 * Этот класс отвечает за загрузку данных из указанного конфигурационного файла
 * и предоставляет доступ к загруженным данным.
 */
class BaseConnector {
private:
  map<string, string>
      dataBase; ///< Хранит данные, загруженные из конфигурационного файла.

public:
  /**
   * @brief Подключение к базе данных.
   *
   * Загружает данные из указанного конфигурационного файла.
   * По умолчанию используется файл "/etc/vcalc.conf".
   *
   * @param baseFile Путь к конфигурационному файлу (по умолчанию
   * "/etc/vcalc.conf").
   * @return Возвращает 0 в случае успешного подключения,
   *         или код ошибки в случае неудачи.
   */
  int baseConnection(string baseFile = "/etc/vcalc.conf");

  /**
   * @brief Получить загруженные данные.
   *
   * Возвращает карту, содержащую данные, загруженные из конфигурационного
   * файла.
   *
   * @return map<string, string> Содержит ключи и значения загруженных данных.
   */
  map<string, string> get_data() { return dataBase; }
};
