#include "Curseur.h"
#include <unistd.h>
#include <iostream>
#define ATTENDRE(temps) usleep(temps)

using namespace sf;
using namespace std;
Curseur::Curseur(sf::Event &event) : position_souris_x(event.mouseButton.x), position_souris_y(event.mouseButton.y) {}

float Curseur::getX()const {return position_souris_x;}

float Curseur::getY()const {return position_souris_y;}

void Curseur::setX(sf::Event event){position_souris_x = event.mouseButton.x;}

void Curseur::setY(sf::Event event){position_souris_y = event.mouseButton.y;}

void Curseur::restriction(Pions &p,sf::RenderWindow& window,Cellule& A) {

    sf::Sprite sprite;


    sf::Texture pionN;

    if(!pionN.loadFromFile("noir.png")){}

    sprite.setPosition(A.getX(),A.getY());
    sprite.setTexture(pionN);
    window.draw(sprite);
    A.set_pion_present_noir(true);
    playsound(1);

}


void Curseur::Pion_cree_apres_click(Pions &p, sf::Event event, sf::RenderWindow &window, Cellule& A,int &nbtours,bool &poser_pion_b, bool &poser_pion_n){
/*
contains permet de tester si un point (ici la souris) est contenu dans le sprite
*/



sf::Sprite sprite;

    sf::Texture pionB;

    if(!pionB.loadFromFile("blanc.png")){}

        if (A.get_entity().contains(getX(), getY()) && nbtours%2==0 && A.Contient_pion_noir()== false && A.Contient_pion_blanc()== false){
        setX(event); setY(event);
        sprite.setPosition(A.getX(),A.getY());
        cout<<A.getX()<<" "<<A.getY()<<endl;
        sprite.setTexture(pionB);
        window.draw(sprite);
        A.set_pion_present_blanc(true);
        playsound(nbtours);
        nbtours++;
        A.lumineux_rectangle(window,sprite);
        poser_pion_b=true;
        }

else {
    sf::Texture pionN;

    if(!pionN.loadFromFile("noir.png")){}

    if (A.get_entity().contains(getX(), getY()) && A.Contient_pion_noir()== false && A.Contient_pion_blanc()== false){
        setX(event); setY(event);
        sprite.setPosition(A.getX(),A.getY());
        sprite.setTexture(pionN);
        window.draw(sprite);
        A.set_pion_present_noir(true);
        playsound(nbtours);
        nbtours++;
        A.lumineux_rectangle(window,sprite);
        poser_pion_n=true;
        }
    }
}


void Curseur::playsound(int k){

if (k%2){

Music one;
one.openFromFile("b2.flac");

one.play();
ATTENDRE((double)25000);
return;
}


Music deux;
deux.openFromFile("b1.flac");

deux.play();
ATTENDRE((double)25000);

}


