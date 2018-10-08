#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Grille.h"
#include "Pions.h"
#include "Joueur.h"
#include "Ia.h"
#include <fstream>

#define NB_ITEM 7



class Menu{
private:
    int ItemSelecter;
    sf::Font font;
    sf::Text menu[NB_ITEM];

public:
    Menu(float largeur, float hauteur);
    ~Menu();
    string n1,n2;
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetItemClicker();
    void drawAide();
    void drawjeuIA(sf::RenderWindow& window,sf::Music &music, Joueur& J1, Joueur& J2);
    void drawjeuIAMM(sf::RenderWindow& window,sf::Music &music);
    void J1vsIA(sf::RenderWindow &window, Grille &D,sf::Music &music, Joueur& J1, Joueur &J2);
    void J1vsIAMM(sf::RenderWindow &window, Grille &D,sf::Music &music);
    void drawGrille(sf::RenderWindow &window, Pions&, Grille&,sf::Music&, Joueur&, Joueur&);
    void drawOptions(sf::Music &music);
    bool spriteClick(sf::Sprite &sprite, sf::RenderWindow &window);
    void drawScore(sf::RenderWindow &window,sf::Music &);
    void drawScore2(sf::RenderWindow &window, sf::Music &music);
    void Partie_Precedente(Joueur&,Joueur&,bool&);
    void menuSecondaire(sf::RenderWindow& windowJeu,sf::Music &music, Joueur&, Joueur&);
};
