#include "word.h"

/// @brief Fonction qui permet de créer un tableau qui contient les valeurs du code de gray dans l'ordre croissant
/// @param tabGray Tableau qui va contenir le code de gray
/// @param taille valeur entière qui indique le nombre d'éléments (log2) souhaité dans le tableau
void CreationGray(word* tabGray, short taille){

    graytab tab;
    tab.n = 0;
    tab.nPrec = 0;
    tab.bitChangement = 0;
    tab.signe = 0;

    mpz_set_ui(tabGray[0],0);

    //Construit le tableau tabGray
    for(unsigned long i = 0;i<(1ULL<<taille);++i){
        if(tab.n!=0){
            //On cherche l'actuel code de gray associé à l'entier i
            tab = gray(i,tab);
            mpz_set_ui(tabGray[i],tab.n);
            tab.nPrec = tab.n;
        }
        else{
            // Pour i = 0
            mpz_set_ui(tabGray[0],0);
            tab.n=1;
        }
    }
}


/// @brief Fonction qui permet de créer les différents tableaux utilisés dans l'algorithme de Schroeppel-Shamir algotithm, on effectue ici toutes les sommations possibles
/// @param TS Tableau de grand entiers dans lequel on va ajouter toutes les sommations possibles
/// @param ai Tableau des éléments du vecteur a
/// @param place Premier indice du tableau ai dans lequel il faut considérer l'éléments pour la sommation 
/// @param taille Nombre d'indices à considérer dans la sommation
void CreationT(word* TS, word* ai, short place, short taille){

    // Variable utile pour sommer des éléments à partir d'un tableau qui contient le code de Gray
    graytab tab;
    // On initialise ses paramètres
    tab.n = 0;
    tab.nPrec = 0;
    tab.bitChangement = 0;
    tab.signe = 0;
    
    //Construit le tableau TS en lui ajoutant toutes les possibilités de sommation des éléments ai à partir de l'indice place, pour environ WORD_SIZE/4 éléments de ai
    for(unsigned long i = 0;i<(1UL<<taille);++i){
        if(tab.n!=0){
            //On cherche l'actuel code de gray associé à l'entier i
            tab = gray(i,tab);
            //Condition permettant de savoir s'il faut ajouter ou soustraire 
            if(tab.signe==0){
                mpz_add(TS[i],TS[i-1],ai[tab.bitChangement-1+place]);
            }
            else{
                mpz_sub(TS[i],TS[i-1],ai[tab.bitChangement-1+place]);
            }
            tab.nPrec = tab.n;
        }
        else{
            // Pour i = 0
            mpz_set_ui(TS[i],0);
            tab.n=1;
        }
    }
}


/// @brief Fonction qui permet de concaténer 4 valeurs entière et affiche une solution de l'algorithme de Schroeppel-Shamir
/// @brief C-à-d Si w1 = 2, w2 = 0, w3 = 2 et w4 = 0 et taille = 2 Alors la solution <=> (10001000) base 2 <=> (136) base 10
/// @param w1 représente le premier quart de ai
/// @param w2 représente le deuxième quart de ai
/// @param w3 représente le troisième quart de ai
/// @param w4 représente le dernier quart de ai
/// @param t2 taille du deuxième quart de ai
/// @param t3 taille du troisième quart de ai
/// @param t4 taille du dernier quart de ai
/// @param Solution Liste des solutions (vecteur ai) concaténé
ListeSolConca concatenation(unsigned long w1, unsigned long w2, unsigned long w3, unsigned long w4, unsigned long t2, unsigned long t3, unsigned long t4, ListeSolConca Solution){
    unsigned long res, ww1, ww2, ww3;

    ww1 = w1<<(t2+t3+t4);
    ww2 = w2<<(t3+t4);
    ww3 = w3<<(t4);

    res = ww1 | ww2;
    res = res | ww3;
    res = res | w4;
    word res2;
    mpz_init_set_ui(res2,res);

    //Ajout de la valeur concaténé dans une ListeSolConca, à terme, toutes les solutions y seront stockées
    Solution = AjouterListeSolConca(res2,Solution);

    // On affiche l'une des solutions
    if(AFFICHAGE) printf(" solution : %lu",res);

    //Libération de l'espace libre
    mpz_clear(res2);

    return Solution;
}


/// @brief Schroeppel-Shamir algorithm
/// @param ai Un pointeur sur le vecteur a
/// @param s Target sum
/// @param T1S Tableau contenant 2^(WORD_SIZE/4) sommations. Premier 1/4 des élements du vecteur a.
/// @param nbTableauS1 Nombre d'éléments utilisés pour les sommations obtenus dans T1S
/// @param T2S Tableau contenant environ 2^(WORD_SIZE/4) sommations = 2^(nbTableauS2). Deuxième 1/4 des élements du vecteur a.
/// @param nbTableauS2 Nombre d'éléments utilisés pour les sommations obtenus dans T2S
/// @param T3S Tableau contenant environ 2^(WORD_SIZE/4) sommations = 2^(nbTableauS3). Troisième 1/4 des élements du vecteur a.
/// @param nbTableauModular_mergeS3 Nombre d'éléments utilisés pour les sommations obtenus dans T3S
/// @param T4S Tableau contenant environ 2^(WORD_SIZE/4) sommations = 2^(nbTableauS4). Dernier 1/4 des élements du vecteur a.
/// @param nbTableauS4 Nombre d'éléments utilisés pour les sommations obtenus dans T4S
/// @param Solution Liste des solutions (vide).
/// @param time
/// @param time_spent
/// @param nbTime
ListeSolConca Schroeppel_Shamir(word* ai, word s, word* T1S, short nbTableauS1, word* T2S, short nbTableauS2, word* T3S, short nbTableauS3, word* T4S, short nbTableauS4, ListeSolConca Solution, word* TabGray, double *time, double *time_spent, short *nbTime){
    
    // On mesure le temps que ça prend
    clock_t begin, end;
    begin = clock();
        // On créer un tableau qui contient les valeurs du code de gray dans l'ordre croissant
        CreationGray(TabGray,nbTableauS1);
        // On remplit les quatres tableaux T1S, T2S, T3S et T4S de leur sommation
        CreationT(T1S,ai,0,nbTableauS1);
        CreationT(T2S,ai,nbTableauS1,nbTableauS2);
        CreationT(T3S,ai,nbTableauS1+nbTableauS2,nbTableauS3);
        CreationT(T4S,ai,nbTableauS1+nbTableauS2+nbTableauS3,nbTableauS4);
    end = clock();
    (*time_spent) += (double)(end - begin) / CLOCKS_PER_SEC;
    time[(*nbTime)++] = (*time_spent);

    // On merge les tableaux et récupère la liste des solutions
    ListeSol SOL = NULL,
             SOLtete = NULL;
    SOLtete = SOL = Modular_merge(T1S, nbTableauS1, T2S, nbTableauS2, T3S, nbTableauS3, T4S, nbTableauS4, s, TabGray, SOL,time, time_spent, nbTime);

    //On affiche les solutions
    if(SOL!=NULL){
        if(AFFICHAGE) gmp_printf("\n\nLES SOLUTIONS POUR UN TARGET DE %Zd, SONT",s);
        while(SOL->suivant!=NULL){
            if(AFFICHAGE) gmp_printf("\n %llu %llu %llu %llu",SOL->valeur.i,SOL->valeur.j,SOL->valeur.k,SOL->valeur.l);

            Solution = concatenation(SOL->valeur.i,SOL->valeur.j,SOL->valeur.k,SOL->valeur.l,nbTableauS2,nbTableauS3,nbTableauS4,Solution);
            SOL = SOL->suivant;
        }
        if(AFFICHAGE) gmp_printf("\n %llu %llu %llu %llu",SOL->valeur.i,SOL->valeur.j,SOL->valeur.k,SOL->valeur.l);
        Solution = concatenation(SOL->valeur.i,SOL->valeur.j,SOL->valeur.k,SOL->valeur.l,nbTableauS2,nbTableauS3,nbTableauS4,Solution);
    }
    else{
        Solution = NULL;
        // system("clear");
        if(AFFICHAGE) afficherA(ai);
        if(AFFICHAGE) gmp_printf("\nPAS DE SOLUTIONS POUR UN TARGET DE %Zd\n",s);
    }
    liberer_ListeSol(SOLtete);
    return Solution;
}