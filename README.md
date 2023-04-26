# Subset-sum-problem
Subset sum problem resolve with Schroeppel-Shamir algorithm

Afin de bien utiliser le programme  :

Il est nécessaire de disposer de la bibliothèque [GMP](https://gmplib.org)


Pour utiliser l'algorithme de Schroeppel-Shamir il faut d'abord générer un fichier contenant les sommations à tester. Pour ce faire, il faut se rendre dans Schroeppel_Shamir_/ puis exécuter la commande **python3 generation_subset.py (dim) (num fichier)**.

Par exemple : **python3 generation_subset.py 16 32** -> On génère ici un fichier dans lequel on va pouvoir tester l'algorithme, qui aura pour nom : *generation32.txt* qui contiendra un vecteur de dimension 16.


Pour lancer l'algorithme de Schroeppel-Shamir il faut se rendre dans le dossier Schroeppel_Shamir_/ puis saisir la commande "**make**", puis "**./start (Target sum) (num fichier) (0 ou 1)**" dans votre terminal (1 pour afficher le résultat dans le terminl, dans le cas contraire 0).

Par exemple : **./start 2 32 1** -> On va ici lancer l'algorithme de Schroeppel-Shamir à partir du fichier *generation32.txt* dans lequel on va regarder si une ou plusieurs sommations donne 2.


Nous travaillons ici avec des éléments dans le vecteur qui ont pour valeur maximum 2^n. Ces grands entiers correspondent aux éléments pouvant être sommé, dans le but de tester l'implémentation de Schroeppel-Shamir ainsi que sa véracité.
