/* Réalisation de l'interface d'une pile ici statique, puisque le
nombre maximal d'états est connu à l'avance. On réalise une structure
composée de l'élément au sommet et d'un tableau : l'empilement se fait par la droite.
On utilise les fonctions de test de vacuité, d'affichage, d'empilement et
de dépilement */

#include <stdio.h>
#include <stdlib.h>
#define MAX_ETATS 256


/* top est le sommet de la pile, tab le tableau qui sert de support à la pile
   Une pile est initialisée avec top égal à 0, au vu des contraintes de l'énoncé */
typedef struct Pile {
    int top;
    int tab[MAX_ETATS];
} Pile;

/* @requires : nothing
   @assigns a new pile
   @ensures a new pile is created */
Pile initPile();

/*  @requires nothing
    @assigns nothing
    @ensures : checks whether the pile is empty or not 
    (returns either 1 or 0) */
int estVide(Pile pile);

/*  @assigns nothing
    @assigns nothing
    @ensures : displays the elements in the pile */
void affichePile(Pile pile);

/*  @requires : ppile contains the address of a valid pile
    @assigns : one of the cases of the array ppile->tab gets changed
    @ensures : the new top of the pile is after the former one */
void empiler(Pile* ppile, int etat);

/*  @requires : n is inferior or equal to ppile->top, ppile points to a non-empty stack
    @assigns : etatDepile is the value at the new top of ppile
    @ensures : returns the value at the new top of ppile : the n former values
               of *ppile are no more accessible */
int depilerPlusieurs(Pile* ppile, int n);