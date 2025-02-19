OBJS = main.c arraylist.c entity.c store.c


buildmac:
	clang -g -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a main.c -o ./build/pr

build: 
	gcc ./*.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra  -o ./build/pr

build-debug:
	gcc ./*.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra -g  -o ./build/pr.debug

run:
	./build/pr

.PHONY: build
