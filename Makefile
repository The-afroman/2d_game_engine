SHELL=/bin/bash
.SHELLFLAGS=-O extglob -c
UNAME_S := $(shell uname -s)
CC := g++
CCC := clang++
cpp_std := -std=c++20
compiler_flags := -Wall
osx_libs := -L"/opt/homebrew/lib"
osx_include := -I"/opt/homebrew/include"
linker_flags_linux := -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -llua5.4
include_path := -I"./libs/"
src_files := src/**/*.cpp src/*.cpp
header_files := src/**/*.h
obj_name := gameengine
obj_name_clang := gameengine-clang


ifeq ($(UNAME_S), Darwin)
	linker_flags := $(osx_libs) $(linker_flags_linux)
	include_path += $(osx_include)
else
	linker_flags := $(linux_flags_linux)
endif

build:
	$(CC) $(compiler_flags) $(cpp_std) $(include_path) $(src_files) $(linker_flags) -o $(obj_name)

build-clang:
	$(CCC) $(compiler_flags) $(cpp_std) $(include_path) $(src_files) $(linker_flags) -o $(obj_name_clang)

run:
	./$(obj_name)

format:
	clang-format -style='{BasedOnStyle: Google, ColumnLimit: 120}' -i $(src_files) $(header_files)

all: format build run

clean:
	rm $(obj_name)
