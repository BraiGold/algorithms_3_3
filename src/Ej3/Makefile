.PHONY : all

CC = g++

all: ejercicio3 gen3

ejercicio3: ejercicio3.o
	$(CC) -std=c++11 ejercicio3.o -o ej3 -g

ejercicio3.o: ejercicio3.cpp ejercicio3.h
	$(CC) -std=c++11 ejercicio3.cpp -c -g

gen3: gen3.o
	$(CC) -std=c++11 gen3.o -o gen3 -g

gen3.o: gen3.cpp ejercicio3.h
	$(CC) -std=c++11 gen3.cpp -c -g

clean:
	rm -f *.o
	rm -f ej3 gen3