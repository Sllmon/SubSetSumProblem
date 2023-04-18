#include "word.h"

// Fonctions permettant de connaître le code de gray de sa valeur parrallèle entière (inconvénient : besoin de connaître la valeur du code de gray précédent)

    // Fonction qui permet de chercher le nombre de bit à 0 à gauche du dernier bit à 1, et retourne ce résultat + 1
    unsigned long nombreDe0gauche(unsigned long n){
        unsigned long i = 0;
        unsigned long temp = 0;
        if(n!=0){
            while(temp==0){
                temp = n & (1<<i);
                i++;
            }
        }
        else{
            i++;
        }
        return i;
    }

    // Fonction qui renvoie le nombre de gray correspondant à partir, d'un nombre entier correspondant au code de gray associé, et le code de gray correspondant à l'entier associé n-1
    // n est en fait l'indice du numéro de gray, c-à-d si n = 10, on cherche le 10ème code de gray existant.
    graytab gray(unsigned long n, graytab tab){
        unsigned long Nb0 = nombreDe0gauche(n);
        unsigned long temp = tab.nPrec >> (Nb0-1);
        if(temp % 2 == 0){
            tab.n = tab.nPrec+(1<<(Nb0-1));
            tab.signe = 0;
        }
        else{
            tab.n = tab.nPrec-(1<<(Nb0-1));
            tab.signe = 1;
        }
        tab.bitChangement = Nb0;
        return tab;
    }

    // Regarder cette fonction pour optimiser nombreDe0gauche()

    // //Fonction qui renvoie l'emplacement du bit dans la variable "bit"
    // //La variable "bit" contiendra uniquement une valeur composé dans sa forme binaire d'un seul bit à 1
    // //Renvoie 3 si bit = (0000100)2
    // unsigned long emplacementBit(unsigned long bit){
    //     unsigned long r=0;
    //     while(bit!=0){
    //         bit = bit / 2;
    //         r++;
    //     }
    //     return r;
    // }