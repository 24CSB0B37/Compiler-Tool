CXX=g++
CXXFLAGS=-std=c++11 -Iinclude

SRC=src/*.cpp
OUT=compiler_tool

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run:
	./$(OUT)

clean:
	rm -f $(OUT)