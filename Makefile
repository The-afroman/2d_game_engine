CC := g++
cppstd := c++23
lflags := -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -llua5.3
libs := "./libs/"
files := $(wildcard src/*.cpp)
outfile := gameengine

build:
	$(CC) -Wall -std=$(cppstd) -I$(libs) $(files) $(lflags) -o $(outfile)

run:
	./gameengine

all: build run

clean:
	rm gameengine