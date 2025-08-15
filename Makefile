.PHONY: build

build:
	gcc -g3 -O0 -o ./build/pr $(shell find ./src -name '*.c') ./src/lib/linux/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11

win-build:
	x86_64-w64-mingw32-g++ -g -o ./build/pr.exe $(shell find ./src -name '*.c') ./src/lib/win/libraylib.a -lm -lwinmm -lgdi32

run:
	make build && ./build/pr

check-leaks:
	make build && valgrind --leak-check=full ./build/pr
