#include "word.h"

#include <string.h>

// Fonctions de paramétrage avant opérations

    /// @brief Fonction qui permet d'afficher les éléments du vecteur a
    /// @param ai Un pointeur sur le vecteur a
    void afficherA(word* ai){
        printf("\na = (");
        for(int i = 0; i<WORD_SIZE-1; ++i){
            gmp_printf("%Zd,",ai[i]);
        }
        gmp_printf("%Zd)\n",ai[WORD_SIZE-1]);
    }

    //Fonction qui permet de choisir le fichier de lecture
    /// @brief Fonction qui permet de choisir le fichier de lecture
    /// @param Texte FILE*
    /// @param destination path : char*
    int choixFichier(FILE* Texte, char* destination){
        int numeroInt;
        char numeroChar[255]="";
        printf("Numéro de la génération (correspondant au nom de fichier) :\n");
        scanf("%d",&numeroInt);
        sprintf(numeroChar,"%d",numeroInt);
        strcpy(destination,"generation");
        strcat(destination,numeroChar);
        strcat(destination,".txt");
        Texte = fopen(destination, "r");
        if (Texte == NULL){
            printf("Erreur fichier introuvable\n");
            choixFichier(Texte,destination);
        }
        else{
            if(AFFICHAGE) printf("Fichier trouvé\n");
            fclose(Texte);
        }
        return 1;
    }

    //Fonction qui permet de choisir le fichier de lecture
    int choixFichier2(FILE* Texte, char* destination, char* Numfile){
        int numeroInt;
        char numeroChar[255]="";
        strcpy(destination,"generation");
        strcat(destination,Numfile);
        strcat(destination,".txt");
        Texte = fopen(destination, "r");
        if (Texte == NULL){
            printf("Erreur fichier introuvable\n");
            choixFichier(Texte,destination);
        }
        else{
            if(AFFICHAGE) printf("Fichier trouvé\n");
            fclose(Texte);
        }
        return 1;
    }

    /// @brief Fonction qui permet de générer à partir d'un fichier les éléments du vecteur a, et la bonne dimension WORD_SIZE de ce vecteur.
    /// @param ai Un pointeur sur le vecteur a
    void generation(word** ai, char* file){
        // LECTURE DU FICHIER
            FILE *Texte = NULL;
            char tmp[2500] = "";

            char dimensionChar[255];
            int dimensionInt;

            char aiChar[2500];

            char destination[255];
            char* token;

            int retour = choixFichier2(Texte,destination,file);
            Texte = fopen(destination, "r");

            if(retour == 1){
                // On lit la ligne correspondant à la dimension
                int i = 0, j = 5;
                fgets(tmp,255,Texte);

                while(tmp[j]!='\n'){
                    dimensionChar[i] = tmp[j];
                    j++;
                    i++;
                }
                dimensionChar[i] = '\0';
                sscanf(dimensionChar,"%d",&WORD_SIZE);

                // On définit le tableau qui contiendra les éléments du vecteur a
                *ai = (word*) malloc(sizeof(word)*WORD_SIZE);
                for(int i=0;i<WORD_SIZE;++i){
                    mpz_init((*ai)[i]);
                }
                
                int n = 0, flag =0, erreur=0; // saut virgule
                i = 0, j = 3;
                mpz_t elt;
                mpz_init(elt);
                fgets(tmp,2500,Texte);
                // On lit les valeurs du vecteur ai
                while(1){
                    if(tmp[j]>=48 && tmp[j] <=57){
                        aiChar[i] = tmp[j];
                        j++;
                        i++;
                    }
                    else{
                        if(tmp[j]=='\n'){
                            flag =1;
                        }
                        aiChar[i] = '\0';


                        erreur = mpz_set_str((*ai)[n],aiChar,10);
                        if(erreur == -1){
                            printf("\n erreur");
                            break;
                        }
                        n++;
                        j = j+2; // on ignore virgule et espace
                        for (int k = 0; k < i; k++){ // on vide les cellules remplies
                            aiChar[k]= 0;
                        }
                        i = 0;
                    }
                    if(flag){
                        break;
                    }
                }
                mpz_clear(elt);
                fclose(Texte);
            }
        if(AFFICHAGE)afficherA(*ai);
    }

// Fin des fonctions de paramétrage avant opérations