CXX = g++
CXXFLAGS = -I include
TARGET = assembler
SOURCES = src/main.cpp src/lexer.cpp src/encoder.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean