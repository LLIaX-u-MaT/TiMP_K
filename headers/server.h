#pragma once

#include "calculator.h"
#include "errors.h"
#include "logger.h"

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

class Server {
private:
  std::string address; // IP-адрес сервера
  int port;            // Порт сервера
  std::map<std::string, std::string> dataFileName; // База данных пользователей
  std::string sha224(const std::string &input_str); // Метод для хеширования

public:
  int connection(int port, std::map<std::string, std::string> dataFileName, Logger *l1); // Метод для обработки соединений
};
