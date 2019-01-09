all: player dealer

player: player.o pipe_networking.o
	gcc -o player player.o pipe_networking.o

dealer: dealer.o pipe_networking.o
	gcc -o dealer dealer.o pipe_networking.o card.o

player.o: player.c pipe_networking.h
	gcc -c player.c

dealer.o: dealer.c pipe_networking.h card.h dealer.h
	gcc -c -g dealer.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

clean:
	rm *.o
	rm *~
