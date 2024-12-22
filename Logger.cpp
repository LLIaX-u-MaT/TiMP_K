#include "Logger.h"

#include <iostream>

using namespace std;

int Logger::setLogPath(string pathFile) {
    ofstream filelog;
    filelog.open(pathFile, ios_base::out | ios_base::app);
    if (filelog.is_open()) {
        pathLogFile = pathFile;
        return 0;
    } else if (pathFile == "/var/log/vcalc.log") {
        pathLogFile = "/tmp/vcalc.log";
        filelog.open(pathLogFile, ios_base::out | ios_base::app);
        if (filelog.is_open()) {
            return 0;
        }
    }
    throw criticalErr("Не удалось создать журнал: " + pathLogFile);
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
        cerr << "Ошибка: не удалось создать журнал в " << pathLogFile
                  << ". Создание журнала на /tmp/vcalc.log" << endl;
        pathLogFile = "/tmp/vcalc.log";
        filelog.open(pathLogFile, ios_base::out | ios_base::app);

        if (!filelog.is_open()) {
            throw criticalErr("Не удалось создать журнал: " + pathLogFile);
        }
    }

    string time = getLocalDateTime("now");
    filelog << time << ' ' << s << endl;

    cout << time << ' ' << s << endl;

    return 0;
}
