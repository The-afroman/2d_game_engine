CC := g++
cpp_std := -std=c++20
compiler_flags := -Wall
linker_flags := -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -llua5.3
include_path := -I"./libs/"
src_files := $(wildcard src/*.cpp src/Game/*.cpp src/Logger/*.cpp)
obj_name := gameengine

build:
	$(CC) $(compiler_flags) $(cpp_std) $(include_path) $(src_files) $(linker_flags) -o $(obj_name)

run:
	./$(obj_name)

all: build run

clean:
	rm $(obj_name)