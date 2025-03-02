FILES = $(shell find . -name "*.c")

buildw:
	gcc $(FILES) -lraylib -lgdi32 -lwinmm -o ./build/pr.exe

build:
	gcc $(FILES) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o ./build/pr.exe

build-debug:
	gcc $(FILES) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g -o ./build/pr.debug

# build-debug:
# 	gcc $(FILES) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra -g  -o ./build/pr.debug

# run:
# 	./build/pr

.PHONY: build
