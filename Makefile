TARGET = bin/pathfinder

SRC_DIR = ./src

SRC = $(shell find $(SRC_DIR) -name *.cpp)

INC_DIR = ./include/

CPPFLAGS = -std=c++11 -I $(INC_DIR)
CC=g++

pathfinder:
	$(CC) $(CPPFLAGS) -o $(TARGET) $(SRC)
