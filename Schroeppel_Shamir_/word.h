#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

//Représentation d'un mot
typedef mpz_t word;

//valeur de la taille de n
extern int WORD_SIZE;

extern int AFFICHAGE;

typedef short bool;
#define true 1
#define false 0

//Définition d'un type permettant de retourner plusieurs informations à la suite de l'utilisation de la fonction gray
typedef struct{ 
    unsigned long n; // Représente le code de gray actuel
    unsigned long nPrec; // Représente le code de gray antérieur à l'appel de la fonction gray
    short bitChangement; // Précise l'emplacement du bit modifié
    short signe; // Précise s'il y a eu un retrait ou ajout de bit à 1
} graytab;

//Définition du type pair : Utile pour stocker en pair un mot et son indexe dans son tableau
typedef struct
{
    word word;
    unsigned long indexe;
}pair;

//Définition du type triple : Utile pour stocker en pair un mot, et un couple d'indexe représentant 
//l'emplacement dans leur deux tableaux respectives des deux valeurs somme du mot
typedef struct
{
    word word;
    unsigned long i;
    unsigned long j;
}triple;

//Définition du type solution : stocke les 4 indices représentant 
//l'emplacement dans leur tableaux respectives des valeurs somme du mot
typedef struct{
    unsigned long i;
    unsigned long j;
    unsigned long k;
    unsigned long l;
} solution;

//Définition des différents type de liste

typedef struct cellule2{
    solution valeur;
    struct cellule2* suivant;
} *ListeSol;

typedef struct cellule3{
    word valeur;
    struct cellule3* suivant;
} *ListeSolConca;


//Signatures des fonctions

//gray.c
unsigned long nombreDe0gauche(unsigned long);
graytab gray(unsigned long, graytab);

//free.c
void liberation(word*, unsigned long);
void liberationPair(pair*, unsigned long);
void liberer(word*,word*,word*,word*,word*,word*, unsigned long, unsigned long, unsigned long, unsigned long, ListeSolConca);
void liberer_ListeSol(ListeSol);
//modular_merge.c
unsigned long inverse(unsigned long, int);
void permuter(triple*, triple*);
unsigned long partition(triple*, long long, long long);
void triRapide(triple*, long long, long long);
void triParDenombrement(word*, pair*, pair*, unsigned long, unsigned long);
unsigned long parcoursT1S(unsigned long, word, unsigned long, unsigned long, word*);
void parcoursT2S(unsigned long, pair*, word*, word*, unsigned long, unsigned long, unsigned long, triple**, unsigned long*, unsigned long*);
triple* join(triple*, word*, unsigned long, word*, unsigned long, pair*, unsigned long, unsigned long, unsigned long*, unsigned long*);
ListeSol solver(ListeSol,triple*, word*, word*, pair*, unsigned long, unsigned long, unsigned long, unsigned long, word, unsigned long, unsigned long, unsigned long*, word*);
int chargement(unsigned long, unsigned long, int*);
ListeSol Modular_merge(word*, short, word*, short, word*, short, word*, short, word, word*,ListeSol, double*, double*, short*);
unsigned long dichotomie_pair(unsigned long, pair*, unsigned long);
unsigned long dichotomie_triple(unsigned long, triple*, unsigned long);

//liste.c
ListeSol AjouterListeSol(solution, ListeSol);
ListeSolConca AjouterListeSolConca(word, ListeSolConca);

//Schroeppel_Shamir.c
void CreationGray(word*, short);
void CreationT(word*, word*, short, short);
ListeSolConca concatenation(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, ListeSolConca);
ListeSolConca Schroeppel_Shamir(word*, word, word*, short, word*, short, word*, short, word*, short, ListeSolConca, word*, double*, double*, short*);

//parametre.c
void afficherA(word*);
int choixFichier(FILE*,char*);
int choixFichier2(FILE*,char*,char*);
void generation(word**,char*);

//verif.c
int verificationSol(word*, word, word, short, short, short, short);