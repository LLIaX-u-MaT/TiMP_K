#include "Server.h"

string Server::sha224(const string &input_str) {
  using namespace CryptoPP;
  SHA224 hash;
  string new_hash;
  StringSource(input_str, true,
               new HashFilter(hash, new HexEncoder(new StringSink(new_hash))));
  return new_hash;
}

int Server::connection(int port,
                       map<string, string> dataFileName,
                       Logger *log) {
  try {
    int queue_len = 100;
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_aton("127.0.0.1", &addr.sin_addr);

    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
      throw criticalErr("Ошибка создания сокета");
    }
    log->writelog("Сокет прослушивания создан");

    if (bind(s, (const sockaddr *)&addr, sizeof(sockaddr_in)) < 0) {
      throw criticalErr("Ошибка связывания сокетов");
    }

    if (listen(s, queue_len) < 0) {
      throw criticalErr("Ошибка прослушивания сокета");
    }

    while (true) {
      sockaddr_in client_addr;
      socklen_t len = sizeof(sockaddr_in);
      int handler_socket = accept(s, (sockaddr *)&client_addr, &len);
      if (handler_socket < 0) {
        log->writelog("Ошибка сокета клиента");
        continue;
      }

      char buff[1024] = {};
      ssize_t rc = recv(handler_socket, buff, sizeof(buff) - 1, 0);
      if (rc <= 0) {
        close(handler_socket);
        continue;
      }

      if (rc < 72) {
        send(handler_socket, "ERR", 3, 0);
        close(handler_socket);
        continue;
      }

      string hash_received(buff + rc - 56, 56);
      string salt(buff + rc - 72, 16);
      string login(buff, rc - 72);

      log->writelog("Логин: " + login);
      log->writelog("Соль: " + salt);
      log->writelog("Хэш: " + hash_received);
             
      auto it = dataFileName.find(login);
      if (it == dataFileName.end()) {
        send(handler_socket, "ERR", 3, 0);
        log->writelog("Клиент не прошёл аутентификацию");
        close(handler_socket);
        continue;
      }

      string expected_hash = sha224(salt + it->second);
      if (expected_hash != hash_received) {
        send(handler_socket, "ERR", 3, 0);
        log->writelog("Клиент не прошёл аутентификацию");
        close(handler_socket);
        continue;
      } else {
        send(handler_socket, "OK", 2, 0);
        log->writelog("Аутентификация клиента произошла успешно: " + login);
      }

      uint32_t vector_count;
      if (recv(handler_socket, &vector_count, sizeof(vector_count), 0) <=
          0) {
        log->writelog("Ошибка получения количества векторов");
        close(handler_socket);
        break;
      }

      for (uint32_t i = 0; i < vector_count; i++) {
        uint32_t vector_size;
        if (recv(handler_socket, &vector_size, sizeof(vector_size), 0) <= 0) {
          log->writelog("Ошибка получения размера вектора");
          close(handler_socket);
          break;
        }

        vector<int64_t> vector_values(vector_size);
        ssize_t received_bytes = recv(handler_socket, vector_values.data(),
                                      vector_size * sizeof(int64_t), 0);
        if (received_bytes <= 0 ||
            received_bytes !=
                static_cast<ssize_t>(vector_size * sizeof(int64_t))) {
          log->writelog("Ошибка получения данных вектора");
          close(handler_socket);
          break;
        }

        Calculator calculate(vector_values);
        int64_t multiply = calculate.sendResult();
        send(handler_socket, &multiply, sizeof(multiply), 0);
      }

      close(handler_socket);
    }
  } catch (const criticalErr &e) {
    log->writelog(e.what());
    return -1;
  }
  return 0;
}