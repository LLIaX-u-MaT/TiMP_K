.PHONY: all debug release clean test

Compiler = g++
RELEASE_FLAGS = -O2 -Wall -DNDEBUG -Iheaders
DEBUG_FLAGS   = -g -O0 -Wall -Iheaders
RELEASE_EXEC  = kurs
TEST_EXEC     = UnitTest
SOURCES       = Calculator.cpp DataBaseHandler.cpp Interface.cpp Logger.cpp Server.cpp
LIBRARY       = -lboost_program_options -lcryptopp

OBJECTS = $(SOURCES:.cpp=.o)

TEST_SOURCES = UnitTest.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

all: release

release: $(RELEASE_EXEC)

$(RELEASE_EXEC): $(OBJECTS) main.o
	$(Compiler) $(RELEASE_FLAGS) $(OBJECTS) main.o -o $(RELEASE_EXEC) $(LIBRARY)

test: $(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJECTS) $(OBJECTS)
	$(Compiler) $(RELEASE_FLAGS) $(TEST_OBJECTS) $(OBJECTS) -o $(TEST_EXEC) $(LIBRARY) -lUnitTest++

%.o: %.cpp
	$(Compiler) $(RELEASE_FLAGS) -c $< -o $@

clean:
	rm -f $(RELEASE_EXEC) $(TEST_EXEC) $(OBJECTS) $(TEST_OBJECTS) main.o
