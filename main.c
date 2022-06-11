// Importation des bibliothèques et headers nécessaires

#include <stdio.h>
#include <stdlib.h>
#include "pile.h"
#include "automaton.h"
#include "dictionnaire.h"

// La fonction traite en entier le fichier et les lettres en entrée
void traitementFichier(FILE* f) {

    // Etape 1 : Traitement du fichier - Création des structures de données nécessaires
    int n = litNbEtats(f);                                    // Nombre d'états de l'automate
    int** matriceActions = creeMatriceActions(n, f);          // Matrice des actions de taille n*128
    int* firstCompReduce = creeVecteurReduit(n, f);           // Vecteur de la première composante de Réduit, pour tout état
    int* secondCompReduce = creeVecteurReduit(n, f);          // Vecteur de la seconde composante de Réduit, pour tout état

    dico mapDecale = creeDico();                              // Initialisation des deux dictionnaires servant à stocker les résultats
    dico mapBranchement = creeDico();                         // des deux fonctions partielles décale et branchement
    dicoSequence(f, &mapDecale, &mapBranchement);             // Remplissage des dictionnaires


    // Affichage des structures de données
    /*printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 128; j++)
            printf("%d ", matriceActions[i][j]);
        printf("\n");
    }
    for (int k = 0; k < n; k++)
        printf("%d %c\n", firstCompReduce[k], secondCompReduce[k]);
    print_dico(mapDecale);
    print_dico(mapBranchement);*/
    

    // Etape 2 : Traitement des mots issus de l'entrée standard
    /* loop invariant : the user enters a word on the keyboard until he
       puts "Fin de lecture\n", which stops the while loop */
    while (1) {
        // Obtention de l'entrée standard avec fgets
        char mot[256];            // Buffer qui sert à contenir l'entrée standard
        fgets(mot, 256, stdin);   // Lecture de l'entrée standard
        Pile stack = initPile();  // Initialisation de la pile
        int curseur = 0;          // Sert au parcours de l'entrée

        // Libération de la mémoire après avoir testé les entrées - Insertion de "Fin de lecture\n" au clavier
        if (compareChaines(mot, "Fin de lecture\n")) {
            // Libération mémoire des deux composantes de Réduit
            free(firstCompReduce);
            free(secondCompReduce);

            // Libération mémoire des deux dictionnaires
            delete_all(&mapDecale);
            delete_all(&mapBranchement);

            // On libère d'abord les lignes de la matrice avant de libérer le vecteur des pointeurs sur les lignes
            // => On évite la fuite mémoire !
            for (int ligne = 0; ligne < n; ligne++)
                free(matriceActions[ligne]);
            free(matriceActions);

            // Fin de l'exécution du programme
            printf("Lecture interrompue : Fin d'exécution\n");
            return;
        }

        // Traitement du mot en entrée standard (qui n'est pas "Fin de lecture\n")
        else {
            /* loop invariant : an action is assigned to a character of the word, which will
               eventually accept or reject the word, based on the format of the automaton */
            while (1) {
                char caractere = mot[curseur];
                int ascii = (int)caractere;                       // Code ASCII du caractère en cours
                int etatCourant = stack.tab[stack.top];           // Accès à l'état courant
                int action = matriceActions[etatCourant][ascii];  // Accès à l'action via la matrice
                if (action == 0) {           // Rejette
                    printf("Rejected\n");
                    // Question bonus : indication du niveau où l'automate n'a pas reconnu l'entrée
                    printf("Erreur au niveau du caractère n°%d : %c\n", curseur+1, caractere);
                    break;
                }
                else if (action == 1) {      // Accepte
                    printf("Accepted\n");
                    break;
                }
                else if (action == 2) {      
                    // Empile décale(etatCourant, caractere), et passe à la lettre suivante
                    empiler(&stack, find_etat_sortie(etatCourant, caractere, mapDecale));
                    curseur++;
                }
                else {                       
                    // Dépile p états, puis empile branchement(etatDepile, A), on reste à la lettre courante
                    int p = firstCompReduce[etatCourant];
                    char A = (char)secondCompReduce[etatCourant];
                    int etatDepile = depilerPlusieurs(&stack, p);
                    empiler(&stack, find_etat_sortie(etatDepile, A, mapBranchement));
                }
            }
        }
    }
}


int main(int argc, char** argv) {

    // Si le nombre d'arguments est différent de 2 (nom de l'exécutable + fichier de l'automate),
    // on renvoie une erreur et on termine le programme
    if (argc != 2) {
        perror("Mauvais nombre d'arguments");
        exit(2);
    }

    // Ouverture du fichier binaire en lecture seule, dont le nom est contenu dans argv[1]
    FILE* f = fopen(argv[1], "rb");

    // Si le fichier n'a pas pu être ouvert, on renvoie une erreur
    // et on termine le programme
    if (f == NULL) {
        perror("Le fichier n'a pas pu être ouvert");
        exit(3);
    }
    // Sinon, c'est que le fichier a pu être ouvert sans encombre, on poursuit
    else
        printf("File \"%s\" correctly read. Please enter your inputs.\n", argv[1]);

    // Traitement du fichier et des entrées standard
    traitementFichier(f);

    // Fermeture du fichier
    fclose(f);
    return 0;
}