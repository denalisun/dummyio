build:
	gcc src/main.c -Wall -o dummy -v -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

run:
	gcc src/main.c -Wall -o dummy -v -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
	dummy

clean:
	del dummy.exe