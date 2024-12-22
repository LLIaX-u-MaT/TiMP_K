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

class Server {
public:
  std::string sha224(const std::string &input_str);
  int connection(int port, std::map<std::string, std::string> dataFileName,
                 Logger *log);
};
