#include <stdio.h>
#include <stdlib.h>
#include "residuEvolution.h"
#include "prob.h"
#include "residu.h"
#include "agmgSolveur.h"
#include "umfpk.h"
#include "rho.h"


int residuEnFctDeMy(int maxIter, char *nameFile, double Lx, double Ly, int *ia, int *ja, double *a, double *b, double bornes[4], double eps, double Q, double uB, double uT)
/*
 
 But
 ===
 Représenter l'évolution du résidu en fonction du pas de discrétisation.
 Ici on affiche le résidu en fonction de my. Donc plus my est grand, plus
 h est petit.
 
 Arguments
 =========
 maxIter (input) - nombre maximum d'itérations (my max)
 solveur (input) - choix du solveur
 nameFile (input) - nom du fichier contenant les données
 Lx (input) - longeur du condensateur dans la direction 1x
 Ly (input) - longeur du condensateur dans la direction 1y
 ia (output) - le tableau 'ia' de la matrice A
 ja (output) - le tableau 'ja' de la matrice A
 a  (output) - tableau 'a' de la matrice A
 b  (output) - le tableau 'b'
 x  (output) - le vecteur solution
 bornes (input) - les bornes entre lesquelles est défini le condensateur
 eps (input) - valeur de epsilon (la permittivité)
 Q  (input) - la charge du condensateur
 uB (input) - Potentiel sur le bord du bas du condensateur compris entre les bornes données
 uT (input) - Potentiel sur le bord du haut du condensateur compris entre les bornes données
 
 */
{
    
    /* DECLARATION DES VARIABLES */

    int my, myDeDepart = 3, n;
    double rho(double, double, double, double, double, int);
    double residuVarUMFPACK, residuVarAGMG;
    int initialzeRho = 0; //Rho vaut 0.0
    double *xUMFPACK, *xAGMG;
    
    //Ouverture du fichier de données
    FILE *fichierDonnees = fopen(nameFile, "w");
    for(my = myDeDepart; my<maxIter; my++){
        double h = Ly/(my-1);
        int mx = Lx/h+1;

        //Génération du problème
        if (prob(mx, my, Lx, Ly, &n, &ia, &ja, &a, &b, h, bornes, eps, Q, initialzeRho, rho, uB, uT))
            return 1;
        
        //Initialisation des solutions
        xUMFPACK = malloc(n * sizeof(double));
        xAGMG = malloc(n * sizeof(double));
        
        if (solve_umfpack(n, ia, ja, a, b, xUMFPACK))
            return 1;
        residuVarUMFPACK = residu(xUMFPACK, &a, &ia, &ja, &b, n)*1e16;
        
        //Choix paramètres AGMG
        int zero = 0, one = 1, iprint = 6, iter = 100;
        double tol = 1.e-16;
        
        if (solve_AGMG(mx, my, n, a, ja, ia, b, xAGMG, zero, one, iter, tol, iprint)){
            return 1;
        }
        residuVarAGMG = residu(xAGMG, &a, &ia, &ja, &b, n)*1e16;

        fprintf(fichierDonnees, "%d %f %f\n", my, residuVarUMFPACK, residuVarAGMG);
        
        /* LIBERER LA MEMOIRE */
        
        free(ia); free(ja); free(a); free(b); free(xUMFPACK); free(xAGMG);
    }
    
    fclose(fichierDonnees);

    //Création du fichier de commandes
    FILE *cmd;
    cmd = popen("gnuplot -persistent", "w");
    
    fprintf(cmd, "load 'fonctionResiduEnFctDeMy.txt'\n");
    fprintf(cmd, "set title \"Etude du résidu en fonction de my\"\n");
    fprintf(cmd, "set xrange[%d:%d]\n", myDeDepart, maxIter);
    fprintf(cmd, "set yrange[%f:%f]\n", 0.0, residuVarAGMG*1.5);
    fprintf(cmd, "plot 'dataResiduEnFctDeMy.txt' using 1:2 w l title 'UMFPACK', '' using 1:3 w l title 'AGMG'\npause -1\n");
    
    //Vérification de la création des fichiers
    if (cmd == NULL || fichierDonnees == NULL)
    {
        printf("Erreur d'ouverture de fichier pour la création de la fonction du résidu en fonction du pas de discrétisation.\n");
        return 1;
    }
    pclose(cmd);
    

    return 0;
}
