all: player dealer

player: player.o networking.o
	gcc -o player player.o networking.o

dealer: dealer.o networking.o
	gcc -o dealer dealer.o networking.o

player.o: player.c networking.h
	gcc -c player.c

dealer.o: dealer.c networking.h dealer.h
	gcc -c -g dealer.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm *.o
	rm *~
