CXX = g++
CXXFLAGS = -std=c++11

SRC = src/main.cpp src/compiler.cpp src/parser.cpp src/error.cpp src/explainer.cpp
OUT = compiler_tool

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run:
	./$(OUT) sample/test.cpp

clean:
	rm -f $(OUT)