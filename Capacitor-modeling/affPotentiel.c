#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "affPotentiel.h"

int plot(double *x, int mx, int my, double h, double *tableauPotentiel, char *nameFile)
/*
 
 But
 ===
 Afficher le graphique du potentiel au sein du condensateur.
 
 Arguments
 =========
 x  (input) - le vecteur solution
 mx (input) - nombre de points dans la direction 1x sur la grille
 my (input) - nombre de points dans la direction 1y sur la grille
 h  (input) - le pas de discrétisation
 tableauPotentiel (input) - tableau composé des différentes valeurs du potentiel en fonction de la position dans le condensateur
 nameFile (input) - nom du fichier contenant les données
 
 */
{
    /* DECLARATION VARIABLES */
    
    int i, j, o = 0;
    FILE *data;
    
    /* CREATION DE LA FONCTION */
    
    
    printf("\n|CREATION DE LA FONCTION DU POTENTIEL U|\n");
    
    //Création du fichier de données
    data = fopen(nameFile, "w");
    for (i = 0; i<my; i++)
        for (j = 0; j<mx; j++)
        {
            fprintf(data, "%f %f %f\n", j*h, i*h, tableauPotentiel[o]);
            o++;
        }
    
    fclose(data);
    
    //Création du fichier de commandes
    FILE *cmd;
    cmd = popen("gnuplot -persistent", "w");
    
    fprintf(cmd, "load 'fonctionPotentiel.txt'\n");
    
    fprintf(cmd, "set xrange[%d:%f]\n", 0, (mx-1)*h);
    fprintf(cmd, "set yrange[%d:%f]\n", 0, (my-1)*h);
    fprintf(cmd, "plot '%s' using 1:2:3 with points pointsize 1 pointtype 5 palette\npause -1\n", nameFile);
    
    //Vérification de la création des fichiers
    if (cmd == NULL || data == NULL)
    {
        printf("Erreur d'ouverture de fichier pour la création de la fonction de potentiel.\n");
        return 1;
    }
    pclose(cmd);
    
    return 0;
}

