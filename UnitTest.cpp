#include "Calculator.h"
#include "DataBaseHandler.h"
#include "Errors.h"
#include "Interface.h"
#include "Logger.h"
#include "Server.h"

#include <UnitTest++/UnitTest++.h>
#include <filesystem>

SUITE(SetDataBaseTests) {
  TEST(ValidDatabaseFile) {
    BaseConnector connector;
    CHECK_EQUAL(0, connector.baseConnection("test/data.txt"));
  }
  TEST(InvalidDataBaseFile) {
    BaseConnector connector;
    CHECK_THROW(connector.baseConnection("test/Null.txt"), criticalErr);
  }
  TEST(EmptyDataBaseFile) {
    BaseConnector connector;
    CHECK_THROW(connector.baseConnection("test/emptyBase.txt"), criticalErr);
  }
  TEST(EmptyLoginDataBase) {
    BaseConnector connector;
    CHECK_THROW(connector.baseConnection("test/dataNoLogin.txt"), criticalErr);
  }
  TEST(EmptyPassDataBase) {
    BaseConnector connector;
    CHECK_THROW(connector.baseConnection("test/dataNoPass.txt"), criticalErr);
  }
  TEST(DataBaseReconnection) {
    BaseConnector connector;
    CHECK_EQUAL(0, connector.baseConnection("test/data.txt"));
    CHECK_EQUAL(0, connector.baseConnection("test/data.txt"));
  }
}

SUITE(SetLoggerTests) {
  TEST(SetLogPath_Success) {
    Logger logger;
    CHECK_EQUAL(logger.setLogPath("test/log.txt"), 0);
  }
  TEST(SetLog_InvalidPathError) {
    Logger logger;
    CHECK_THROW(logger.setLogPath("/invalid/path/to/log"), criticalErr);
  }
  TEST(SetLog_EmptyPathError) {
    Logger logger;
    CHECK_THROW(logger.setLogPath(""), criticalErr);
  }
  TEST(SetLogPathInProtectedFolder) {
    Logger logger;
    CHECK_THROW(logger.setLogPath("/var/log/test.log"), criticalErr);
  }
  TEST(WriteLog_Success) {
    Logger logger("test/log.txt");
    CHECK_EQUAL(0, logger.writelog("Это тест логирования журнала"));
  }
  TEST(MultipleWriteLog_Success) {
    Logger logger("test/log.txt");
    CHECK_EQUAL(0, logger.writelog("Это тест логирования журнала 1"));
    CHECK_EQUAL(0, logger.writelog("Это тест логирования журнала 2"));
  }
}

SUITE(CommunicatorTests) {
  TEST(Server_sha224_Test) {
    Server server;
    std::string input = "test";
    std::string expected_hash =
        "90A3ED9E32B2AAF4C61C410EB925426119E1A9DC53D4286ADE99A809";
    CHECK_EQUAL(server.sha224(input), expected_hash);
  }
  TEST(EmptyStringHash) {
    Server server;
    std::string expected_empty_hash =
        "D14A028C2A3A2BC9476102BB288234C415A2B01F828EA62AC5B3E42F";
    CHECK_EQUAL(expected_empty_hash, server.sha224(""));
  }
  TEST(HashWithSalt) {
    Server server;
    std::string salt = "random_salt";
    std::string password = "password";
    std::string combined_input = salt + password;
    std::string expected_hash =
        "F881117367A08C1BF98EE45F7F728650D91C479A3E0D8D06E9D90B6A";
    CHECK_EQUAL(server.sha224(combined_input), expected_hash);
  }
  TEST(HashWithSpecialCharacters) {
    Server server;
    std::string input = "test@123!";
    std::string expected_hash =
        "9AF50091DEDA5C56499A0FFAEED67B1A1EE19206BA78F78924443208";
    CHECK_EQUAL(server.sha224(input), expected_hash);
  }
  TEST(HashWithWhiteSpace) {
    Server server;
    std::string input = "test 123";
    std::string expected_hash =
        "36BACDB6F72F16A6D00674B09F49FA70B8894DC614C5028E3E412517";
    CHECK_EQUAL(server.sha224(input), expected_hash);
  }
}
SUITE(CalculatorTests) {
  TEST(MultiplyPositiveNumbers) {
    std::vector<int64_t> input = {9, 18, 27, 36};
    Calculator calculate(input);
    CHECK_EQUAL(157464, calculate.sendResult());
  }
  TEST(MultiplyNegativeNumbers) {
    std::vector<int64_t> input = {-9, 18, 27, 36};
    Calculator calculate(input);
    CHECK_EQUAL(-157464, calculate.sendResult());
  }
  TEST(PositiveOverflow) {
    std::vector<int64_t> input = {numeric_limits<int64_t>::max(), 2};
    Calculator calculate(input);
    CHECK_EQUAL(9223372036854775807, calculate.sendResult());
  }
  TEST(NegativeOverflow) {
    std::vector<int64_t> input = {numeric_limits<int64_t>::min(), 2};
    Calculator calculate(input);
    CHECK_EQUAL(numeric_limits<int64_t>::min(), calculate.sendResult());
  }
  TEST(SingleElement) {
    std::vector<int64_t> input = {100};
    Calculator calculate(input);
    CHECK_EQUAL(100, calculate.sendResult());
  }
  TEST(EmptyVector) {
    std::vector<int64_t> input = {};
    Calculator calculate(input);
    CHECK_EQUAL(1, calculate.sendResult());
  }
  TEST(ZeroElement) {
    std::vector<int64_t> input = {0, 50, 100};
    Calculator calculate(input);
    CHECK_EQUAL(0, calculate.sendResult());
  }
}

int main(int argc, const char *argv[]) { return UnitTest::RunAllTests(); }
