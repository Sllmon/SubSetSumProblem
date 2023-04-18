
import sys
import subprocess

#1 = nb et 2 : le pas
if len(sys.argv) < 3:
    print("2 paramètres sont attendus :\n 1- Un entier correspondant à la taille <=> nombre d'élément pouvant contribuer à la sommation <=> dimension\n 2- Le numéro de la génération (correspondant au nom de fichier)")
else:
    nb = int(sys.argv[1])
    pas = int(sys.argv[2])
    for i in range(4,nb+1,pas):
        args = ["40",str(i)]
        sys.argv[1] = str(i)
        sys.argv[2] = str(i)
        print(sys.argv[1]+" "+sys.argv[2])
        exec(open("generation_subset.py").read(),None,None)
        proc = subprocess.run(['./start', str(i+1), str(i+1), "0"])