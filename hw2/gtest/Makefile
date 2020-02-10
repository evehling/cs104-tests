CC = g++
CPPFLAGS = -g -Wall -std=c++11
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

test: FORCE $(BIN_DIR) $(BIN_DIR)/gtest
	 ./$(BIN_DIR)/gtest

$(BIN_DIR)/gtest: $(BIN_DIR)/gtest.o $(BIN_DIR)/gitint.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/gtest.o: gtest.cpp gitint.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/gitint.o: gitint.cpp gitint.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

FORCE: ;

.phony: clean test

clean:
	-@rm -rf $(BIN_DIR)

ValidTest: $(BIN_DIR) $(BIN_DIR)/gtest
	 ./$(BIN_DIR)/gests