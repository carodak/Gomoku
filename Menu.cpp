#include "Menu.h"
#include <iostream>


using namespace sf;
std::string nr,nf;
bool avecIA=0;
Menu::Menu(float  largeur, float hauteur){
    if (!font.loadFromFile("black_jack.ttf")){}

        menu[0].setFont(font);
        menu[0].setColor(sf::Color::Red);
        menu[0].setString("Un Joueur");
        menu[0].setCharacterSize(40);
        menu[0].setPosition(sf::Vector2f(largeur/2.7, 1150 / (NB_ITEM + 1) * 1));

        menu[1].setFont(font);
        menu[1].setColor(sf::Color::White);
        menu[1].setString("Deux Joueurs");
        menu[1].setCharacterSize(40);
        menu[1].setPosition(sf::Vector2f(largeur/3, 875 / (NB_ITEM + 1) * 2));

        menu[2].setFont(font);
        menu[2].setColor(sf::Color::White);
        menu[2].setString("Meilleurs Scores");
        menu[2].setCharacterSize(40);
        menu[2].setPosition(sf::Vector2f(largeur/3.4, 775 / (NB_ITEM + 1) * 3));

        menu[3].setFont(font);
        menu[3].setColor(sf::Color::White);
        menu[3].setString("Aide");
        menu[3].setCharacterSize(40);
        menu[3].setPosition(sf::Vector2f(largeur/2.4, 725 / (NB_ITEM + 1) * 4));

        menu[4].setFont(font);
        menu[4].setColor(sf::Color::White);
        menu[4].setString("Options");
        menu[4].setCharacterSize(40);
        menu[4].setPosition(sf::Vector2f(largeur/2.6, 700 / (NB_ITEM + 1) * 5));

        menu[5].setFont(font);
        menu[5].setColor(sf::Color::White);
        menu[5].setString("Quitter");
        menu[5].setCharacterSize(40);
        menu[5].setPosition(sf::Vector2f(largeur/2.6, 675 / (NB_ITEM + 1) * 6));

        ItemSelecter=0;
    }

    Menu::~Menu(){}

    void Menu::draw(sf::RenderWindow &window){
        for (int i = 0; i < NB_ITEM; i++){
        window.draw(menu[i]);
        }
     }

     void Menu::MoveUp(){
     if (ItemSelecter-1 >= 0){
        menu[ItemSelecter].setColor(sf::Color::White);
        ItemSelecter--;
        menu[ItemSelecter].setColor(sf::Color::Red);
     }
     }

     void Menu::MoveDown(){
     if (ItemSelecter+1 < NB_ITEM){
        menu[ItemSelecter].setColor(sf::Color::White);
        ItemSelecter++;
        menu[ItemSelecter].setColor(sf::Color::Red);
     }
     }

     int Menu::GetItemClicker(){
     return ItemSelecter;
     }


void Menu::drawAide(){
        RenderWindow window(VideoMode(600, 600), "Aide");
        RectangleShape rectangle(sf::Vector2f(600,600));
        Texture texture;
        texture.loadFromFile("woodlight.jpg");
        rectangle.setTexture(&texture);
        Text TxtTitre,TxtAide;
        TxtTitre.setFont(font);
        TxtTitre.setColor(sf::Color(236,137,71));
        TxtTitre.setString("Renju");
        TxtTitre.setPosition(sf::Vector2f(250,5));
        TxtTitre.setCharacterSize(50);
        TxtTitre.setStyle(sf::Text::Underlined);

        TxtAide.setFont(font);
        TxtAide.setColor(sf::Color::White);
        TxtAide.setString("     Le renju se joue sur un plateau de 15 lignes horizontales et 15 \n lignes verticales. \n \n"
                          "     Dans un premier temps, le plateau est vide. Le joueur qui a \n obtenu par tirage au sort"
                          " les pions noirs joue toujours en premier en \n placant son premier pion sur la case centrale du damier. \n \n"
                          "     Le blanc doit alors poser son pion sur l'une des cases libres du \n damier. Noir fait la meme chose et ainsi de suite,"
                          " le but du jeu \n etant de prendre l'adversaire de vitesse et de reussir le premier a \n aligner 5 pions de sa couleur, dans les"
                          " 3 directions possibles: \n vertical, horizontal ou diagonal. Si les deux joueurs placent tous les \n pions sans qu'aucun"
                          " ne parvienne a realiser un alignement, le jeu est \n declare nul.");
       TxtAide.setPosition(sf::Vector2f(0,75));
        TxtAide.setCharacterSize(23);


        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
              switch (event.type)
                    {
                case sf::Event::Closed:
                        {
                        window.close();
                        }
                    default:
                    break;
                    }
            }

            window.clear();
            window.draw(rectangle);
            window.draw(TxtTitre);
            window.draw(TxtAide);
            window.display();
        }
     }






// Si un mode de jeu a été selectionné on nettoie la fenêtre et on l'agrandit pour l'affichage de la grille


     void Menu::drawGrille(sf::RenderWindow &window, Pions &p, Grille &D,sf::Music &music, Joueur &j1, Joueur &j2){

                        D.printGrille(window);


        sf::Texture music_on, music_off, volume_up, volume_down;
        if(!music_on.loadFromFile("music_on.png")){}
        sf::Sprite spriteOn(music_on);
        spriteOn.setPosition(25,275);
        if(!music_off.loadFromFile("music_off.png")){}
        sf::Sprite spriteOff(music_off);
        spriteOff.setPosition(125,275);
        if(!volume_up.loadFromFile("volume_up.png")){}
        sf::Sprite spritevolup(volume_up);
        spritevolup.setPosition(25,375);
        if(!volume_down.loadFromFile("volume_down.png")){}
        sf::Sprite spritevoldown(volume_down);
        spritevoldown.setPosition(125,375);

        int volume=100;

                        while (window.isOpen())
                            {

                                sf::Event event;
                                Curseur A(event); // Le curseur va nous aider pour le clic sur la grille
                                while (window.pollEvent(event))
                                {
                                    //On vérifie le type d'évènement
                                    switch (event.type)
                                    {
                                        //Si l'evenement est de fermer la fenetre
                                        case sf::Event::Closed:
                                        {
                                            window.close();

                                        }

                                          //MouseButtonReleased va éviter que le mentien du click gauche crée plusieures cellules
                                        case sf::Event::MouseButtonReleased:

                                        {
                                            //Si l'évenement est un click gauche
                                            if (event.mouseButton.button == sf::Mouse::Left)
                                            {



                                                //On crée le pion si l'on est sur une cellule
                                                D.verif_click(A,p,event,window,j1,j2);
                                                if (D.gagnant()!=0){
                                                window.display();
                                                D.printVictoire(j1,j2);
                                                }

                                                 if (spriteClick(spriteOn,window)){
                                                volume= 100;
                                                music.setVolume(volume);
                                                }

                                                if (spriteClick(spriteOff,window)){
                                                volume=0;
                                                music.setVolume(volume);
                                                }

                                                if(spriteClick(spritevolup,window)){
                                                volume += 20;
                                                music.setVolume(volume);
                                                }

                                                if(spriteClick(spritevoldown,window)){
                                                volume -= 20;
                                                music.setVolume(volume);
                                                }

                                            }
                                        }


                                        default:
                                        break;
                                    }

                                    window.display();
                                    window.draw(spriteOn);
                                    window.draw(spriteOff);
                                    window.draw(spritevolup);
                                    window.draw(spritevoldown);
                                }
                            }
     }


void Menu::drawjeuIA(sf::RenderWindow& window,sf::Music &music, Joueur &J1, Joueur& J2){
    window.create(sf::VideoMode(1024,768), "Renju Mode Joueur VS Ordi ");
    window.clear();

        sf::Texture texture;
        if (!texture.loadFromFile("woodlight.jpg")){}

        sf::Sprite sprite(texture);

        while (window.isOpen()){

            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(sprite);
            window.display();
            Grille D;
            J1vsIA(window,D,music, J1, J2);
    }
}

void Menu::drawjeuIAMM(sf::RenderWindow& window,sf::Music &music){
    window.create(sf::VideoMode(1024,768), "Renju Mode Joueur VS Ordi ");
    window.clear();

        sf::Texture texture;
        if (!texture.loadFromFile("woodlight.jpg")){}

        sf::Sprite sprite(texture);

        while (window.isOpen()){

            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(sprite);
            window.display();
            Grille D;
            J1vsIAMM(window,D,music);
    }
}

     void Menu::J1vsIA(sf::RenderWindow &window, Grille &D,sf::Music &music, Joueur &J1, Joueur &J2){

        D.printGrille(window);

        sf::Texture music_on, music_off, volume_up, volume_down;
        if(!music_on.loadFromFile("music_on.png")){}
        sf::Sprite spriteOn(music_on);
        spriteOn.setPosition(25,275);
        if(!music_off.loadFromFile("music_off.png")){}
        sf::Sprite spriteOff(music_off);
        spriteOff.setPosition(125,275);
        if(!volume_up.loadFromFile("volume_up.png")){}
        sf::Sprite spritevolup(volume_up);
        spritevolup.setPosition(25,375);
        if(!volume_down.loadFromFile("volume_down.png")){}
        sf::Sprite spritevoldown(volume_down);
        spritevoldown.setPosition(125,375);

        int volume=100;

                        while (window.isOpen())
                            {

                                sf::Event event;
                                Curseur A(event); // Le curseur va nous aider pour le clic sur la grille
                                Ia C;
                                while (window.pollEvent(event))
                                {
                                    //On vérifie le type d'évènement
                                    switch (event.type)
                                    {
                                        //Si l'evenement est de fermer la fenetre
                                        case sf::Event::Closed:
                                        {
                                            window.close();

                                        }

                                          //MouseButtonReleased va éviter que le mentien du click gauche crée plusieures cellules
                                        case sf::Event::MouseButtonReleased:

                                        {
                                            //Si l'évenement est un click gauche
                                            if (event.mouseButton.button == sf::Mouse::Left)
                                            {
                                                C.jouer(D,window,A,J1,J2);
                                                if(D.gagnant()!=0){
                                                window.display();
                                                 D.printVictoire(J1,J2);
                                                 }

                                                 if (spriteClick(spriteOn,window)){
                                                volume= 100;
                                                music.setVolume(volume);
                                                }

                                                if (spriteClick(spriteOff,window)){
                                                volume=0;
                                                music.setVolume(volume);
                                                }

                                                if(spriteClick(spritevolup,window)){
                                                volume += 20;
                                                music.setVolume(volume);
                                                }

                                                if(spriteClick(spritevoldown,window)){
                                                volume -= 20;
                                                music.setVolume(volume);
                                                }


                                            }

                                        }


                                        default:
                                        break;
                                    }

                                    window.display();
                                    window.draw(spriteOn);
                                    window.draw(spriteOff);
                                    window.draw(spritevolup);
                                    window.draw(spritevoldown);

                                }
                            }
     }

 void Menu::J1vsIAMM(sf::RenderWindow &window, Grille &D,sf::Music &music){

        D.printGrille(window);

        sf::Texture music_on, music_off, volume_up, volume_down;
        if(!music_on.loadFromFile("music_on.png")){}
        sf::Sprite spriteOn(music_on);
        spriteOn.setPosition(25,275);
        if(!music_off.loadFromFile("music_off.png")){}
        sf::Sprite spriteOff(music_off);
        spriteOff.setPosition(125,275);
        if(!volume_up.loadFromFile("volume_up.png")){}
        sf::Sprite spritevolup(volume_up);
        spritevolup.setPosition(25,375);
        if(!volume_down.loadFromFile("volume_down.png")){}
        sf::Sprite spritevoldown(volume_down);
        spritevoldown.setPosition(125,375);

        int volume=100;

                        while (window.isOpen())
                            {

                                sf::Event event;
                                Curseur A(event); // Le curseur va nous aider pour le clic sur la grille
                                Ia C;
                                while (window.pollEvent(event))
                                {
                                    //On vérifie le type d'évènement
                                    switch (event.type)
                                    {
                                        //Si l'evenement est de fermer la fenetre
                                        case sf::Event::Closed:
                                        {
                                            window.close();

                                        }

                                          //MouseButtonReleased va éviter que le mentien du click gauche crée plusieures cellules
                                        case sf::Event::MouseButtonReleased:

                                        {
                                            //Si l'évenement est un click gauche
                                            if (event.mouseButton.button == sf::Mouse::Left)
                                            {
                                                C.jouer2(D,window,A);
                                                if(D.gagnant()!=0){
                                                window.display();
                                                 C.printVictoire(D);
                                                 }

                                                 if (spriteClick(spriteOn,window)){
                                                volume= 100;
                                                music.setVolume(volume);
                                                }

                                                if (spriteClick(spriteOff,window)){
                                                volume=0;
                                                music.setVolume(volume);
                                                }

                                                if(spriteClick(spritevolup,window)){
                                                volume += 20;
                                                music.setVolume(volume);
                                                }

                                                if(spriteClick(spritevoldown,window)){
                                                volume -= 20;
                                                music.setVolume(volume);
                                                }


                                            }

                                        }


                                        default:
                                        break;
                                    }

                                    window.display();
                                    window.draw(spriteOn);
                                    window.draw(spriteOff);
                                    window.draw(spritevolup);
                                    window.draw(spritevoldown);

                                }
                            }
     }

    bool Menu::spriteClick(sf::Sprite &sprite, sf::RenderWindow &window)
    {
    sf::IntRect rect(sprite.getPosition().x, sprite.getPosition().y, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);

    //Retourne vrai si on a clické dans le sprite et faux sinon
    if (rect.contains(Mouse::getPosition(window))) {
        return true;
    }

    return false;
}


     void Menu::drawOptions(sf::Music &music){
        RenderWindow window(VideoMode(300, 300), "Options");
        RectangleShape rectangle(sf::Vector2f(300,300));
        Texture texture;
        texture.loadFromFile("woodlight.jpg");
        rectangle.setTexture(&texture);

        sf::Texture soundOn, soundOff, volume_up, volume_down;;
        if(!soundOn.loadFromFile("soundOn.png")){}
        sf::Sprite spriteOn(soundOn);
        spriteOn.setPosition(50,20);
        if(!soundOff.loadFromFile("soundOff.png")){}
        sf::Sprite spriteOff(soundOff);
        spriteOff.setPosition(200,20);
        if(!volume_up.loadFromFile("volume_up.png")){}
        sf::Sprite spritevolup(volume_up);
        spritevolup.setPosition(50,150);
        if(!volume_down.loadFromFile("volume_down.png")){}
        sf::Sprite spritevoldown(volume_down);
        spritevoldown.setPosition(200,150);

        int volume=100;

        while (window.isOpen())
        {
            Event event;
            Curseur S(event);
            while (window.pollEvent(event))
            {
                switch (event.type)
                    {
                    case sf::Event::Closed:
                        {
                        window.close();
                        }
                    case sf::Event::MouseButtonReleased:
                        {
                        if (event.mouseButton.button == sf::Mouse::Left){

                            if (spriteClick(spriteOn,window)){
                                S.playsound(2);
                                music.play();
                            }

                            if (spriteClick(spriteOff,window)){
                                S.playsound(2);
                                music.stop();
                            }

                            if(spriteClick(spritevolup,window)){
                                volume += 20;
                                music.setVolume(volume);
                            }

                             if(spriteClick(spritevoldown,window)){
                                volume -= 20;
                                music.setVolume(volume);
                            }
                        }
                        }
                    default:
                        break;
                    }
                }
            window.clear();
            window.draw(rectangle);
            window.draw(spriteOn);
            window.draw(spriteOff);
            window.draw(spritevolup);
            window.draw(spritevoldown);
            window.display();
        }
        }



void Menu::Partie_Precedente(Joueur& j1, Joueur& j2, bool &withIA){
        RenderWindow window(VideoMode(600, 150), "Partie Precedente ! ");
        sf::Texture texture;
        RectangleShape rectangle(sf::Vector2f(600,150));
        if (!texture.loadFromFile("woodlight.jpg")){}
        rectangle.setTexture(&texture);

        sf::Sprite sprite(texture);
        sf::Font font;
        if (!font.loadFromFile("black_jack.ttf")){}

        sf::Text text;
        text.setFont(font);
        text.setColor(sf::Color::White);
        text.setCharacterSize(21);
        text.move(30, 20);
        text.setString("SOUHAITEZ-VOUS POURSUIVRE LA PARTIE PRECEDENTE ?");

        sf::Sprite bouton1,bouton2;
        sf::Texture Vrai,Faux;

        if(!Vrai.loadFromFile("vrai.png")){};
        bouton1.setTexture(Vrai);
        bouton1.move(100, 70);

        if(!Faux.loadFromFile("faux.png")){};
        bouton2.setTexture(Faux);
        bouton2.move(400, 70);

        while (window.isOpen())
        {
        window.clear();
        window.draw(rectangle);
        window.draw(text);
        window.draw(bouton1);
        window.draw(bouton2);
        window.display();

        sf::Event event;
        while (window.pollEvent(event))
            {
                if(event.type == Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed)
                {

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                if(bouton1.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){

                std::string NomJ1,NomJ2;
            unsigned int ScoreJ1, ScoreJ2;
            ifstream PartieP("partie_prec.txt", ios::in);
            if( PartieP.is_open())
            {
            PartieP >> NomJ1 >> ScoreJ1 >> NomJ2 >> ScoreJ2;
            PartieP.close();
            }
            j1.SetPseudo(NomJ1);
            j1.SetScore(ScoreJ1);
            j2.SetPseudo(NomJ2);
            j2.SetScore(ScoreJ2);
            ofstream PartiePrec("partie_prec.txt", ios::trunc);
            window.close();
            }

            if(bouton2.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
            window.close();
            ofstream PartieP("partie_prec.txt", ios::trunc);
            if (withIA==0)
            j1.Entrer_Pseudo();
            else if (withIA==1){
            j1.SetPseudo("IA");
            withIA==0;
            }
            j2.Entrer_Pseudo();
        }

            }
            }
            }

}
}
void Menu::drawScore(sf::RenderWindow &window, sf::Music &music)

{
        Joueur j1(0);
        Joueur j2(1, "Inconnu");

        Partie_Precedente(j1,j2,avecIA);


    window.create(sf::VideoMode(1024,768), "Renju Mode J1 v J2");
    window.clear();

        sf::Texture texture;
        if (!texture.loadFromFile("woodlight.jpg")){}

        sf::Sprite sprite(texture);

        while (window.isOpen()){

            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(sprite);
            j2.Print_score(window);
            j1.Print_score(window);
            window.display();

    //Avant d'afficher la grille on affiche les scores pendant 2 secondes, permet d'éviter que la grille "arrive" directement sans qu'on ait le temps de voir les scores
            sf::sleep(sf::milliseconds(2000));
           Pions p; Grille D;

           D.qui_commence(j1,j2);
           n1=j1.GetPseudo();
           n2=j2.GetPseudo();
           nr=j2.GetPseudo();
           nf=j1.GetPseudo();

          drawGrille(window,p,D,music,j1,j2);
    }



}

void Menu::drawScore2(sf::RenderWindow &window, sf::Music &music)

{
        Joueur j1(0, "IA");
        Joueur j2(1, "Joueur1");
avecIA=1;
j1.setCouleur(Joueur::BLANC);
j2.setCouleur(Joueur::NOIR);
        Partie_Precedente(j1,j2, avecIA);


    window.create(sf::VideoMode(1024,768), "Renju Mode Joueur VS IA");
    window.clear();

        sf::Texture texture;
        if (!texture.loadFromFile("woodlight.jpg")){}

        sf::Sprite sprite(texture);

        while (window.isOpen()){

            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(sprite);
            j2.Print_score(window);
            j1.Print_score(window);
            window.display();

    //Avant d'afficher la grille on affiche les scores pendant 2 secondes, permet d'éviter que la grille "arrive" directement sans qu'on ait le temps de voir les scores
            sf::sleep(sf::milliseconds(2000));


          menuSecondaire(window,music,j1,j2);
    }



}

void Menu::menuSecondaire(sf::RenderWindow& window,sf::Music &music, Joueur &J1, Joueur &J2){
  window.create(sf::VideoMode(500, 400), "Choix du mode");
        RectangleShape rectangle(sf::Vector2f(500,500));
        Texture texture;
        texture.loadFromFile("woodlight.jpg");
        rectangle.setTexture(&texture);

        sf::Texture MorpionMM, MorpionAB, RenjuMM, RenjuAB;
        if(!MorpionMM.loadFromFile("MorpionMM.png")){}
        sf::Sprite spriteMorpionMM(MorpionMM);
        spriteMorpionMM.setPosition(60,70);
        if(!MorpionAB.loadFromFile("MorpionAB.png")){}
        sf::Sprite spriteMorpionAB(MorpionAB);
        spriteMorpionAB.setPosition(50,150);
        if(!RenjuMM.loadFromFile("RenjuMM.png")){}
        sf::Sprite spriteRenjuMM(RenjuMM);
        spriteRenjuMM.setPosition(90,240);
        if(!RenjuAB.loadFromFile("RenjuAB.png")){}
        sf::Sprite spriteRenjuAB(RenjuAB);
        spriteRenjuAB.setPosition(75,330);


        while (window.isOpen())
        {
            Event event;
            Curseur S(event);
            while (window.pollEvent(event))
            {
                switch (event.type)
                    {
                    case sf::Event::Closed:
                        {
                        window.close();
                        }
                    case sf::Event::MouseButtonReleased:
                        {
                        if (event.mouseButton.button == sf::Mouse::Left){

                            if (spriteClick(spriteMorpionMM,window)){
                                std::cout<<"APPEL SYSTEM MORPION MIN MAX"<<std::endl;
                                system("./morpion/minmax/morpion ");
                            }

                            if (spriteClick(spriteMorpionAB,window)){
                                std::cout<<"APPEL SYSTEM MORPION ALPHA BETA"<<std::endl;
                                system("./morpion/alphabeta/morpionAB ");
                            }

                            if(spriteClick(spriteRenjuMM,window)){
                                drawjeuIAMM(window,music);
                             }

                            if(spriteClick(spriteRenjuAB,window)){
                                drawjeuIA(window,music,J1,J2);
                            }
                        }
                        }
                    default:
                        break;
                    }
                }

            window.clear();
            window.draw(rectangle);
            window.draw(spriteMorpionMM);
            window.draw(spriteMorpionAB);
            window.draw(spriteRenjuMM);
            window.draw(spriteRenjuAB);
            window.display();
        }
        }










