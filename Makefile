COMPILE=gcc src/main.c src/game/player.c src/game/zombie.c -Wall -o dummy -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lm

build:
	${COMPILE}

run:
	${COMPILE}
	dummy

clean:
	del dummy.exe