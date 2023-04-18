#include "word.h"

//Fonction qui renvoie 1 si une solution donnée est vraie, 0 sinon
//En paramètre : le tableau des éléments pouvant être sommé, la somme cherché, la solution proposé par le programme
int verificationSol(word* ai, word s, word Solution, short nbTableauS1, short nbTableauS2, short nbTableauS3, short nbTableauS4){
    
    unsigned long  i1, i2, i3, i4, nbEltParTab, nbElt;

    //On cherche à partir de la solution donné, les indices correspondant à une valeur binaire, qui associe les sommation effectué pour donner la solution.
    //C-à-d
    //Si ai = (2,3,4,5,6,7,8,9) et Solution = (136) base 10 <=> (10001000) base 2. (pour somme cible = 8)
    //Alors i1 = 2, i2 = 0, i3 = 2 et i4 = 0

    //On cherche les indices i1, i2, i3 et i4
    word tmp, mask;
    mpz_init(mask);

    mpz_init_set(tmp,Solution);
    mpz_fdiv_q_2exp(tmp,tmp,nbTableauS2+nbTableauS3+nbTableauS4);
    i1 = mpz_get_ui(tmp);

    mpz_set(tmp,Solution);
    mpz_fdiv_q_2exp(tmp,tmp,nbTableauS3+nbTableauS4);

    mpz_set_ui(mask,(1<<nbTableauS2)-1);
    mpz_and(tmp,tmp,mask);
    i2 = mpz_get_ui(tmp);

    mpz_set(tmp,Solution);
    mpz_fdiv_q_2exp(tmp,tmp,nbTableauS4);

    mpz_set_ui(mask,(1<<nbTableauS3)-1);
    mpz_and(tmp,tmp,mask);
    i3 = mpz_get_ui(tmp);

    mpz_set(tmp,Solution);

    mpz_set_ui(mask,(1<<nbTableauS4)-1);
    mpz_and(tmp,tmp,mask);
    i4 = mpz_get_ui(tmp);

    word rep;
    mpz_init(rep);

    int mask2 = 1, tmp2;

    // On associe les indices aux éléments qu'ils représentent dans ai et on les additionne
    // C-à-d
    // Si ai = (2,3,4,5,6,7,8,9). (pour somme cible = 8)
    // Alors i1 = 2, i2 = 0, i3 = 2 et i4 = 0
    // Et donc rep = 2 à la suite de la première condition if
    // rep = 2 à la suite de la deuxième condition if
    // rep = 8 à la suite de la troisième condition if

    if(AFFICHAGE)printf("\n\n\nSOMMATION : (entre crochet l'emplacement des éléments du vecteur)\n");
    for (int i = 0; i < 4; ++i){
        if(i==0){
            mask2 = 1;
            for(int j = nbTableauS1-1; j >= 0; --j){
                tmp2 = i1 & mask2;
                //Si <> de 0
                if(tmp2){
                    mpz_add(rep,rep,ai[j]);
                    if(AFFICHAGE)gmp_printf("%Zd [%d] + ",ai[j],j);
                }
                mask2 = mask2 << 1;
            }
        }
        else{
            if(i==1){
                mask2 = 1;
                for(int j = nbTableauS1+nbTableauS2-1; j >= nbTableauS1; --j){
                    tmp2 = i2 & mask2;
                    //Si <> de 0
                    if(tmp2){
                        mpz_add(rep,rep,ai[j]);
                        if(AFFICHAGE)gmp_printf("%Zd [%d] + ",ai[j],j);
                    }
                    mask2 = mask2 << 1;
                }
            }
            else{
                if(i==2){
                    mask2 = 1;
                    for(int j = nbTableauS1+nbTableauS2+nbTableauS3-1; j >= nbTableauS1+nbTableauS2; --j){
                        tmp2 = i3 & mask2;
                        //Si <> de 0
                        if(tmp2){
                            mpz_add(rep,rep,ai[j]);
                            if(AFFICHAGE)gmp_printf("%Zd [%d] + ",ai[j],j);
                        }
                        mask2 = mask2 << 1;
                    }
                }
                else{
                    mask2 = 1;
                    for(int j = nbTableauS1+nbTableauS2+nbTableauS3+nbTableauS4-1; j >= nbTableauS1+nbTableauS2+nbTableauS3; --j){
                        tmp2 = i4 & mask2;
                        //Si <> de 0
                        if(tmp2){
                            mpz_add(rep,rep,ai[j]);
                            if(AFFICHAGE)gmp_printf("%Zd [%d] + ",ai[j],j);
                        }
                        mask2 = mask2 <<1;
                    }
                }
            }
        }
    }
    if(AFFICHAGE)gmp_printf("0 = %Zd\n\n",s);

    //On vérifie si rep == s, si c'est le cas s est vérifié
    if(mpz_cmp(s,rep)==0){
        if(AFFICHAGE)printf("Résultat vérifié et cohérent\n\n");
        mpz_clears(mask,tmp,rep,NULL);
        return 1; //La solution est correct
    }
    else{
        if(AFFICHAGE)printf("Résultat vérifié et incohérent\n\n");
        mpz_clears(mask,tmp,rep,NULL);
        return 0; //La solution n'est pas correct
    }
    return 1;
}