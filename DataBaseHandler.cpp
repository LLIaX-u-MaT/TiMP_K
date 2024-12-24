/**
 * @file DataBaseHandler.cpp
 * @brief Определение класса BaseConnector для работы с конфигурационными
 * файлами.
 */
 
#include "DataBaseHandler.h"

int BaseConnector::baseConnection(string baseFile) {
  ifstream readFile(baseFile);
  if (!readFile.is_open()) {
    throw criticalDataBaseErr("Ошибка: База данных не найдена: " + baseFile);
  }

  string line;
  while (getline(readFile, line)) {
    auto separator = line.find(':');
    if (separator != string::npos) {
      string tempLogin = line.substr(0, separator);
      string tempPass = line.substr(separator + 1);

      if (tempLogin.empty() || tempPass.empty()) {
        throw dataBaseErr(
            "Внимание: Обнаружена некорректная пара логин:пароль: " + line);
      }
      dataBase[tempLogin] = tempPass;
    }
  }

  if (dataBase.empty()) {
    throw criticalDataBaseErr("Ошибка: База данных пустая");
  }

  return 0;
}
