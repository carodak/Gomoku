#ifndef CURSEUR_H
#define CURSEUR_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Cellule.h"
#include "Pions.h"



class Curseur
{
    public:
        Curseur(sf::Event &event);
        //Accesseurs en lecture
        float getX() const;
        float getY() const;

        //Accesseurs en écriture
        void setX(sf::Event);
        void setY(sf::Event);

        //Autres
        void Pion_cree_apres_click(Pions &, sf::Event, sf::RenderWindow &, Cellule &,int &, bool&, bool&);
        void playsound(int);
        void restriction(Pions &,sf::RenderWindow&,Cellule&);
    private:
            float position_souris_x; //Coordonnées du curseur dans la fenêtre de jeu
            float position_souris_y;


};

#endif // CURSEUR_H
