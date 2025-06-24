CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
LDFLAGS = -lncurses

SRC = src/main.cpp src/cpu.cpp src/memory.cpp src/process.cpp
OBJ = $(SRC:.cpp=.o)
BIN = proctrack

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(BIN)
