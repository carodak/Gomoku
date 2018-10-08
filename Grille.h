#ifndef GRILLE_H
#define GRILLE_H
#define NMAX 15
#include <SFML/Graphics.hpp>
#include "Cellule.h"
#include "Pions.h"
#include "Curseur.h"
#include "Joueur.h"
#include <string>

class Grille {

private :
Cellule Gri[NMAX][NMAX];

public :
Grille();
Cellule& getCellule(int i, int j); //retourne la Cellule de la grille se trouvant à la coordonnée i,j
void printGrille(sf::RenderWindow &window);
void verif_click(Curseur &B, Pions &p, sf::Event event, sf::RenderWindow &window, Joueur&, Joueur&);
int qui_commence(Joueur&, Joueur&);
int gagnant();
int* nb_series(int n);
void printVictoire(Joueur&, Joueur&);
void choix (Joueur &,Joueur &);
};

#endif
