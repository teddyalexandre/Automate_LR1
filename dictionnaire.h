#include <stdio.h>
#include <stdlib.h>

/* Utilisation d'une structure de dictionnaire afin de "représenter" les données
   des fonctions partielles décale et branchement dans une structure de données 
   facilement manipulable. Elle s'appuie sur l'implémentation des listes chaînées,
   plus souple et naturelle qu'avec des tableaux statiques */

/* type abstrait du dictionnaire */
typedef struct bucket* dico;

/* @requires nothing
   @assigns NULL pointer
   @ensures a new dico element is created */
dico creeDico();

/* @requires *map is a valid dico element, etat_i and etat_s are integers, car is a character
   @assigns map
   @ensures the set {etat_i, car, etat_s} figures in *map */
void dico_add(int etat_i, char car, int etat_s, dico* map);

/* @requires map is a valid dico, etat and car are respectively an integer and a character
   @assigns nothing
   @ensures the value s corresponding to the set {etat, car, s} in the dico exists and is returned */
int find_etat_sortie(int etat, char car, dico map);

/* @requires map is a valid dico
   @assigns nothing
   @ensures the values of map are printed */
void print_dico(dico map);

/* @requires *map is a valid dico
   @assigns nothing
   @ensures all the elements of *map are removed */
void delete_all(dico* map);