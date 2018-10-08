#include <SFML/Graphics.hpp>
#include <iostream>
#include "SFML/Audio.hpp"
#include "Menu.h"
#include "Curseur.h"
#include "Pions.h"
#include "Grille.h"
#include "tmp.h"


using namespace std;

int main()
{
nbtours=0;
/*
    A FAIRE :
*/
 sf::RenderWindow window(sf::VideoMode(600,600), "RENJU!");


    sf::Texture texture;
    if (!texture.loadFromFile("woodlight.jpg")){}
    sf::Sprite sprite(texture);
    sprite.setPosition(-25,-450);

    Menu menu(window.getSize().x,window.getSize().y);

    sf::Texture gotexture;
    if(!gotexture.loadFromFile("renju.png")){}
    sf::Sprite gosprite(gotexture);
    gosprite.setPosition(168,10);

    sf::Music music;
    if(!music.openFromFile("Time-traveler.ogg"))
    {
        std::cout << "ERROR" << std::endl;
    }
    music.play();
    music.setLoop(true);
    window.clear();

 while (window.isOpen())
    {

        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;

                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;

                case sf::Keyboard::Return:
                    switch (menu.GetItemClicker())
                    {
                    case 0:  {
                        menu.drawScore2(window,music);
                        std::cout<< "Le mode de jeu 1 Joueur a été selectionné" <<std::endl;
                        }
                        break;
                    case 1:
                         {

                        menu.drawScore(window,music);

                        std::cout<< "Le mode de jeu 2 Joueurs a été selectionné" <<std::endl;
                        }
                        break;
                    case 2:
                         std::cout<< "Meilleurs Scores" <<std::endl;
                        break;
                    case 3:
                         menu.drawAide();
                        break;
                    case 4:
                         menu.drawOptions(music);
                        break;
                    case 5:
                         window.close();
                        break;

                        default:
                        break;
                    }
                    default:
                    break;
                }

                default:
                break;
                case sf::Event::Closed:
                window.close();

            }
        }

        window.clear();

        window.draw(sprite);
        window.draw(gosprite);

        menu.draw(window);

        window.display();
    }



    /*
    ====================================================================================================================
    */





    return 0;
}
