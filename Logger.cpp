/**
 * @file Logger.cpp
 * @brief Определение класса Logger для ведения логов приложения.
 */

#include "Logger.h"

using namespace std;

int Logger::setLogPath(string pathFile) {
    ofstream filelog;
    filelog.open(pathFile, ios_base::out | ios_base::app);

    if (filelog.is_open()) {
        pathLogFile = pathFile;
        writelog("Журнал установлен: " + pathLogFile);
        return 0;
    } else if (pathFile == "/var/log/vcalc.log") {
        pathLogFile = "/tmp/vcalc.log";
        filelog.open(pathLogFile, ios_base::out | ios_base::app);
        if (filelog.is_open()) {
            writelog("Журнал установлен: " + pathLogFile);
            return 0;
        }
    }
    throw logErr("Не удалось создать журнал: " + pathLogFile);
}

string Logger::getLocalDateTime(string s) {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);

    if (s == "now")
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    else if (s == "date")
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

    return string(buf);
}

int Logger::writelog(string s) {
    ofstream filelog(pathLogFile, ios_base::out | ios_base::app);

    if (!filelog.is_open()) {
        cerr << "Внимание: Не удалось создать журнал в " << pathLogFile
             << ". Создание журнала в /tmp/vcalc.log" << endl;

        pathLogFile = "/tmp/vcalc.log";
        filelog.open(pathLogFile, ios_base::out | ios_base::app);

        if (!filelog.is_open()) {
            throw logErr("Не удалось создать журнал: " + pathLogFile);
        }
    }

    string time = getLocalDateTime("now");
    filelog << time << ' ' << s << endl;

    cout << time << ' ' << s << endl;

    return 0;
}
