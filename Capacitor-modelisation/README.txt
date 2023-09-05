Alban Dietrich, BA3-Physique, n°ID : 000440726, 7/12/2018

Compléments de calcul numérique, Projet 2018-2019

Un menu est mis à disposition afin de faciliter l’étude des données au sein d’un condensateur.
Le problème a été modélisé de façon général, c’est-à-dire qu’on peut adapter le code à n’importe quel projet en changeant simplement des variables. 
J’ai rajouté une option qui représente le résidu (pour le solveur AGMG et UMFPACK) en fonction
du my (qui est proportionnel au pas de discrétisation) sur un graphique. 

Question 1 :
	Une fonction affMatrice() a été créée dans le fichier affAxB afin de retranscrire le
	problème linéaire Ax = b dans un ficher créé. Cette fonction est seulement utile pour 
	un my (et mx) petit, car sinon la matrice est grande et est difficile à représenter.

Question 2 (et 6):
	Comme dit ci-dessus, en plus de calculer le résidu, j’ai étudié l’évolution du résidu en 	fonction de my pour les 2 solveurs. On peut observer que AGMG est plus intéressant pour des
	petites valeurs de my.
	(environ my <= 7) tandis qu’après UMFPACK est plus intéressant.

Question 3:
	J’ai trouvé une charge Q (par unité de longueur selon z) = -7.446149e-11 C/m (pour my = 50)
 	grâce à la question 5. Le graphique du potentiel commence à avoir une bonne allure à partir
	de my = 50. 

Question 4:
	Le graphe du champ électrique est bon pour une valeur de my = 50.
	On voit sur le graphe que le champ électrique descend bien le potentiel et qu’au bord des
	bornes, le potentiel passe de 0 à +/- 0.5, le champ électrique va donc brusquement augmenter.
	Des couleurs ont été rajoutées aux graphiques afin de faciliter sa compréhension.
	Les couleurs des flèches dépendent de la norme du champ E et évoluent avec de façon non
	linéaire. Ce choix a été fait de façon à avoir un beau dégradé.

Question 5:
	Le flux de E = intégrale(E.ds) = Q/eps.
	Pour calculer cette intégrale, la méthode des trapèzes a été utilisée (méthode vu au cours
	d’analyse numérique de l’année dernière). On calcule le flux au milieu des 2 conducteurs.
	Mais lorsque my est pair, on ne peut pas calculer le flux directement car on se trouve après
	ou avant le milieu du condensateur. Il faut donc faire la moyenne du flux sur la surface avant
	et après la surface du milieu.
	Grâce à la formule du flux ci-dessus on peut facilement trouver Q. Et comme CV = Q,
	et V = u_t-u_b, on peut déterminer la capacité C. 
	Lorsque le pas de discrétisation est diminué de plus en plus, la valeur de la capacité semble
	se stabiliser. Donc pour avoir une valeur de C assez précise, il faut un pas assez petit.
	En changeant u_t et u_b, on modifie V, mais on ne modifie pas la capacité C, seul Q change.

Question 6:
	Le solveur utilisé est AGMG. On remarque grâce au graphique du résidu en fonction de my que 
	pour des petites valeurs de my, le résidu est plus petit chez AGMG. Tandis qu’après, UMFPACK 
	est plus intéressant. Par contre on remarque en comparant les temps d’exécution que le AGMG
	est bien plus rapide que UMFPACK.
	
	
