.PHONY: build win-build run check-leaks

# build-linux:
# 	gcc -g3 -O0 -o ./build/pr $(shell find ./src -name '*.c') ./src/lib/linux/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11 -Wall
# check-leaks:
# 	make build && valgrind --leak-check=full ./build/pr

build:
	x86_64-w64-mingw32-gcc -g3 -O0  -o ./build/pr.exe $(shell find ./src -name '*.c') ./src/lib/win/libraylib.a -lm -lwinmm -lgdi32 -Wall -Wextra -Wswitch -Wswitch-enum -Wenum-conversion

run:
	make build && ./build/pr.exe
