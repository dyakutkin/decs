.PHONY: build win-build run check-leaks

# check-leaks:
# 	make build && valgrind --leak-check=full ./build/pr

win-build:
	x86_64-w64-mingw32-gcc -g3 -O0  -o ./build/pr.exe $(shell find ./src -name '*.c') ./src/lib/win/libraylib.a -lm -lwinmm -lgdi32 -Wall -Wextra -Wswitch -Wswitch-enum -Wenum-conversion
build-debug:
	gcc -g3 -O0 -fno-omit-frame-pointer -fno-inline -fsanitize=address,undefined -o ./build/debug $(shell find ./src -name '*.c') ./src/lib/linux/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra -Wswitch -Wswitch-enum -Wenum-conversion
build-release:
	gcc -O3 -DNDEBUG -o ./build/release $(shell find ./src -name '*.c') ./src/lib/linux/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra -Wswitch -Wswitch-enum -Wenum-conversion
debug:
	make build-debug && gdb ./build/debug
run:
	make build-release && ./build/release
