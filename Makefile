CXX = g++
CXXFLAGS = -Wall -std=c++17 -I./include $(shell python3 -m pybind11 --includes)
LDFLAGS = -lpython3.12

SRC = $(wildcard src/*.cpp)

OBJ = $(SRC:.cpp=.o)

all: main

main: $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o main
