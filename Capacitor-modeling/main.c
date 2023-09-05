#include <stdio.h>
#include <stdlib.h>
#include "prob.h"
#include "umfpk.h"
#include "time.h"
#include "residu.h"
#include "affPotentiel.h"
#include "affChE.h"
#include "affAxB.h"
#include "tableauChampElec.h"
#include "tableauPotentiel.h"
#include "fonctIntegraleFlux.h"
#include "calculCapacite.h"
#include "agmgSolveur.h"
#include "rho.h"
#include "residuEvolution.h"

int main(int argc, char *argv[])
/*
 
 But
 ===
 Gérer l'ensemble des fonctionnalités du projet
 
 */
{
    /* DECLARER LES VARIABLES */
    
    //Dimensions du condensateur
    double Lx = 0.01, Ly = 0.004;
    int my = 50;
    double h = Ly/(my-1);
    int mx = Lx/h+1;
    
    //Type de condensateur
    double epsVal = 8.5;
    double eps0 = 8.854*1e-12;
    double eps = epsVal*eps0;
    double Q = -7.446149e-11;
    double fluxCentre, chargeDuCondensateur;
    int rhoInitialize = 1; //Si = 0 -> rho = 0 sinon rho != 0

    //Les bornes du condensateur
    double bornes[4] = {0.002, 0.008, 0.002, 0.004};
    
    //Potentiel sur les bords du condensateur
    double uB = -0.5;
    double uT = 0.5;
    
    //Format CSR
    int *ia, *ja;
    double *a, *b, *x, *xAGMG;
    
    //Les temps calculés avant et après la résolution du solveur
    double t1, t2, t1AGMG, t2AGMG;
    
    //Tableau du potentiel
    double *tableauPot;
    
    //Tableau du champ électrique
    double *tableauChEx;
    double *tableauChEy;
    
    //Autres variables
    int n;
    
    //Choix
    int choixMode = 3, choixSolveur = 2;
    
    /* MENU */
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("••••••••••••••••••••••••••••••••••••••••\n");
    printf("•   Compléments de calcul numérique    •\n");
    printf("•          Projet 2018 – 2019          •\n");
    printf("•       Modéliser un condensateur      •\n");
    printf("••••••••••••••••••••••••••••••••••••••••\n\n");
    
    if(choixMode == 3){
        //Evolution du résidu en fonction de my
        
        //Initialisation
        ia = NULL; ja = NULL; a = NULL; b = NULL; x = NULL;
        
        if(residuEnFctDeMy(100, "dataResiduEnFctDeMy.txt", Lx, Ly, ia, ja, a, b, bornes, eps, Q, uB, uT))
            return 1;
        return 0;
    }
    
    /* DISQUE CHARGE OU PAS */
    
    /* GENERER LE PROBLEME */
    
    printf("\n|GENERATION DU PROBLEME|\n");
    
    if (prob(mx, my, Lx, Ly, &n, &ia, &ja, &a, &b, h, bornes, eps, Q, rhoInitialize, &rho, uB, uT))
        return 1;
    printf("\nPROBLEM: ");
    printf("mx = %d my = %d  n = %d  nnz = %d\n", mx, my, n, ia[n]);
    
    
    /* ALLOUER LA MEMOIRE POUR LES VECTEURS DE SOLUTION */
    
    x = malloc(n * sizeof(double));
    xAGMG = malloc(n * sizeof(double));
    
    if (x == NULL || xAGMG == NULL) {
        printf("\n ERREUR : pas de mémoire pour vecteur des solutions\n\n");
        return 1;
    }
    
    /* RESOUDRE ET MESURER LE TEMPS DE SOLUTION */
    
    printf("\nCALCUL DU TEMPS DE SOLUTION\n");
    if (choixSolveur == 2 || choixSolveur == 4) {
        //Solveur AGMG
        
        //Choix paramètres AGMG
        int zero = 0, one = 1, iprint = 6, iter = 100;
        double tol = 1.e-16;//Prendre une assez petite tol pour être au moins aussi précis que le solveur UMFPACK
        
        //Calcul de la solution
        t1AGMG = mytimer();
        if (solve_AGMG(mx, my, n, a, ja, ia, b, xAGMG, zero, one, iter, tol, iprint)){
            return 1;
        }
        t2AGMG = mytimer();
        
        //Temps de résolution
        printf("\nTemps de solution AGMG (CPU): %5.1f sec\n",t2AGMG-t1AGMG);
    }
    if (choixSolveur == 1 || choixSolveur == 4){
        //Solveur UMFPACK
        
        //Calcul de la solution
        t1 = mytimer();
        if (solve_umfpack(n, ia, ja, a, b, x))
            return 1;
        t2 = mytimer();
        
        //Temps de résolution
        printf("\nTemps de solution UMFPACK (CPU): %5.1f sec\n",t2-t1);

    }
    
    /* APPELS DES FONCTIONS */
    
    //Calcul et affichage du résidu
    printf("\n|CALCUL DU RESIDU|\n");

    if (choixSolveur == 1 || choixSolveur == 4){
        printf("Le residu avec UMFPACK vaut : %.30e\n", residu(x, &a, &ia, &ja, &b, n));
    }
    if (choixSolveur == 2 || choixSolveur == 4){
        printf("Le residu avec AGMG vaut : %.30e\n", residu(xAGMG, &a, &ia, &ja, &b, n));
    }
    
    if (choixSolveur == 4){
        //Libérer la mémoire
        free(ia); free(ja); free(a); free(b); free(x); free(xAGMG);
        return 0;
    }
    else{
        if (choixSolveur == 2)
        {
            //Assignation de la solution selon le solveur
            x = xAGMG;
        }
    }
    
    //Création du tableau de potentiel + génération du graphe
    tableauPot = malloc(mx*my*sizeof(double));
    creaTableau(x, tableauPot, mx, my, bornes, h, uB, uT);
    
    if (plot(x, mx, my, h, tableauPot, "dataPotentiel.txt"))
        return 1;
    
    //Création du tableau du champ électrique + génération du graphe
    tableauChEx = malloc(mx*my*sizeof(double));
    tableauChEy = malloc(mx*my*sizeof(double));
    champE(x, h, mx, my, tableauChEx, tableauChEy, tableauPot, bornes);
    
    if (plotChE(x, mx, my, h, tableauChEx, tableauChEy, "dataChampE.txt"))
        return 1;
    
    //Affichage du flux
    if(!rhoInitialize){
        fluxCentre = fonctInt(tableauChEy, mx, my, h, Ly/(2*h));
        printf("\nFlux centre = %e\n", fluxCentre);
        chargeDuCondensateur = fluxCentre*eps;
        
        //Affichage de la capcacité
        printf("\nCapacite par unité de longueur de z = %e F/m\n", capa(fluxCentre, epsVal*eps0, mx, my, uB, uT));
        
        printf("\nLa charge de la capacité par unité de longueur de z est de l'ordre de : %e C/m\n", chargeDuCondensateur);
    }
    
    /* LIBERER LA MEMOIRE */
    
    free(ia); free(ja); free(a); free(b); free(x); free(tableauChEx); free(tableauChEy);
    
    
    return 0;
}


