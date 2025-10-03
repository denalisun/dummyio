build:
	gcc src/main.c -Wall -o dummy -v -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

run:
	gcc src/main.c src/game/player.c -Wall -o dummy -v -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lm
	dummy

clean:
	del dummy.exe