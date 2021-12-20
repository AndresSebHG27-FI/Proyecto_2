programa: main.o polinomios.o
	gcc -o programa main.o polinomios.o
main.o: main.c polinomio.h
	gcc -c main.c
polinomios.o: polinomios.c polinomio.h
	gcc -c polinomios.c