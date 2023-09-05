#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tableauPotentiel.h"
#include "tableauChampElec.h"

int champE(double *x, double h, int mx, int my, double *tableauChEx, double*tableauChEy, double *tableauPot, double bornes[4])
/*
 
 But
 ===
 Calculer le champ électrique E en fonction du potentiel.
 
 E = -(du/dx, du/dy)
 
 On va calculer ses composantes de 3 manières différentes afin d'être le plus précis possible :
 
 1. Avec la différence progressive (lorsqu'on est sur un bord sud ou ouest):
    dy      y(x+h) - y(x)
    --(x) = -------------
    dx            h
 2. Avec la différence regressive (lorsqu'on est sur un bord nord ou est):
     dy      y(x) - y(x-h)
     --(x) = -------------
     dx            h
 3. Avec la différence centrée (lorsqu'on est dans le centre du condensteur):
     dy      y(x+h) - y(x-h)
     --(x) = -------------
     dx            2h
 
 On rassemble le tout dans un tableau double afin de simplifier son utilisation.
 
 Arguments
 =========
 x  (input) - le vecteur solution
 h  (input) - le pas de discrétisation
 mx (input) - nombre de points dans la direction 1x sur la grille
 my (input) - nombre de points dans la direction 1y sur la grille
 chE[][2] (input) - tableau double composé des componsantes du champ E : [Ex, Ey]
 tableauPot (input) - tableau composé des différentes valeurs du potentiel en fonction de la position dans le condensateur
 bornes (input) - les bornes entre lesquelles est défini le condensateur
 
 */
{
    
    /* DECLARATION DE VARIABLES */
    
    
    int i, j, k = 0, n;
    n = mx*my;
    
    
    /* CREATION TABLEAU DU CHAMP ELECTRIQUE */
    
    
    printf("\n|CREATION CHAMPELEC|\n");

    
    for(j=0;j<my;j++){
        for(i=0;i<mx;i++)
        {
            //Colonne
            if(j==0){
                tableauChEy[k]=-(tableauPot[k+mx]-tableauPot[k])/h;
            }
            else if(j==my-1){
                tableauChEy[k]=-(tableauPot[k]-tableauPot[k-mx])/h;
            }
            else{
                tableauChEy[k] = -(tableauPot[k+mx]-tableauPot[k-mx])/(2*h);

            }
            //Ligne
            if(i==0){
                tableauChEx[k] =-(tableauPot[k+1]-tableauPot[k])/h;
            }
            else if(i==mx-1){
                tableauChEx[k] =-(tableauPot[k]-tableauPot[k-1])/h;
            }
            else{
                tableauChEx[k] = -(tableauPot[k+1]-tableauPot[k-1])/(2*h);
            }
            k++;
        }
    }
    
    //Libération de la mémoire
    free(tableauPot);
    
    return 0;
}
