build:
	clang -g -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a main.c -o ./build/pr

run:
	./build/pr


.PHONY: build