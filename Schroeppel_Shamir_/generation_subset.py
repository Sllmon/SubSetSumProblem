# Code qui génére un fichier texte contenant
#  -Une dimension = nombre d'éléments pouvant être sommé <=> nombre d'éléments dans le vecteur a
#  -Les éléments
#  -Une somme t, pouvant être obtenu par sommation des éléments

# La dimension doit être > 2
# Un minimum de deux éléments doit être sommé pour obtenir t

import random
import sys


if len(sys.argv) < 3:
    print("2 paramètres sont attendus :\n 1- Un entier correspondant à la taille <=> nombre d'élément pouvant contribuer à la sommation <=> dimension\n 2- Le numéro de la génération (correspondant au nom de fichier)")
else:
    n = int(sys.argv[1])
    numberFile = (sys.argv[2])
    nameFile = "generation" + numberFile +".txt"

    max = (2 ** n)

    with open(nameFile, "w") as fileout:
        fileout.write("Dim: " + str(n))
        vector_a = list()
        fileout.write("\na: ")
        for i in range(0,n-1):
            val = random.randint(0,max-1)
            vector_a.append(val)
            fileout.write(str(val)+", ")
        val = random.randint(0,max-1)
        vector_a.append(val)
        fileout.write(str(val)+"\n")


        #On choisit entre 2 et n-1 éléments dans a, pour générer un target sum
        choice = random.randint(2,n-1)
        cpt = 0
        #Tableau qui permet de savoir si un élément a déjà été comptabilisé dans la sommation
        # 0 pour non, 1 pour oui
        alreadyIn = []
        for i in range(0,n):
            alreadyIn.append(0)

        targetsum = 0
        while cpt < choice:
            #Permet de rendre aléatoire le choix des éléments
            tmp = random.randint(0,n-1)
            if alreadyIn[tmp] == 0:
                targetsum+=vector_a[tmp]
                alreadyIn[tmp] = 1
                cpt+=1

        fileout.write("t: "+str(targetsum))
        fileout.close()


#0 to n-1 we want ?