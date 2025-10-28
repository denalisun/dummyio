.PHONY: build build-win run clean

CC=gcc
OUT=bin/dummy
SRC=src/main.c src/game/player.c src/game/zombie.c src/game/world.c src/game/ui.c src/game/gun.c src/game/projectile.c src/structs/array.c src/utils.c
LDFLAGS=-L lib/ -lraylib -lm -lGL -lpthread -ldl -lrt -lX11 -I include/
CFLAGS=-Wall -Werror -std=c99

build:
	$(CC) $(SRC) $(CFLAGS) -o $(OUT) $(LDFLAGS)

win:
	x86_64-w64-mingw32-gcc $(SRC) $(CFLAGS) -o $(OUT) -L lib/ -lraylib.windows -lm -lopengl32 -lgdi32 -lwinmm -I include/

web:
	emcc -o $(OUT).html $(SRC) -Os $(CFLAGS) ./lib/libraylib.web.a -I include/ -s USE_GLFW=3 -DPLATFORM_WEB --shell-file ./shell.html

all: build win web

clean:
	rm -rf bin