#include <stdio.h>
#include <stdlib.h>
#include "automaton.h"
#include "dictionnaire.h"

/* Les fonctions tailleChaine, compareChaines, premiereOccurrence,
   sousTableau et lectureNewline sont utilisées dans les fonctions qui suivent */

int tailleChaine(char* s) {
    int size = 0;
    // loop invariant : s[size] is a character that does not correspond to the end of the string
    while (s[size] != '\0') 
        size++;
    return size;
}

int compareChaines(char* s1, char* s2) {
    // Deux chaînes de caractères ne peuvent être égales si elles n'ont pas la même taille
    if (tailleChaine(s1) != tailleChaine(s2)) return 0;
    else {
        for (int pos = 0; pos < tailleChaine(s1); pos++)
            if (s1[pos] != s2[pos])   // Si deux caractères placés au même endroit diffèrent, on renvoie 0
                return 0;
        return 1;    // Si on arrive en sortie de boucle, les chaînes de caractères sont égales, on renvoie 1
    }
}

int premiereOccurrence(int* t, int motif, int size) {
    for (int curseur = 0; curseur + 2 < size; curseur++) {
        int i = 0;
        // t has finite size, so the condition will either get false, or i will equal 3
        // so the while loop has finite iterations and terminates
        while (t[curseur+i] == motif) {
            i++;
            if (i == 3) return curseur;
        }
    }
    // Usually not reached, just to make sure the function always return something
    return -1;
}

// res is the part of the array s between inf and sup included
void sousTableau(int* res, int* s, int inf, int sup) {
    for (int k = inf; k <= sup; k++)
        res[k-inf] = s[k];
}

// The procedure detects and treats the newline characters at the end of the lines
void lectureNewline(FILE* f) {
    char newline;
    fread(&newline, 1, 1, f);
}

int litNbEtats(FILE* f) { 
    // Reading of the first line with fgets (at most 6 characters to stock)
    char buffer[6];
    fgets(buffer, 6, f);
    // The buffer is cut between two parts, the second one contains the number of states is the interesting one
    // and gets returned (read as an integer directly)
    int nbEtats;
    sscanf(buffer, "%*c %d", &nbEtats);
    return nbEtats;
}

int** creeMatriceActions(int n, FILE* f) {
    // Dynamic allocation of a 2D array of integers
    int** matrix = (int**) malloc(n*sizeof(int*));
    for (int k = 0; k < n; k++)
        matrix[k] = (int*) calloc(128, sizeof(int));
    
    // Reading of the second line, byte per byte
    for (int pos = 0; pos < n*128; pos++)
        fread(&matrix[pos / 128][pos % 128], 1, 1, f);
    
    // Lecture du '\n'
    lectureNewline(f);
    return matrix;
}

int* creeVecteurReduit(int n, FILE* f) {
    // Dynamic allocation of an array of int
    int* vecteur = (int*) malloc(n*sizeof(int));
    // Reading of the third line, byte per pyte
    for (int pos = 0; pos < n; pos++)
        fread(&vecteur[pos], 1, 1, f);

    // Lecture du '\n'
    lectureNewline(f);
    return vecteur;
}

void dicoSequence(FILE* f, dico* map1, dico* map2) { 
    // Dynamic allocation of an array of int (states + ASCII encoding characters)
    int lenSequence = 0;
    int* lastLinesASCII = malloc(3*2*256*128*sizeof(char)+1);    // 3*2*256*128 is a supremum of the number of characters to read
    /* loop invariant : the current position in the file matches with a valid character, until EOF occurs */
    while (!feof(f)) {
        fread(&lastLinesASCII[lenSequence], 1, 1, f);    // The reading is done byte per byte
        lenSequence++;
    }

    // The separator is stocked in finSequence, its ASCII in ent
    unsigned char finSequence = '\255';
    int ent = (int)finSequence;
    // Detection of the first sequence of '\255\255\255'
    int sep = premiereOccurrence(lastLinesASCII, ent, lenSequence);     // Size of the first elements (partial function decale)
    int tailleBranchement = (lenSequence-5)-(sep+3)+1;                  // Size of the second series of elements (partial function branchement)

    // Dynamic allocation of two arrays that will help the building of the dico elements
    // Based on the buffer lastLinesASCII
    int* decale = malloc(sep*sizeof(int));
    sousTableau(decale, lastLinesASCII, 0, sep-1);
    int* branchement = malloc(tailleBranchement*sizeof(int));
    sousTableau(branchement, lastLinesASCII, sep+3, lenSequence-5);
    // The next sequence begins at sep+3 and ends at lenSequence-5 (the separators are between lenSequence-4 and lenSequence-2, the \0 at lenSequence-1)

    // Creation of both dico elements, making sure no segmentation fault occurs (break action)
    // Since at the next iteration, it would occur without the break
    for (int pos = 0; pos+2 < sep; pos+=3) {
        // The second argument gets transformed in his (char) equivalent
        dico_add(decale[pos], (char)decale[pos+1], decale[pos+2], map1);
        if (pos + 3 == sep) break;
    }
    
    for (int pos = 0; pos+2 < tailleBranchement; pos+=3) {
        // Idem
        dico_add(branchement[pos], (char)branchement[pos+1], branchement[pos+2], map2);
        if (pos + 3 == tailleBranchement) break;
    }
}