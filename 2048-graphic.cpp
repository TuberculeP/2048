#include "modele.h" //Notre bibliothèque de définition
#include <vector>   //Pour utiliser des tableaux
#include<iomanip>   //Pour utiliser setw()
#include<iostream>  //Pour afficher et entrer des valeurs
#include <time.h>   //Pour créer un seed en fonction du temps = meilleure aléatoire
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;
typedef vector<vector<int> > Plateau;

int main()
{

    srand (time(NULL));
    RenderWindow window( VideoMode(1000.0f, 1000.0f), "Projet 2048", Style::Titlebar | Style::Close); //Cree une fenetre de 1000 pixels par 1000 pixels, intitulé "Projet 2048", en affichant la barre du titre et le bouton fermeture

    RectangleShape base(Vector2f(800.0f, 800.0f)); //Forme un rectangle de 800 pixels par 800 (un carré donc)
    Font font;
    font.loadFromFile("Times New Romance.ttf"); //Permet de charger un fichier contenant une police d'écriture
    Plateau plateau = plateauInitial();
    int score = 0;
    

    Music music;
    if(!music.openFromFile("2048_1.wav"))
        return -1;
    
    music.setLoop(true);
    music.play();

    bool sonVictoireJoue=false;
    SoundBuffer buffer;
    SoundBuffer buffer2;
    SoundBuffer buffer3;

    buffer.loadFromFile("victory.ogg");
    Sound victoire;
    victoire.setBuffer(buffer);

    buffer2.loadFromFile("beep.ogg");
    Sound beep;
    beep.setBuffer(buffer2);
    beep.setVolume(30);

    buffer3.loadFromFile("end.ogg");
    Sound end;
    end.setBuffer(buffer3);

    
    while(window.isOpen()) // Tant que la fenetre est ouverte
    {
            window.clear(); //Clear la totalité de la fenêtre
            
            if(estGagnant(plateau) == true) //Si le plateau contient un 2048 donc est gagnant alors on  rempli le fond en jaune
            {
                base.setFillColor(Color::Yellow); 
            }
            else //Sinon le laisse en blanc
            {
                base.setFillColor(Color::White); //Sinon rempli le carré de la couleur blanc
            }
            base.setOrigin(-100.0f, -100.0f); //Et place son origine (le coin en haut à gauche) aux coordonnées -100, -100
            if (estTermine(plateau)) //Si le joueur perd alors on rempli le fond en rouge et on stop la musique
            {
                base.setFillColor(Color::Red);
                end.play();
                music.stop();
            }
            
            string str_score = "Score : "+to_string(score);
            Text Score(str_score, font);
            Score.setCharacterSize(50);
            Score.setOrigin(-500.0f, -900.0f);
            Score.setFillColor(Color::Green);

            window.draw(base); //Dessine le carré dans la fenêtre
            window.draw(Score); //Dessine le Score dans la fenêtre
            
            for(float i = 0; i<4; i+=1)
            {
                for(int j = 0; j<4; j++)
                {
                    int longueur = plateau[i][j];
                    string str_plateau = to_string(plateau[i][j]);
                    if(str_plateau=="0"){str_plateau=" ";} //Si la tuile est 0 alors on la remplace par un emplacement vide

                    RectangleShape tuiles(Vector2f(150.0f, 150.0f));
                    tuiles.setOrigin(-25.0f, -750.0f);
                    tuiles.setPosition(125.0f + j*180.0f, -590.0f +i*180.0f);
                    tuiles.setFillColor(Color::Black);

                    Text affichage(str_plateau, font); 
                    affichage.setCharacterSize(50);
                    affichage.setOrigin(-25.0f, -750.0f);
                    affichage.setFillColor(Color::White);

                    //Plus la longueur du nombre est grande, plus on centre le nombre
                    if( longueur < 10)
                    {
                        affichage.setPosition(190.0f + j*180.0f, -540.0f +i*180.0f);
                    }
                    else if( longueur > 10 and longueur < 100)
                    {
                        affichage.setPosition(178.0f + j*180.0f, -540.0f +i*180.0f);
                    }
                    else if( longueur > 100 and longueur < 1000)
                    {
                        affichage.setPosition(166.0f + j*180.0f, -540.0f +i*180.0f);
                    }
                    else if( longueur > 1000 and longueur < 10000)
                    {
                        affichage.setPosition(154.0f + j*180.0f, -540.0f +i*180.0f);
                    }
                    else if( longueur > 10000 and longueur < 100000)
                    {
                        affichage.setPosition(142.0f + j*180.0f, -540.0f +i*180.0f);
                    }
                    else if( longueur > 100000)
                    {
                        affichage.setPosition(130.0f + j*180.0f, -540.0f +i*180.0f);
                    }
                    
                    window.draw(tuiles);
                    window.draw(affichage);
                }
            }
            

            if(estGagnant(plateau)) //Si le plateau contient un 2048 donc est gagnant alors on affiche un message de victoire et on change la musique
            {
                Text gagne("Victoire ! Vous avez atteint 2048 !", font);
                gagne.setCharacterSize(30);
                gagne.setOrigin(-100.0f, -50.0f);
                gagne.setFillColor(Color::Red);
                window.draw(gagne);

                if(!sonVictoireJoue){ victoire.play(); sonVictoireJoue=true; } 
            }



            window.display();
            

            Event event;
            int entree = -1;
            while(window.waitEvent(event)) //On attend qu'un évènement se produise
            {
                if(event.type==Event::KeyPressed) //Si l'évènement effectué est une touche du clavier alors on fait un déplacement du plateau en fonction de la touche
                {
                    switch(event.key.code)
                    {
                        case Keyboard::Q:

                            entree = 0;
                            break;

                        case Keyboard::D:

                            entree = 1;
                            break;
                        
                        case Keyboard::Z:

                            entree = 2;
                            break;
                        
                        case Keyboard::S:

                            entree = 3;
                            break;
                    }
                    break;
                }
                if(event.type==Event::Closed){ //Si l'évènement est la fermeture de la fenêtre alors on la ferme
                    window.close(); 
                    entree = 4;
                    break;}
            }

            if(entree>-1 and entree<4) //Si l'évènement est bien une touche du clavier alors on met à jour le score
            {   
                int score_deplacement = plateau[4][0];
                plateau[4][0]=0;
                bool pasBouge = (plateau==deplacement(plateau, entree)); //Si le déplacement ne change pas les positions alors aucun score ne sera gagné    
                plateau=deplacement(plateau, entree);
                


                if(!pasBouge) //Si le plateau est différent de sa position précédente alors on remplit une tuile d'un tableau et on met à jour le score
                {
                    plateau=remplisVide(plateau);
                    score += plateau[4][0];
                    beep.play();
                }
            }
            if(entree==4) //Si on a fermé la fenêtre
            {
                break;
            }

    }
    std::cout<<"À bientôt ! "<<endl;
    
    return 0;
    
    
}