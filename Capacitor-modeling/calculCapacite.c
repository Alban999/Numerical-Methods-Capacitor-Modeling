#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calculCapacite.h"

double capa(double flux, double eps, int mx, int my, double uB, double uT)
/*
 
 But
 ===
 Calculer la capacité de notre condensateur.
 
 Arguments
 =========
 flux (input) - flux reçu au centre du condensateur
 eps (input) - valeur de epsilon (la permittivité)
 mx (input) - nombre de points dans la direction 1x sur la grille
 my (input) - nombre de points dans la direction 1y sur la grille
 uB (input) - Potentiel sur le bord du bas du condensateur compris entre les bornes données
 uT (input) - Potentiel sur le bord du haut du condensateur compris entre les bornes données

 */
{
    /* DECLARATION DE VARIABLES */
    
    
    double tension = fabs(uT-uB);
    
    /* CALCUL DE LA CAPACITE */
    
    
    printf("\n|CALCUL DE LA CAPACITE|\n");
    
    printf("\nflux au centre: %e, eps : %e, tension : %e\n", flux, eps, tension);
    
    /*
     
     REPONSE:
     - Meilleurs estimation de C ? -> en diminuant le pas de discrétisation
     - Si on change  ut = −ub, C change car  = C = flux*eps/(ut-ub)
     
     */
    
    return fabs(flux*eps/tension);
}
