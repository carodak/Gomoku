#include "Pions.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
//Constructeurs
Pions::Pions() : nb_pions(60) {}

Pions::Pions(Couleur coul) : nb_pions(60), couleur_pion(coul) {}

//Accesseur en lecteur
Pions::Couleur Pions::getCouleur() const {return couleur_pion;}

//Accesseur en écriture
void Pions::setCouleur(Couleur coul){couleur_pion=coul;}


void Pions::pion_blanc(){
    sf::Texture pionB;
    sf::Sprite sprite;

    if(!pionB.loadFromFile("blanc.png")){}
        sprite.setTexture(pionB);
    }

void Pions::pion_noir(){
    sf::Texture pionN;
    sf::Sprite sprite;

    if(!pionN.loadFromFile("noir.png")){}
        sprite.setTexture(pionN);
    }

