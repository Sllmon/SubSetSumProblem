//|___________________________________________________________________________________|//                                                                        |// 
//|Schroeppel-Shamir algorithm                                                        |// 
//|                                                                                   |//                                                                       |// 
//|Source : Papier de Nick Howgrave-Graham et Antoine Joux, New generic algorithms    |//
//|for hard knapsacks                                                                 |//
//|___________________________________________________________________________________|//

#include "word.h"

// Valeur de la taille de n <=> dimension du vecteur a
int WORD_SIZE = 8;
int AFFICHAGE = 1;

int main(int argc, char **argv){
    if(argc < 4){
        fprintf(stderr,"3 paramètres sont attendus :\n\n 1- Le résultat de la sommation attendu\n 2- Le numéro de la génération (correspondant au nom de fichier)\n 3- 0 sans affichage ou 1 avec affichage");
        exit(1);
    }

    // Valeur recherché par sommation des éléments du vecteur de a
    word TARGET;
    // On déclare le tableau qui contiendra les éléments du vecteur a
    word* ai = NULL;

    // Variables utilisées pour le calcul du temps d'exécution :
    clock_t begin, end;
    double time_spent = 0.0;
    double time[100] = {0};
    short nbTime = 0;


    // Récupértion de la saisie de l'utilisateur sur la valeur à trouver par sommation (le target)
    mpz_init_set_str(TARGET,argv[1],10);
    AFFICHAGE = atoi(argv[3]);
    
    // Lecture des informations sur le fichier saisie par l'utilisateur, on remplie le vecteur a avec les bons éléments, également WORD_SIZE    
    generation(&ai,argv[2]); 

    // On définit et déclare les variables utilent au bon déroulement du programme
    // On mesure le temps que ça prend
    begin = clock();
        // tailleTableauS correspond au nombre de cellules présentent dans un tableau contenant une partie de toutes les sommations possibles des valeurs du vecteur a
        // On va en fait découper notre vecteur a en 4 parties :
        // Si a = (1,2,3,4,5,6,7,8) alors
        // p1 = (1,2) (2 = tailleTableauS1); p2 = (3,4) (2 = tailleTableauS2); p3 = (5,6); p4 = (7,8) (ces variables ne sont pas crées)
        // T1S = (0,1,2,3) (4 = tailleTableauS1) <=> 2^tailletableauS1; T2S = (0,3,4,7); T3S = (0,5,6,11); T4S = (0,7,8,15)
        unsigned long tailleTableauS1, tailleTableauS2, tailleTableauS3, tailleTableauS4; // = (1UL<<(WORD_SIZE/4));
        short nbTableauS1, nbTableauS2, nbTableauS3, nbTableauS4;

        // Liste des solutions du Subset Sum Problem
        ListeSolConca Solution = NULL,
                      SolutionTete = NULL;

        // Si WORD_SIZE n'est pas disible par 4 on va obtenir dans tableaux de taille différente
        // On cherche alors ici à savoir combien de tableaux vont avoir une taille différente
        int w = WORD_SIZE,
            nbTableauTailleDif = 0;
        while(w % 4 != 0){
            w++;
            nbTableauTailleDif++;
        }
        nbTableauTailleDif = 4 - nbTableauTailleDif;
        // On associe la taille de chaque tableau
        if(nbTableauTailleDif != 0){
            int max = (int) ceil((double)WORD_SIZE/4),
                min = (int) floor((double)WORD_SIZE/4);
            nbTableauS1 = max;
            nbTableauTailleDif--;
            if (nbTableauTailleDif) nbTableauS2 = max; else nbTableauS2 = min;
            if(nbTableauTailleDif>0) nbTableauTailleDif--;
            if (nbTableauTailleDif) nbTableauS3 = max; else nbTableauS3 = min;
            nbTableauS4 = min;
        }
        else{
            nbTableauS1 = nbTableauS2 = nbTableauS3 = nbTableauS4 = WORD_SIZE/4;
        }

        // On associe le nombre d'éléments pour chaque tableau, c'est en fait 2^tailleTableauS1
        tailleTableauS1 = 1UL << nbTableauS1;
        tailleTableauS2 = 1UL << nbTableauS2;
        tailleTableauS3 = 1UL << nbTableauS3;
        tailleTableauS4 = 1UL << nbTableauS4;

        // Tableaux T?S contenant à eux 4 toutes les sommations possible des valeurs du vecteur a
        word* T1S = malloc(sizeof(word)*tailleTableauS1);
        word* T2S = malloc(sizeof(word)*tailleTableauS2);
        word* T3S = malloc(sizeof(word)*tailleTableauS3);
        word* T4S = malloc(sizeof(word)*tailleTableauS4);
        word* TabGray = malloc(sizeof(word)*tailleTableauS1); //tailleTableauS1 à la plus grosse taille

        // Initialisation des tableaux T?S et tabGray
        for(int i=0;i<tailleTableauS1;++i) mpz_init(T1S[i]);
        for(int i=0;i<tailleTableauS2;++i) mpz_init(T2S[i]);
        for(int i=0;i<tailleTableauS3;++i) mpz_init(T3S[i]);
        for(int i=0;i<tailleTableauS4;++i) mpz_init(T4S[i]);
        for(int i=0;i<tailleTableauS1;++i) mpz_init(TabGray[i]);

    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    time[nbTime++] = time_spent;
    // Fin de la définition et de la déclaration des variables utilent au bon déroulement du programme

    // Lancement de l'algorithme de Schroeppel_Shamir
    SolutionTete = Solution = Schroeppel_Shamir(ai,TARGET,T1S, nbTableauS1,T2S, nbTableauS2, T3S, nbTableauS3, T4S, nbTableauS4, Solution, TabGray, time,&time_spent,&nbTime);
    
    if(Solution != NULL){
        // On vérifie les solutions
       while(Solution->suivant != NULL){
            verificationSol(ai,TARGET,Solution->valeur,nbTableauS1,nbTableauS2,nbTableauS3,nbTableauS4);
            Solution = Solution->suivant;
       }
        if(Solution->suivant == NULL)
        verificationSol(ai,TARGET,Solution->valeur,nbTableauS1,nbTableauS2,nbTableauS3,nbTableauS4);
    }

    FILE* fichier_csv; int flag = 1;
    fichier_csv = fopen("time.csv","aw");
    if(fichier_csv == NULL) flag = 0;
    // Affichage du temps d'exécution
    for (int i = 0; i < nbTime; i++){
        if(AFFICHAGE){
            if(i == 0) printf("Temps jusqu'à la lecture du fichier %f\n",time[i]);
            if(i == 1) printf("Temps jusqu'à la déclaration des tableaux : %f\n",time[i]);
            if(i == 2) printf("Temps jusqu'au remplissage des tableaux : %f\n",time[i]);
        }  
        if(i == 3){
            if(AFFICHAGE)  printf("Temps jusqu'au trie des tableaux : %f\n",time[i]);
            // On affiche le temps total dans le csv
            if(flag) fprintf(fichier_csv,"%d;%f\n",WORD_SIZE,time[3]);
        }
    }
    if(flag) fclose(fichier_csv);
    
    //Libération de la mémoire
    liberer(ai,T1S,T2S,T3S,T4S,TabGray,tailleTableauS1,tailleTableauS2,tailleTableauS3,tailleTableauS4,SolutionTete);
    mpz_clear(TARGET);
}
