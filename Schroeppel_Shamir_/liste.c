#include "word.h"

ListeSol AjouterListeSol(solution s, ListeSol L){
    ListeSol lst = malloc(sizeof(struct cellule2));
    lst->valeur = s;
    lst->suivant = L;
    return lst;
}

ListeSolConca AjouterListeSolConca(word w, ListeSolConca L){
    ListeSolConca lst = malloc(sizeof(struct cellule3));
    mpz_init_set(lst->valeur,w);
    lst->suivant = L;
    return lst;
}