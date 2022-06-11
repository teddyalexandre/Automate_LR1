#include <stdio.h>
#include <stdlib.h>
#include "pile.h"


// Creation of a new pile : the top is set to 0 initially
Pile initPile() {
    Pile pile;
    pile.top = 0;
    pile.tab[pile.top] = 0;
    return pile;
}

// A pile is empty when top equals 0
int estVide(Pile pile) {
    return (pile.top == 0);
}

void affichePile(Pile pile) {
    // The pile is parsed 
    for (int i = 0; i <= pile.top; i++)
        printf("%i ", pile.tab[i]);
    printf("\n");
}

// etat is added at the top, incremented by 1
void empiler(Pile* ppile, int etat) {
    ppile->top = ppile->top + 1;
    ppile->tab[ppile->top] = etat;
}

// Based on the former function, the value at the top is saved, 
// then n pops are done successfully
int depilerPlusieurs(Pile* ppile, int n) {
    int etatDepile = ppile->tab[ppile->top - n];
    ppile->top -= n;
    return etatDepile;
}