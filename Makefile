automaton: main.o pile.o dictionnaire.o automaton.o
	gcc -o automaton main.o pile.o dictionnaire.o automaton.o

pile.o: pile.c pile.h
	gcc -Wall -c pile.c

dictionnaire.o: dictionnaire.c dictionnaire.h
	gcc -Wall -c dictionnaire.c

automaton.o: automaton.c automaton.h dictionnaire.h
	gcc -Wall -c automaton.c

main.o: main.c pile.h automaton.h dictionnaire.h
	gcc -Wall -c main.c