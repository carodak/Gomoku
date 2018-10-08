#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include "Cellule.h"

using namespace sf;
using namespace std;





/*Constructeur par défaut , on à choisi de ne pas utiliser de constructeur paramétré , c'est le tableau de Cellule qui s'occupera de ça .
Peu importe la coordonnée d'une seule seule, le tableau de cellules modifiera les coordonnées des cellules dans le constructeur
*/

Cellule::Cellule()
{
//taille du rectangle représentant la cellule de 35 par défaut
    rectangle.setSize(sf::Vector2f(35, 35));
    x=0;
    y=0;
    pion_present_noir=false;
    pion_present_blanc=false;
    rectangle.setFillColor(Color::White);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));

}


void Cellule::Print_cellule(sf::RenderWindow &window)
{
//Les coordonées du rectangle sont celles de la cellule
    rectangle.setPosition(getX(),getY());
    window.draw(rectangle);
} //Ce fera avec sfml , test en cours ...

//Accesseur en intérrogation

bool Cellule::Contient_pion_noir () const
{

    return Cellule::pion_present_noir;

}

bool Cellule::Contient_pion_blanc () const
{

    return Cellule::pion_present_blanc;

}

//Accesseur en lecture sur X
float Cellule::getX() const
{
    //return rectangle.getPosition().x;
    return x;
}



//Accesseur en lecture sur Y
float Cellule::getY() const
{
    // return rectangle.getPosition().y;
    return y;
}

//A MODIFIER A METTRE EN FIXE AU MILIEU DU JEU
//Accesseur en ecriture sur X
void Cellule::setX(float x)
{
    this->x=x;
}


//Accesseur en ecriture sur Y
void Cellule::setY(float y)
{
    this->y=y;
}


void Cellule::set_pion_present_noir(bool a)
{
    pion_present_noir=a;
}

void Cellule::set_pion_present_blanc(bool a)
{
    pion_present_blanc=a;
}

void Cellule::set_rectangle(float i, float j)
{
//rectangle.setPosition(372, 270);
    rectangle.setPosition(i,j);
}


void Cellule::rectangle_transparent(sf::RenderWindow &window, sf::Sprite &sprite){
//On met la couleur du rectangle en transparent
rectangle.setFillColor(sf::Color(255, 255, 255, 255));
window.draw(rectangle);
window.draw(sprite);
}


void Cellule::lumineux_rectangle(sf::RenderWindow &window, sf::Sprite &sprite){
    rectangle.setFillColor(sf::Color(251, 161, 8));
    window.draw(rectangle);
    window.draw(sprite);
}

sf::FloatRect Cellule::get_entity()
{
// sf::Sprite::getGlobalBounds() : retourne la position et la dimension du sprite
    return rectangle.getGlobalBounds();
}

