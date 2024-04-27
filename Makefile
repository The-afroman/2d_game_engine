SHELL=/bin/bash
.SHELLFLAGS=-O extglob -c
CC := g++
CCC := clang++
cpp_std := -std=c++20
compiler_flags := -Wall
linker_flags := -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -llua5.3
include_path := -I"./libs/"
src_files := src/**/*.cpp src/*.cpp
header_files := src/**/*.h
obj_name := gameengine
obj_name_clang := gameengine-clang

build:
	$(CC) $(compiler_flags) $(cpp_std) $(include_path) $(src_files) $(linker_flags) -o $(obj_name)

build-clang:
	$(CCC) $(compiler_flags) $(cpp_std) $(include_path) $(src_files) $(linker_flags) -o $(obj_name_clang)

run:
	./$(obj_name)

format:
	clang-format -style='{BasedOnStyle: Google}' -i $(src_files) $(header_files)

all: format build run

clean:
	rm $(obj_name)
