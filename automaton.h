#include <stdio.h>
#include <stdlib.h>
#include "dictionnaire.h"

/* @requires s is a valid string
   @assigns nothing
   @ensures the result corresponds to the size of s */
int tailleChaine(char* s);

/* @requires s1 and s2 are valid strings
   @assigns nothing
   @ensures the comparison of s1 and s2 (equal or not) */
int compareChaines(char* s1, char* s2);

/* @requires size is the size of t, motif represents '\255'
   @assigns nothing
   @ensures the position of the first occurrence of motif is returned,
            set to -1 if it doesn't appear in t */
int premiereOccurrence(int* t, int motif, int size);

/* @requires inf and sup are between 0 and n, n being the size of s
   @assigns res
   @ensures res is the part of s between inf and sup */
void sousTableau(int* res, int* s, int inf, int sup);

/* @requires f is a binary file descriptor
   @assigns nothing
   @ensures a newline character is read from f */
void lectureNewline(FILE* f);

/* @requires f is a binary file descriptor (read only mode)
   @assigns nothing
   @ensures the number of states of the automaton descripted in f is returned */
int litNbEtats(FILE* f);

/* @requires the value of n between 0 and 255 and f a binary file descriptor
   @assigns nothing
   @ensures the matrix of actions has valid components (values between 0 and 3), dimensions of n*128 */
int** creeMatriceActions(int n, FILE* f);

/* @requires n between 0 and 255, f a binary file descriptor
   @assigns nothing
   @ensures an array of int is returned, size being n */
int* creeVecteurReduit(int n, FILE* f);


/* @requires *map1 and *map 2 are dico elements, f a binary file descriptor
   @assigns *map1 and *map2
   @ensures *map1 is the dico elements representing the partial function decale
            *map 2 the one of branchement */
void dicoSequence(FILE* f, dico* map1, dico* map2);