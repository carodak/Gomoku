#ifndef CELLULE_H
#define CELLULE_H
#include <SFML/Graphics.hpp>


class Cellule {


private :


unsigned int x;
unsigned int y;
bool pion_present_noir;
bool pion_present_blanc;
//On crée un rectangle représentant la cellule
sf::RectangleShape rectangle;


public :


Cellule();  //Constructeur par défaut
void Print_cellule(sf::RenderWindow &); //Doit se faire avec une interface graphique
bool Contient_pion_noir() const;
bool Contient_pion_blanc() const;
float getX() const;
float getY() const;
void setX(float x);
void setY(float y);
void set_pion_present_noir(bool);
void set_pion_present_blanc(bool);
void set_rectangle(float,float);
void lumineux_rectangle(sf::RenderWindow &,sf::Sprite &);
void rectangle_transparent(sf::RenderWindow &, sf::Sprite &);
sf::FloatRect get_entity();
};







#endif
