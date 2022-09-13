/** HEAD **/

#include "modele.h" //Notre bibliothèque de définition
#include <vector>   //Pour utiliser des tableaux
#include<iomanip>   //Pour utiliser setw()
#include<iostream>  //Pour afficher et entrer des valeurs
#include <time.h>   //Pour créer un seed en fonction du temps = meilleure aléatoire
#include <curses.h> //Pour utiliser les flèches directionnelles

using namespace std;
typedef vector<vector<int> > Plateau;



/**2048 **/
int score;

int main()
{
    srand (time(NULL));
    initscr(); //On initialise notre programme de sorte à ce qu'il utilise ncurses.
    keypad(stdscr, true); //Cette option permet d'autoriser la saisie du clavier sur le terminal.
    curs_set(0); //Désactive l'affichage du pointeur.
    noecho(); //Permet de désactiver l'affichage sur le terminal lorsqu'une touche est frappée.
    cbreak(); //Permet de ne pas appuyer sur Enter lorsq'une touche est frappée (pratique).
    refresh(); //Permet de rafraichir l'affichage.
    cout<<"Bienvenue sur 2048 !"<<"\r"<<endl<<"\r"<<endl; //La combinaison "\r" et endl; permet de faire un saut de ligne.
    //Ainsi que de revenir en début de ligne.
    Plateau plateau = plateauInitial();
    dessin(plateau);
    score = 0;
    
    do
    {
        cout<<"\r"<<endl<<"\r"<<endl<<"Entrez une direction :  "<<"\r"<<endl;
        int direction = getch(); //getch() permet la saisie d'un caractère.

        int entree=-1;
        while(entree==-1)
        {
        
        
            if(direction==KEY_LEFT) //KEY_LEFT (comme son nom l'indique) désigne la flèche gauche du clavier.
            {
                entree=0;
            }
            else if(direction==KEY_RIGHT) //KEY_RIGHT est pareil pour la flèche droite.
            {
                entree=1;
            }
            else if(direction==KEY_UP) //KEY_UP pareil pour la flèche du haut.
            {
                entree=2;
            }
            else if(direction==KEY_DOWN) //KEY_DOWN pour la flèche du bas.
            {
                entree=3;
            }
            else
            {
                cout<<"Erreur. Entrez une direction"<<"\r"<<endl; //En cas de mauvaise manipulation, on affiche un message d'erreur.
                direction = getch(); //On redemande de saisir une flèche directionnelle.
                cout<<"\r"<<endl;
                
            }
        }
        int save_score=score;
        bool pasBouge = (plateau==deplacement(plateau, entree));
        score=save_score;
        
        plateau=deplacement(plateau, entree);
        
        if(!pasBouge)
        {
            plateau=remplisVide(plateau);
        }
        else
        {
            if(estTermine(plateau)){cout <<"TERMINÉ !"<<endl;}
        }
        cout << "\033[2J\033[1;1H";
        //(\033[2J) permet de clear le terminal.
        //(\033[1;1H) nous repositionne à la rangée 1 et colonne 1 du terminal.
        dessin(plateau);
        cout<<"\r"<<endl<<"Score : "<<score;
    }while(!estTermine(plateau));
    endwin(); //Permet de quitter le mode terminal ncurses pour repasser à l'ancien terminal.
    return 0;
    
    
    
}

/** Fonctions **/

Plateau plateauVide()
{
    Plateau vide = {{0,0,0,0},
                   {0,0,0,0},
                   {0,0,0,0},
                   {0,0,0,0}};
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
                score+=v*2;
                plateau[i][indice]=v*2; 
                plateau[i][indice_suivant]=0;
                
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
                score+=v*2;
                plateau[i][indice]=v*2; 
                plateau[i][indice_suivant]=0;
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
                score+=v*2;
                plateau[indice][i]=v*2; 
                plateau[indice_suivant][i]=0;
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
                score+=v*2;
                plateau[indice][i]=v*2; 
                plateau[indice_suivant][i]=0;
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
    cout<<"#############################"<<"\r"<<endl;
    for(vector<int> ligne: plateau)
    {
        cout<<"# ";
        for(int colonne:ligne)
        {
            cout<< setw(4) <<colonne<<" # ";
        }
        cout<<"\r"<<endl;
        cout<<"#############################"<<"\r"<<endl;
    }
    
}

bool estTermine(Plateau plateau){
    
    int save_score=score;
    for(int i=0; i<4; i++)
    {
        if(deplacement(plateau,i)!=plateau){score=save_score; return false;}
        
    }
    return true;
}

bool estGagnant(Plateau plateau)
{
    for(vector<int> ligne: plateau)
    {
        for(int elt:ligne)
        {
            if(elt==2048) return false;
        }
    }
    return true;
}