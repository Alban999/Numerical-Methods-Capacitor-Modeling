#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "affChE.h"

int plotChE(double *x, int mx, int my, double h, double *tableauChEx, double*tableauChEy, char *nameFile)
/*
 
 But
 ===
 Afficher le graphique du champ électrique au sein du condensateur.
 
 Arguments
 =========
 x  (input) - le vecteur solution
 mx (input) - nombre de points dans la direction 1x sur la grille
 my (input) - nombre de points dans la direction 1y sur la grille
 h  (input) - le pas de discrétisation
 tableauChE[][2] (input) - tableau double composé des componsantes du champ E : [Ex, Ey]
 nameFile (input) - nom du fichier contenant les données
 
 */
{
    /* DECLARATION DE VARIABLES */
    
    
    int i, j, o = 0;
    
    /* CREATION DE LA FONCTION */
    
    
    printf("\n|CREATION DE LA FONCTION DU CHAMP E|\n");

    //Création du fichier de données
    FILE *data1 = fopen(nameFile, "w");
    for (i = 0; i<my; i++)
        for(j = 0; j<mx; j++)
        {
            fprintf(data1, "%f %f %f %f\n", h*j, h*i, tableauChEx[o], tableauChEy[o]);
            o++;
        }
    
    fclose(data1);

    //Créer fichier commande
    FILE *cmd1;
    cmd1 = popen("gnuplot -persistent", "w");
    
    fprintf(cmd1, "load 'fonctionChampE.txt'\n");
    fprintf(cmd1, "set xrange[%d:%f]\n", 0, (mx-1)*h*1000);
    fprintf(cmd1, "set yrange[%d:%f]\n", 0, (my-1)*h*1000);
    fprintf(cmd1, "plot '%s' every 14:7 using (c*$1):(c*$2):(n*($3)):(n*($4)):((($3*$3)+($4*$4))**0.5) with vectors head size 0.1,20,60 filled palette\npause -1\n", nameFile);
    
    //Vérification de la création des fichiers
    if (cmd1 == NULL || data1 == NULL)
    {
        printf("Erreur d'ouverture de fichier pour la création de la fonction du champ E.\n");
        return 1;
    }
    
    pclose(cmd1);

    return 0;
}


