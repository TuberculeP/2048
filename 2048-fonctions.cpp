#include "modele.h"
#include <vector>
#include <iomanip>
#include <iostream>
#include <stdexcept>
/** 
 * Ce fichier sert au stockage des fonctions core du 2048 qui fonctionnent à la fois pour la version Terminal et la version SFML 
 * On se concentre ici sur le code
 * Pour une documentation précise des fonctions, se référer au fichier modele.h
**/

Plateau plateauVide()
{ 
    Plateau vide = {
                    {0,0,0,0},
                    {0,0,0,0},
                    {0,0,0,0},
                    {0,0,0,0},
                    {0}
                   };
    return vide;
}

int tireDeuxOuQuatre()
{
    if(rand()%10<9){ return 2; }else{ return 4; }
}

Plateau plateauInitial()
{
    Plateau plateau = plateauVide();
    for(int i=0; i<2; i++)
    {
        int ligne = rand()%4;
        int colonne = rand()%4;
        if (plateau[ligne][colonne]==0)
        {
            int value = tireDeuxOuQuatre();
            plateau[ligne][colonne]=value;
        } else { i--; }
    }
    return plateau;
}

Plateau remplisVide(Plateau plateau)
{
    while(true)
    {
        int ligne=rand()%4;int colonne=rand()%4;
        if(plateau[ligne][colonne]==0)
        {
            plateau[ligne][colonne]=tireDeuxOuQuatre();
            return plateau;
        }
    }
}

Plateau deplacementGauche(Plateau plateau)
{
               
    plateau[4][0] = 0; //initialisation du score gagné durant ce déplacement

    //Pour chaque ligne de la matrice
    for(int i=0; i<4;i++)
    {
        //Pour chaque élément de la ligne
        for(int indice=0; indice<3; indice++)
        {

            //On sauvegarde la valeur
            int v=plateau[i][indice];
            
            //On va chercher le prochain élément !=0 dans la ligne
            int indice_suivant=indice+1;
            while(plateau[i][indice_suivant]==0 and indice_suivant<4) indice_suivant++;
            
            //Si ces éléments sont égaux on assigne v*2 à l'emplacement du premier élément
            //et on supprime l'autre dans la ligne
            if(plateau[i][indice_suivant]==v and v!=0)
            { 

                plateau[i][indice]=v*2; 
                plateau[i][indice_suivant]=0;

                plateau[4][0] += v*2; //ajout de points
                
            }
            else
            { 
                //Si l'élément de base est un zéro, on va simplement replacer (la valeur glisse)
                if(indice_suivant<4 and v==0 and plateau[i][indice_suivant]!=0)
                {
                    plateau[i][indice]=plateau[i][indice_suivant]; 
                    plateau[i][indice_suivant]=0;
                    
                    indice--;
                    
                } 
            }
        }
    }
    return plateau;
}

Plateau deplacementDroite(Plateau plateau)
{

    plateau[4][0] = 0; //initialisation du score gagné durant ce déplacement


    //Pour chaque ligne de la matrice
    for(int i=0; i<4;i++)
    {
        //Pour chaque élément de la ligne
        for(int indice=3; indice>0; indice--)
        {            

            //On sauvegarde la valeur
            int v=plateau[i][indice];
            
            //On va chercher le prochain élément !=0 dans la ligne
            int indice_suivant=indice-1;
            while(plateau[i][indice_suivant]==0 and indice_suivant>=0) indice_suivant--;
            
            //Si ces éléments sont égaux on assigne v*2 à l'emplacement du premier élément
            //et on supprime l'autre dans la ligne
            if(plateau[i][indice_suivant]==v and v!=0 and plateau[i][indice_suivant]!=0)
            { 
                plateau[i][indice]=v*2; 
                plateau[i][indice_suivant]=0;
                
                plateau[4][0] += v*2; // ajout de points
            }
            else
            { 
                //Si l'élément de base est un zéro, on va simplement replacer (la valeur glisse)
                if(indice_suivant>=0 and v==0)
                {
                    plateau[i][indice]=plateau[i][indice_suivant]; 
                    plateau[i][indice_suivant]=0;
                    indice++;
                    
                } 
            }
        }
    }
    return plateau;
}

Plateau deplacementHaut(Plateau plateau)
{

    plateau[4][0] = 0; //initialisation du score gagné durant ce déplacement


    //Pour chaque colonne de la matrice
    for(int i=0; i<4;i++)
    {
        //Pour chaque élément de la ligne
        for(int indice=0; indice<3; indice++)
        {
            //On sauvegarde la valeur
            int v=plateau[indice][i];
            
            //On va chercher le prochain élément !=0 dans la colonne
            int indice_suivant=indice+1;
            while(plateau[indice_suivant][i]==0 and indice_suivant<3){ indice_suivant++;}
            
            //Si ces éléments sont égaux on assigne v*2 à l'emplacement du premier élément
            //et on supprime l'autre dans la colonne
            if(plateau[indice_suivant][i]==v and v!=0)
            {
                plateau[indice][i]=v*2; 
                plateau[indice_suivant][i]=0;

                plateau[4][0] += v*2; //ajout de points
            }
            else
            { 
                //Si l'élément de base est un zéro, on va simplement replacer (la valeur glisse)
                if(indice_suivant<4 and v==0 and plateau[indice_suivant][i]!=0)
                {
                    plateau[indice][i]=plateau[indice_suivant][i]; 
                    plateau[indice_suivant][i]=0;
                    indice--;
                    
                } 
            }
        }
    }
    return plateau;
}

Plateau deplacementBas(Plateau plateau)
{

    plateau[4][0] = 0; //initialisation du score gagné durant ce déplacement


    //Pour chaque colonne de la matrice
    for(int i=0; i<4;i++)
    {
        //Pour chaque élément de la ligne
        for(int indice=3; indice>0; indice--)
        {

            //On sauvegarde la valeur
            int v=plateau[indice][i];
            
            //On va chercher le prochain élément !=0 dans la colonne
            int indice_suivant=indice-1;
            while(plateau[indice_suivant][i]==0 and indice_suivant>0){ indice_suivant--;}
            
            //Si ces éléments sont égaux on assigne v*2 à l'emplacement du premier élément
            //et on supprime l'autre dans la colonne
            if(plateau[indice_suivant][i]==v and v!=0)
            {
                plateau[indice][i]=v*2; 
                plateau[indice_suivant][i]=0;

                plateau[4][0] += v*2; //ajout de points
            }
            else
            { 
                //Si l'élément de base est un zéro, on va simplement replacer (la valeur glisse)
                if(indice_suivant>=0 and v==0 and plateau[indice_suivant][i]!=0)
                {
                    plateau[indice][i]=plateau[indice_suivant][i]; 
                    plateau[indice_suivant][i]=0;
                    indice++;
                    
                } 
            }
        }
    }
    return plateau;
}

Plateau deplacement(Plateau plateau, int direction)
{
  switch ( direction ) {
    case 0:
      return deplacementGauche(plateau);
    case 1:

      return deplacementDroite(plateau);
    case 2:

      return deplacementHaut(plateau);
    case 3:

      return deplacementBas(plateau);
    default:
      cerr << "Deplacement non-autorise!" << endl;
      exit(-1);
  }
}

void dessin(Plateau plateau)
{
    cout<<"#############################"<<endl;
    for(int i=0; i<4; i++)
    {
        cout<<"# ";
        for(int j=0; j<4; j++)
        {
            if(plateau[i][j]==0){
                cout<< setw(4)<<" "<<" # ";
            }else{
                cout<< setw(4) <<plateau[i][j]<<" # ";
            }
        }
        cout<<endl;
        cout<<"#############################"<<endl;
    }
    
}

bool estTermine(Plateau plateau){
    
    for(int i=0; i<4; i++)
    {
        if(deplacement(plateau,i)!=plateau) return false;
        
    }
    return true;
}

bool estGagnant(Plateau plateau)
{
    for(vector<int> ligne: plateau)
    {
        for(int elt:ligne)
        {
            if(elt>=2048) return true;
        }
    }
    return false;
}
