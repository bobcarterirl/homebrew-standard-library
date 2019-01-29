CC = g++
CFLAGS = -g -O2 -Wall -Iinclude -std=c++17

SOURCES = $(shell find src -type f -name *.c -o -name *.cpp)
OBJECTS = $(patsubst src/%.cpp,obj/%.o,$(SOURCES))
TARGET = stl-tests

all: dir bin/$(TARGET)

bin/$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $+

obj/%.o: src/%.cpp
	$(CC) -c $(CFLAGS) -o $@ $+

dir:
	mkdir -p bin
	mkdir -p obj
	mkdir -p src
	mkdir -p include
	cd src && find . -type d -exec mkdir -p ../obj/{} \;

clean:
	rm -rf bin/*
	rm -rf obj/*

new: clean
	$(MAKE) all

.PHONY: clean dir all new
