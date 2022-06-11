#include <stdio.h>
#include <stdlib.h>
#include "dictionnaire.h"

/* definition of the concrete type struct bucket : 2 integers, 1 character,
   one pointer to a bucket (dico type) */
struct bucket {
    int etatEntree;
    char symbole;
    int etatSortie;
    dico next;
};

// Returns the pointer NULL
dico creeDico() {
    return NULL;
}

// The addition is done from the beginning
void dico_add(int etat_i, char car, int etat_s, dico* map) {
    // Dynamic allocation of a struct bucket element
    dico new_map = malloc(sizeof(struct bucket));
    new_map->etatEntree = etat_i;
    new_map->symbole = car;
    new_map->etatSortie = etat_s;
    new_map->next = *map;   // new_map points to *map
    *map = new_map;         // *map points to new_map, in order to have he new elements
}

int find_etat_sortie(int etat, char car, dico map) {
    // The whole dico is parsed
    while (map != NULL) {
        if (map->etatEntree == etat && map->symbole == car)
            return map->etatSortie;
        map = map->next;
    }
    // If the inputs do not figure in the dico, we return 0
    return 0;
}

void print_dico(dico map) {
    // The whole dico is parsed
    while (map != NULL) {
        printf("%d %c %d\n", map->etatEntree, map->symbole, map->etatSortie);
        map = map->next;
    }
}

void delete_all(dico* map) {
    // The whole dico is parsed
    while (*map != NULL) {
        dico tmp = *map;
        *map = (*map)->next;
        free(tmp);
    }
}

// On the last three functions, the while loops all terminate since the size
// of the dico(*) element strictly diminishes (map = map->next decrements the size of map by 1) and
// will eventually reach 0