#include "DataBaseHandler.h"

int BaseConnector::baseConnection(string baseFile) {
    ifstream readFile(baseFile);
    if (!readFile.is_open()) {
        throw criticalErr("База данных не найдена");
    }

    string line;
    while (getline(readFile, line)) {
        auto separator = line.find(':');
        if (separator != string::npos) {
            string tempLogin = line.substr(0, separator);
            string tempPass = line.substr(separator + 1);

            if (tempLogin.empty() || tempPass.empty()) {
                throw criticalErr("База данных не корректная");
            }

            dataBase[tempLogin] = tempPass;
        }
    }

    if (dataBase.empty()) {
        throw criticalErr("База данных пустая");
    }
    
    return 0;
}
