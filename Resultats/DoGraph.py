import matplotlib.pyplot as plt
import csv
import numpy as np

x = []
y = []

x1 = []
y1 = []
x2 = []
y2 = []
x3 = []
y3 = []
x4 = []
y4 = []

with open('res.csv','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=';')
    cpt = 0
    for row in plots:
        x.append(float(row[0]))
        y.append(float(row[1])/60)
        if cpt == 0:
            x1.append(float(row[0]))
            y1.append(float(row[1])/60)
            cpt = cpt + 1
    
        else:
            if cpt == 1:
                x2.append(float(row[0]))
                y2.append(float(row[1])/60)
                cpt = cpt + 1
            else:
                if cpt == 2:
                    x3.append(float(row[0]))
                    y3.append(float(row[1])/60)
                    cpt = cpt + 1
                else:
                    if cpt == 3:
                        x4.append(float(row[0]))
                        y4.append(float(row[1])/60)
                        cpt = 0


# moindre au carré
# co = np.polyfit(x,y,1)
# a = co[0]
# b = co[1]
# plt.semilogy(a,b)

#plt.semilogy(x,y)
plt.semilogy(x1,y1, color='red')
plt.semilogy(x2,y2, color='green')
plt.semilogy(x3,y3, color='blue')
plt.semilogy(x4,y4, color='black')

plt.scatter(x1,y1, color='red')
plt.scatter(x2,y2, color='green')
plt.scatter(x3,y3, color='blue')
plt.scatter(x4,y4, color='black')



#plt.axis([25, 75, 0, 1000000])
#plt.scatter(x,y, label='Chargé depuis un csv')
plt.xlabel('x = nb dimension')
plt.ylabel("y = Temps d'exécution en minutes")
plt.title('Schroeppel-Shamir algorithm\nTime')

plt.legend()

plt.show()