/**
 * @file Interface.cpp
 * @brief Определение класса UserInterface для работы с пользовательским интерфейсом приложения.
 *
 */
 
#include "Interface.h"

namespace po = boost::program_options;

int UserInterface::interface(int argc, const char **argv) {
  po::options_description desc("Доступные опции");
  desc.add_options()("help,h", "Выдать справку")(
      "database,d",
      po::value<string>(&params.d)->default_value("/etc/vcalc.conf"),
      "Установить путь к базе данных")(
      "log,l",
      po::value<string>(&params.l)->default_value("/var/log/vcalc.log"),
      "Установить путь к журналу")(
      "port,p", po::value<int>(&params.p)->default_value(33333),
      "Установить порт");

  po::variables_map vm;
  try {
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
      cout << desc << endl;
      cout << "Пример: " << argv[0]
           << " -d[atabase] data.txt -l[og] log.txt -p[ort] 7777" << endl;
      return 0;
    }
    string dataFileName = vm["database"].as<string>();
    string logFileName = vm["log"].as<string>();
    int port = vm["port"].as<int>();

    if (port < 1 || port > 65535) {
      throw po::validation_error(po::validation_error::invalid_option_value,
                                 "port");
    }
    if (params.p_default() && params.d_default() && params.l_default()) {
      std::cout << desc << std::endl;
    }

    Logger log(logFileName);
    BaseConnector bc;
    bc.baseConnection(dataFileName);

    log.writelog((logFileName != "/var/log/vcalc.log")
                     ? "Путь к журналу: " + logFileName
                     : "Путь к журналу по умолчанию: " + logFileName);

    log.writelog((dataFileName != "/etc/vcalc.conf")
                     ? "Путь к базе данных: " + dataFileName
                     : "Путь к базе данных по умолчанию: " + dataFileName);

    log.writelog((port != 33333) ? "Порт: " + to_string(port)
                                 : "Порт по умолчанию: " + to_string(port));

    Server connect;
    connect.connection(port, bc.get_data(), &log);

  } catch (const po::error &e) {
    cerr << "Ошибка Boost: " << e.what() << endl;
    return 1;
  } catch (const exception &e) {
    cerr << "Ошибка: " << e.what() << endl;
    return 1;
  } catch (...) {
    cerr << "Неизвестная ошибка" << endl;
    return 1;
  }

  return 0;
}
