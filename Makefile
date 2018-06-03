cc = mipsel-linux-gcc

all:
	$(cc) server.c display.c network.c camera.c cmd.c -o qq_320 -lpthread

clean:
	rm qq_320
