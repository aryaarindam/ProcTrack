CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lncurses

SRCS = src/main.cpp src/cpu.cpp src/memory.cpp src/process.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = proctrack

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET) src/*.o
