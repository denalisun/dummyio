SRC=src/main.c src/game/player.c src/game/zombie.c src/game/world.c src/game/ui.c src/game/gun.c src/game/projectile.c src/structs/array.c
COMPILE=gcc ${SRC} -Wall -o dummy -I include/ -L lib/ -lraylib -lm -lGL -lpthread -ldl -lrt -lX11

build:
	${COMPILE}

run:
	${COMPILE}
	./dummy

clean:
	rm dummy