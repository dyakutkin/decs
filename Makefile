FILES = $(shell find . -name "*.c")

build:
	gcc $(FILES) -lraylib -lgdi32 -lwinmm -o ./build/pr.exe

# build-debug:
# 	gcc $(FILES) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra -g  -o ./build/pr.debug

# run:
# 	./build/pr

.PHONY: build
