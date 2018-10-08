#ifndef PIONS_H
#define PIONS_H
#include "Cellule.h"

using namespace std;

class Pions{
public:
    enum Couleur{
    NOIR,
    BLANC,
    NB_COULEURS
    };

private:
    const unsigned int nb_pions;
    Couleur couleur_pion;

public:
    Pions(); //Constructeurs par défaut
    Pions(Couleur coul); //Constructeur paramétré
    Couleur getCouleur() const; //Accesseur en lecture
    void setCouleur(Couleur coul); //Accesseur en écriture
    void pion_blanc();
    void pion_noir();
};
#endif // PIONS_H
