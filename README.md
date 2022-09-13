# 2048
Un jeu de 2048 en C++ (version graphique optionnelle)

> Projet réalisé à l'Université Paris-Saclay dans le cadre d'un TP d'apprentissage du C++.
>
> Encadrement par <a href="https://github.com/nthiery">Nicolas Thiéry</a>

> Collaboration avec Bryan Canchy

## Compilation via `make` :

Le `makefile` est configuré comme il suit :

- `make` ou `make 2048` pour obtenir une version terminal à input texte.
- `make 2048c` pour obtenir une version terminale utilisant la librairie Ncurses (pour jouer avec les flèches du clavier ou ZQSD)
> installez-là via **homebrew** avec la commande : `brew install ncurses`
- `make 2048g` pour obtenir une version graphique jouable avec les flèches du clavier ou ZQSD
> nécessite la librairie graphique SFML (`brew install sfml`)

## Problèmes connus

Pour une raison encore inconnue, sûrement due à une différence d'indexation entre deux versions de compilateurs, des **erreurs de déplacement** peuvent apparaître sur MacOS à puce M1.

de manière aléatoire..

chepa :/
