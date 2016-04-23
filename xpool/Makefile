all:t_xpool

t_xpool: test.o xpool.o
	gcc -g -o t_xpool xpool.o test.o

test.o:test.c xpool.h
	gcc -g -c test.c

xpool.o:xpool.c xpool.h
	gcc -g -c xpool.c 

clean:
	rm *.o
	rm t_xpool 
