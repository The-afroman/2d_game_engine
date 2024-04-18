SHELL=/bin/bash
.SHELLFLAGS=-O extglob -c
CC := g++
cpp_std := -std=c++20
compiler_flags := -Wall
linker_flags := -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -llua5.3
include_path := -I"./libs/"
src_files := src/**/*.cpp src/*.cpp
header_files := src/**/*.h
obj_name := gameengine

build:
	$(CC) $(compiler_flags) $(cpp_std) $(include_path) $(src_files) $(linker_flags) -o $(obj_name)

run:
	./$(obj_name)

format:
	clang-format -i $(src_files) $(header_files)

all: format build run

clean:
	rm $(obj_name)