# Makefile for C++ Command Shell

CXX = g++
CXXFLAGS = -Wall -std=c++11

SRC = src/main.cpp src/commands.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = cppshell

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o

run: all
	./$(TARGET)
