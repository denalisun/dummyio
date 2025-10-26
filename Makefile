CC=gcc
OUT=dummy
SRC=src/main.c src/game/player.c src/game/zombie.c src/game/world.c src/game/ui.c src/game/gun.c src/game/projectile.c src/structs/array.c
LIB=-L lib/ -lraylib -lm -lGL -lpthread -ldl -lrt -lX11
INCLUDE=-I include/
COMPILE=$(CC) ${SRC} -Wall -Werror -std=c99 -o $(OUT) $(INCLUDE) $(LIB)

build:
	${COMPILE}

run:
	${COMPILE}
	./dummy

clean:
	rm dummy
