#ifndef IA_H
#define IA_H
#include <SFML/Graphics.hpp>
#include "Grille.h"
using namespace std;
using namespace sf;
//#include "Pions.h"

class Ia{

public :
void draw_pion_blanc(sf::RenderWindow& window, Cellule &A);
void draw_pion_noir(sf::RenderWindow& window, Cellule &A);
void IA_jouer(int profondeur,sf::RenderWindow& window, Grille&, Joueur &J1);
int Min(int profondeur,sf::RenderWindow& window, int alpha, int beta, Grille&);
int Max(int profondeur,sf::RenderWindow &window, int alpha, int beta, Grille&);
int diagonale(Grille &A);
int eval(Grille&);
void jouer(Grille&, sf::RenderWindow &window,Curseur &B, Joueur &J1, Joueur &J2);
void printVictoire(Grille& G);
int Min2(int profondeur,sf::RenderWindow &window,Grille& A);
int Max2(int profondeur,sf::RenderWindow &window,Grille& A);
void IA_jouer2(int profondeur,sf::RenderWindow& window, Grille& A);
void jouer2(Grille&, sf::RenderWindow &window,Curseur &B);
};

#endif
