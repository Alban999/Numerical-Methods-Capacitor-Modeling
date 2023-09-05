#include <stdio.h>
#include "affAxB.h"

int affMatrice(double *a, int *ia, int *ja, double *b, int mx, int my)
/*
 
 But
 ===
 Afficher le système d'équations du problème Ax = b.
 
 (Ce fichier est utile seulement pour des petites matrices)
 
 Arguments
 =========
 a  (input) - le tableau 'a' de la matrice A
 ia (input) - le tableau 'ia' de la matrice A
 ja (input) - le tableau 'ja' de la matrice A
 b  (input) - le tableau 'b'
 mx (input) - nombre de points dans la direction 1x sur la grille
 my (input) - nombre de points dans la direction 1y sur la grille
 
 */
{
    /* DECLARATION DES VARIABLES */
    
    
    //Dimensions de la matrice
    int nx = mx-2, ny = my-2;
    int n = nx*ny;
    int ligne[n];
    int i, j, k;
    
    
    //Création du fichier pour écrire la matrice
    FILE *fichierMatrice = fopen("MatriceDuProb.txt", "w");
    
    /* CREATION DE LA MATRICE + AFFICHAGE */
    
    
    printf("\n\n|AFFICHAGE DE MATRICE|\n\n");
    for(i=0;i<n;i++)
    {
        for(k = 0; k<n; k++)
        {
            ligne[k] = 0;
        }
        for(j=ia[i];j<ia[i+1];j++)
        {
            ligne[ja[j]] = a[j];
        }
        for(k = 0; k<n; k++)
        {
            if(ligne[k]>=0)
                fprintf(fichierMatrice, " ");
            fprintf(fichierMatrice, "%d ", ligne[k]);
        }
        
        fprintf(fichierMatrice, "\n");
    }
    
    fprintf(fichierMatrice, "\n*\n\n");
    
    for(i=1; i<n+1; i++)
    {
        fprintf(fichierMatrice, "u%d\n", i);
    }
    
    fprintf(fichierMatrice, "\n=\n\n");
    
    for (i=0; i<n; i++) {
        if(b[i]>=0)
            fprintf(fichierMatrice, " ");
        fprintf(fichierMatrice, "%f\n", b[i]);

    }
    
    fclose(fichierMatrice);

    //Vérification de la création du fichier
    if (fichierMatrice == NULL)
    {
        printf("Erreur d'ouverture de fichier lors de l'affichage de Ax = b.\n");
        return 1;
    }
    
    return 0;
    
}

