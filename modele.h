#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;


typedef vector<vector<int> > Plateau;
/** Des fonctions peuvent être ajoutés à ce fichier si besoin est (fonctions pour mettre à jour le score par exemple)
**/

/** génère un Plateau de dimensions 4*4 ne contenant que des 0
 *  @return un Plateau vide
 *  50% Félix, 50% Bryan
 *  Testé sur JupyterHub par Félix et Bryan
 **/
Plateau plateauVide();


/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 *  50% Félix, 50% Bryan
 *  Testé sur JupyterHub par Félix
 **/
int tireDeuxOuQuatre();

/** génère deux nombres sur des cases aléatoires d'un Plateau vide
 *  @return un Plateau en début de jeu
 *  50% Félix, 50% Bryan
 *  Testé sur JupyterHub par Félix
 **/
Plateau plateauInitial();

/** remplis le vide d'un tableau avec un 2 ou un 4
 * @param plateau le Plateau
 * @return plateau le Plateau une fois remplis
 * 100% Félix
 * Testé sur JupyterHub par Félix
**/
Plateau remplisVide(Plateau plateau);

/** déplace les tuiles d'un Plateau vers la gauche et les combine si possible
 * @param plateau le Plateau
 * @return le Plateau une fois déplacé vers la gauche
 * 75% Félix, 25% Bryan
 * Testé sur JupyterHub par Félix ( mais bug improbable sur MacOS )
 **/
Plateau deplacementGauche(Plateau plateau);

/** déplace les tuiles d'un Plateau vers la droite et les combine si possible
 * @param plateau le Plateau
 * @return le Plateau une fois déplacé vers la droite
 * 50% Félix, 50% Bryan
 * Testé sur JupyterHub par Félix ( mais bugs improbables sur MacOS )
 **/
Plateau deplacementDroite(Plateau plateau);

/** déplace les tuiles d'un Plateau vers le haut et les combine si possible
 * @param plateau le Plateau
 * @return le Plateau une fois déplacé vers le haut
 * 50% Félix, 50% Bryan
 * Testé sur JupyterHub par Félix ( mais bugs improbables sur MacOS )
 **/
Plateau deplacementHaut(Plateau plateau);

/** déplace les tuiles d'un Plateau vers le bas et les combine si possible
 * @param plateau le Plateau
 * @return le Plateau une fois déplacé vers le bas
 * 50% Félix, 50% Bryan
 * Testé sur JupyterHub par Félix ( mais bugs improbables sur MacOS )
 **/
Plateau deplacementBas(Plateau plateau);

/** déplace les tuiles d'un Plateau dans la direction donnée et génère une nouvelle tuile si le déplacement est valide
 * @param plateau le Plateau
 * @param direction la direction
 * @return le Plateau déplacé dans la direction
 * 100% M.Thiéry, elle était donné :)
 * Testé sur JupyterHub par Félix 
 **/
Plateau deplacement(Plateau plateau, int direction);

/** affiche un Plateau
 * @param p le Plateau
 * 50% Félix, 50% Bryan
 * Testé sur JupyterHub par Félix 
 **/
void dessin(Plateau plateau);

/** permet de savoir si une partie est terminée
 * @param plateau un Plateau
 * @return true si le plateau est plein, false sinon
 * 50% Félix, 50% Bryan
 * Testé sur JupyterHub par Félix 
 **/
bool estTermine(Plateau plateau);

/** permet de savoir si une partie est gagnée
 * @param plateau un Plateau
 * @return true si le plateau contient un 2048, false sinon
 * 50% Félix, 50% Bryan
 * Testé sur JupyterHub par Félix 
 **/
bool estGagnant(Plateau plateau);