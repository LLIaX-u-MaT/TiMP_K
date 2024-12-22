#include "Calculator.h"
#include "DataBaseHandler.h"
#include "Errors.h"
#include "Interface.h"
#include "Logger.h"
#include "Server.h"

int main(int argc, const char **argv) {
  UserInterface interface;
  return interface.interface(argc, argv);
  return 0;
}
