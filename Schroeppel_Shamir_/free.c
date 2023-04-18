#include "word.h"
 
//Fonctions qui permettent de libérer de la mémoire

void liberation(word* w,unsigned long N){
    for (unsigned long i = 0; i < N; ++i){
        mpz_clear(w[i]);
    }
    free(w);
}

void liberationPair(pair* w,unsigned long N){
    for (unsigned long i = 0; i < N; ++i){
        mpz_clear(w[i].word);
    }
    free(w);
}

void liberer_ListeSol(ListeSol SOL){
    ListeSol tmp = NULL;
    if(SOL!=NULL){
        while(SOL->suivant!=NULL){
            tmp = SOL;
            SOL = SOL->suivant;
            free(tmp);
        }
    }
    free(SOL);
}

void liberer(word* ai,word* T1S,word* T2S,word* T3S,word* T4S,word* tabGray, unsigned long t1, unsigned long t2, unsigned long t3, unsigned long t4, ListeSolConca Solution){
    liberation(ai,WORD_SIZE);
    liberation(T1S,t1);
    liberation(T2S,t2);
    liberation(T3S,t3);
    liberation(T4S,t4);
    liberation(tabGray,t1);
    ListeSolConca tmp = NULL;
    if(Solution!=NULL){
        while(Solution->suivant!=NULL){
            mpz_clear(Solution->valeur);
            tmp = Solution;
            Solution = Solution->suivant;
            free(tmp);
        }
        mpz_clear(Solution->valeur);
    }
    free(Solution);
}