#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fonctIntegraleFlux.h"

double fonctInt(double*tableauChEy, int mx, int my, double h, int n)
/*
 
 But
 ===
 Calculer le flux du champ électrique à travers un certain plan.
 Ce flux est calculé grâce à la formule des trapèzes, qui est une
 méthode d'intégration.
 
 Intégrale de f(x) sur [a, b] est + ou - = h/2.(f1 + 2f2 + ... + 2fm-1 + fm)
 
 Attention, lorsque my est pair, le plan se trouve au milieu de 2
 points de la grille. Il faut donc faire la moyenne des flux à
 travers les surfaces se situant avant et après le plan en question.
 
 Arguments
 =========
 tableauChE[][2] (input) - tableau double composé des componsantes du champ E : [Ex, Ey]
 mx (input) - nombre de points dans la direction 1x sur la grille
 my (input) - nombre de points dans la direction 1y sur la grille
 h  (input) - le pas de discrétisation
 n (input) - y = n, équation de la surface à travers laquelle on calcule le flux
 
 */
{
    
    /* DECLARATION DE VARIABLES */

    double Int = 0, Int1 = 0, Int2 = 0;;
    int i;
    
    printf("\n|CALCUL DU FLUX|\n");

    if(my%2==0){
        for(i=1;i<mx+1;i++){
            Int1 = Int1 + (h/2)*(tableauChEy[i-1+mx*n]+tableauChEy[i+mx*n]);
            Int2 = Int2 + (h/2)*(tableauChEy[i-1+mx*(n+1)]+tableauChEy[i+mx*(n+1)]);
            Int = (Int1+Int2)/2;
            
        }
    }
    else{
        for(i=1;i<mx+1;i++){
            Int = Int + (h/2)*(tableauChEy[i-1+mx*n]+tableauChEy[i+mx*n]);
        }
    }

    
    
    return Int;
    
}
