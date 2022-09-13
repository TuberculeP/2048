/** HEAD **/

#include "modele.h" //notre bibliothèque de définition
#include <vector>   //pour utiliser des tableaux
#include<iomanip>   //pour utiliser setw()
#include<iostream>  //pour afficher et entrer des valeurs
#include <time.h>   //pour créer un seed en fonction du temps = meilleure aléatoire

using namespace std;
typedef vector<vector<int> > Plateau;

int main()
{

    srand (time(NULL));
    cout<<"Bienvenue sur 2048 !"<<endl<<endl;
    
    Plateau plateau = plateauInitial();
    dessin(plateau);
    int score = 0;
    
    while(true)
    {
        
        cout<<endl<<endl<<"Entrez une direction :  ";
        string direction;
        cin>>direction;
        cout<<endl;
        
        int entree = -1;
        while(entree==-1)
        {
        
        
            if(direction=="q" or direction=="g" or direction=="gauche")
            {
                entree=0;
            }
            else if(direction=="d" or direction=="droite")
            {
                entree=1;

            }
            else if(direction=="z" or direction=="h" or direction=="haut")
            {
                entree=2;

            }
            else if(direction=="s" or direction=="b" or direction=="bas")
            {
                entree=3;

            }
            else
            {
                cout<<"Erreur."<<endl;
                cout<<endl<<endl<<"Entrez une direction :  ";
                cin>>direction;
                cout<<endl;
                
            }
        }

        int score_deplacement = plateau[4][0];
        plateau[4][0]=0;

        bool pasBouge = (plateau==deplacement(plateau, entree)); //Si le déplacement ne change pas les positions alors aucun score ne sera gagné
        
        plateau=deplacement(plateau, entree);
        
        if(!pasBouge)
        {
            plateau=remplisVide(plateau);
            score += plateau[4][0];
        }
        else
        {
            if(estTermine(plateau)){
                break;
            }
        }
        cout<<"\033[2J\033[1;1H";
        //(\033[2J) permet de clear le terminal.
        //(\033[1;1H) nous repositionne à la rangée 1 et colonne 1 du terminal.
        dessin(plateau);
        if(estGagnant(plateau)) cout<<"Victoire !  Tu as fait apparaitre un 2048 ! Tu peux continuer à jouer pour augmenter ton score :)"<<endl;
        cout<<"Score : "<<score<<endl;
    }
    cout<<"Terminé !"<<endl;
    if(!estGagnant(plateau)) cout<<"Défaite :(";
    
    return 0;
    
    
}