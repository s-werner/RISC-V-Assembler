CXX = g++
CXXFLAGS = -I include -std=c++17
GTEST_DIR = $(shell brew --prefix googletest)
TEST_CXXFLAGS = -I include -I $(GTEST_DIR)/include -std=c++17
TEST_LDFLAGS = -L $(GTEST_DIR)/lib -lgtest -lgtest_main -pthread
TARGET = assembler
TEST_TARGET = test_runner
SOURCES = src/main.cpp src/lexer.cpp src/encoder.cpp
TEST_SOURCES = tests/test_encoder.cpp src/lexer.cpp src/encoder.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

test: $(TEST_SOURCES)
	$(CXX) $(TEST_CXXFLAGS) $(TEST_SOURCES) $(TEST_LDFLAGS) -o $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

.PHONY: clean test