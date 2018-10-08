#include "Grille.h"
#include <iostream>
#include <stdlib.h> //Pour rand() , qui sera utilisée dans la méthode : qui_commence()
#include <unistd.h>
#define ATTENDRE(temps) sleep(temps)

using namespace std;
using namespace sf;

float v = 200;
float w = 50;


Grille::Grille(){
    for (int i=0; i<NMAX; i++){
        for (int j=0 ; j<NMAX; j++){
            Gri[i][j].setX(v);
            Gri[i][j].setY(w);
          Gri[i][j].set_rectangle(v,w);
            w+=40;
        }
        v+=40;
        w = 50;
    }
}

Cellule& Grille::getCellule(int i, int j){
return Gri[i][j];
}


void Grille::printGrille(sf::RenderWindow &window){
 for (int i=0; i<NMAX; i++){
        for (int j=0 ; j<NMAX; j++){
        Gri[i][j].Print_cellule(window) ;
        }
    }
}

int f=0; //Compte le nombre de tours
// poser_pion_b vaut true si l'on a posé un pion blanc au tour précédent, idem pour poser_pion_n
bool poser_pion_b=false;
bool poser_pion_n=false;

//n et m permettent de garder en mémoire la cellule sur lequel le pion a été posé
int n;
int m;

void Grille::verif_click(Curseur &B,Pions &p, sf::Event event, sf::RenderWindow &window, Joueur &J1, Joueur &J2){

    sf::Sprite sprite;
    //Si l'on a posé un pion au tour précédent, on enlève la coloration de la case où ce pion a été posé
    //il faut reafficher l'image du pion

if ( f==2) { choix(J2,J1);



        Font font;
        font.loadFromFile("black_jack.ttf");
        Text text1, text2;
        text1.setFont(font);
        text2.setFont(font);
        string s1,s2;
        if (J1.GetCouleur()==0){
            s1="noir";
        }else{s1="blanc";}

        if (J2.GetCouleur()==0){
            s2="noir";
        }else{s2="blanc";}

        text1.setString(J1.GetPseudo()+" joue avec le pion "+s1);
        text2.setString(J2.GetPseudo()+" joue avec le pion "+s2);
        text1.setCharacterSize(35);
        text2.setCharacterSize(35);
        text1.setColor(sf::Color::White);
        text2.setColor(sf::Color::White);
        //text1.setStyle(sf::Text::Bold);
        //text2.setStyle(sf::Text::Bold);
        text1.move(300,650);
        window.draw(text1);
        text2.move(300,695);
        window.draw(text2);



}

if (poser_pion_b==true){
        sf::Texture pionB;
        if(!pionB.loadFromFile("blanc.png")){}
        sprite.setPosition(Gri[n][m].getX(),Gri[n][m].getY());
        sprite.setTexture(pionB);
        Gri[n][m].rectangle_transparent(window,sprite);
        poser_pion_b=false;
}

if (poser_pion_n==true){
        sf::Texture pionB;
        if(!pionB.loadFromFile("noir.png")){}
        sprite.setPosition(Gri[n][m].getX(),Gri[n][m].getY());
        sprite.setTexture(pionB);
        Gri[n][m].rectangle_transparent(window,sprite);
        poser_pion_n=false;
}

if (f==0) {  B.restriction(p,window,Gri[(int)NMAX/2][(int)NMAX/2]); f++;return;}
for(int i=0; i<NMAX; i++){

    for (int j=0 ;j<NMAX; j++){
            B.Pion_cree_apres_click(p,event,window,Gri[i][j],f,poser_pion_b,poser_pion_n);
            if(poser_pion_b==true || poser_pion_n==true){
            n=i;
            m=j;
            return;
            }
        }
    }

}



void Grille::choix(Joueur &J1, Joueur &J2)  {
RenderWindow window(VideoMode(800,600),"Choix");
 window.clear();
sf::Texture texture;
RectangleShape rectangle(sf::Vector2f(500,250));
if (!texture.loadFromFile("woodlight.jpg")){}
rectangle.setTexture(&texture);

Font font;
font.loadFromFile("black_jack.ttf");
Text text,text1,text2;
text.setFont(font);
text.setColor(sf::Color::White);
text.setPosition(sf::Vector2f(1/3*800,1/3*600));
text.setCharacterSize(40);

sf::FloatRect textRect = text.getLocalBounds();

Text un("BLANC",font,25);
un.setColor(Color::Yellow);
Text deux("NOIR",font,25);
deux.setColor(Color::Green);

un.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
un.setPosition(sf::Vector2f(280,600/2));

deux.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
deux.setPosition(sf::Vector2f(480,600/2));

text1.setFont(font);
text1.setColor(sf::Color::White);
text1.setPosition(sf::Vector2f(280,300));
text1.setCharacterSize(25);

text2.setFont(font);
text2.setColor(sf::Color::White);
text2.setPosition(sf::Vector2f(280,300));
text2.setCharacterSize(25);

text.setString(" "+J1.GetPseudo()+" doit choisir la couleur de ses pions !");

text1.setString(" "+J1.GetPseudo()+" Joue avec les pions blancs , c'est donc son tour !");

text2.setString(" "+J1.GetPseudo()+" Joue avec les pions noirs , \n     son tour vient juste apres ");

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
                case sf::Event::MouseButtonReleased:

                        {
                    //Si l'évenement est un click gauche
                            if (event.mouseButton.button == sf::Mouse::Left){
                                if (un.getGlobalBounds().contains (event.mouseButton.x, event.mouseButton.y)){
                                window.clear();
                                window.draw(text1);
                                window.display();
                                J1.setCouleur(Joueur::BLANC);
                                J2.setCouleur(Joueur::NOIR);
                                ATTENDRE(2);
                                window.close();
                                }

                                else  if (deux.getGlobalBounds().contains (event.mouseButton.x, event.mouseButton.y)){
                                window.clear();
                                window.draw(text2);
                                window.display();
                                J1.setCouleur(Joueur::NOIR);
                                J2.setCouleur(Joueur::BLANC);
                                ATTENDRE(2);
                                window.close();
                                }
                        }
                    }
                    default:
                    break;
                    }
            }

       window.clear();

        window.draw(text);
        window.draw(un);
        window.draw(deux);

        window.display();
        }

}



int Grille::qui_commence (Joueur& J1,Joueur& J2) {


RenderWindow window(VideoMode(800,600),"Qui Commence ?");

Texture texture;
texture.loadFromFile("woodlight.jpg");
Font font;
font.loadFromFile("black_jack.ttf");
Music music;
music.openFromFile("0029.ogg");
Text text("Qui commence ? ",font,60);
Text un(" "+J1.GetPseudo()+" commence !",font,50);
un.setColor(Color::Yellow);
Text deux(" "+J2.GetPseudo()+" commence !",font,50);
deux.setColor(Color::Green);
sf::FloatRect textRect = text.getLocalBounds();
text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
text.setPosition(sf::Vector2f(800/2.0f,600/2.0f));

un.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
un.setPosition(sf::Vector2f(800/2.0f,600/2.0f));

deux.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
deux.setPosition(sf::Vector2f(800/2.0f,600/2.0f));



 while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::Closed)
                window.close();
        }

if (event.type == sf::Event::MouseButtonPressed)
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {

        int x=event.mouseButton.x;
        int y=event.mouseButton.y;

        if ( x < 600 && x > 200 && y < 600 && y > 200){

        music.play();
        text.setColor(Color::Red);

        int v1=rand() % 100; //un rand entre 0 et 100


        if (v1%2) {

        window.clear();
        window.draw(un);



        window.display();
        ATTENDRE(5);
        window.close();
        return 1;

         //Correspond au joueur avec l'id 1
        }

        else {

        window.clear();

        window.draw(deux);
        Joueur J3;
        J3.SetPseudo(J2.GetPseudo());
        J3.setCouleur(J2.GetCouleur());
        J3.SetNbp_j(J2.GetNbp_j());
        J3.SetNb_tour(J2.GetNb_tour());
        J3.SetScore(J2.GetScore_j());

        J2.SetPseudo(J1.GetPseudo());
        J2.setCouleur(J1.GetCouleur());
        J2.SetNbp_j(J1.GetNbp_j());
        J2.SetNb_tour(J1.GetNb_tour());
        J2.SetScore(J1.GetScore_j());

        J1.SetPseudo(J3.GetPseudo());
        J1.setCouleur(J3.GetCouleur());
        J1.SetNbp_j(J3.GetNbp_j());
        J1.SetNb_tour(J3.GetNb_tour());
        J1.SetScore(J3.GetScore_j());



        window.display();
        ATTENDRE(5);

        //Sinon return 2 , qui correspond au joueur avec l'id 2;


        return 2;

        }
        }


    }

}

        window.clear();


        window.draw(text);

        window.display();





}

return -1;
}


int* Grille::nb_series(int n) //Compte le nombre de séries de n pions alignés de chacun des joueurs
{
     int compteur1, compteur2, i, j, k, j1=0,j2=0;

     int series[3];

     compteur1 = 0;
     compteur2 = 0;

      //Diagonale descendante
     for(k=0;k<NMAX;k++){
        compteur1 = 0;
        compteur2 = 0;
        for(int j=0;j<=k;j++){
            i=NMAX-1-k+j;
            if(Gri[i][j].Contient_pion_blanc())
            {
                compteur1++;
                compteur2 = 0;
                 if(compteur1 == n)
               {
                    j1++;
               }
            }
            if(Gri[i][j].Contient_pion_noir())
            {
               compteur2++;
               compteur1 = 0;

               if(compteur2 == n)
               {
                     j2++;
               }
            }
            else if(!Gri[i][j].Contient_pion_blanc() && !Gri[i][j].Contient_pion_noir())
            {
                compteur1 = 0;
                compteur2 = 0;
            }
        }
     }

     compteur1 = 0;
     compteur2 = 0;

     for(k=NMAX-2;k>=0;k--){
        compteur1 = 0;
        compteur2 = 0;
        for(int j=0;j<=k;j++){
            i=NMAX-1-k+j;
            if(Gri[j][i].Contient_pion_blanc())
            {
                compteur1++;
                compteur2 = 0;

                if(compteur1 == n)
               {
                    j1++;
               }
            }
            if(Gri[j][i].Contient_pion_noir())
            {
               compteur2++;
               compteur1 = 0;

               if(compteur2 == n)
               {
                     j2++;
               }
            }
            else if(!Gri[j][i].Contient_pion_blanc() && !Gri[j][i].Contient_pion_noir())
            {
                compteur1 = 0;
                compteur2 = 0;
            }
        }
     }

     compteur1 = 0;
     compteur2 = 0;

     //Diagonale montante
     for(k=0;k<NMAX;k++){
        compteur1 = 0;
        compteur2 = 0;
        for(int j=0;j<=k;j++){
            i=k-j;
            if(Gri[i][j].Contient_pion_blanc())
            {
                compteur1++;
                compteur2 = 0;
                 if(compteur1 == n)
               {
                    j1++;
               }
            }
            if(Gri[i][j].Contient_pion_noir())
            {
               compteur2++;
               compteur1 = 0;

               if(compteur2 == n)
               {
                     j2++;
               }
            }
            else if(!Gri[i][j].Contient_pion_blanc() && !Gri[i][j].Contient_pion_noir())
            {
                compteur1 = 0;
                compteur2 = 0;
            }
        }
     }

     compteur1 = 0;
     compteur2 = 0;

     for(k=NMAX-2;k>=0;k--){
        compteur1 = 0;
        compteur2 = 0;
        for(int j=0;j<=k;j++){
            i=k-j;
            if(Gri[NMAX-j-1][NMAX-i-1].Contient_pion_blanc())
            {
                compteur1++;
                compteur2 = 0;

                if(compteur1 == n)
               {
                    j1++;
               }
            }
            if(Gri[NMAX-j-1][NMAX-i-1].Contient_pion_noir())
            {
               compteur2++;
               compteur1 = 0;

               if(compteur2 == n)
               {
                     j2++;
               }
            }
            else if(!Gri[NMAX-j-1][NMAX-i-1].Contient_pion_blanc() && !Gri[NMAX-j-1][NMAX-i-1].Contient_pion_noir())
            {
                compteur1 = 0;
                compteur2 = 0;
            }
        }
     }

     //En ligne
     for(i=0;i<NMAX;i++)
     {
          compteur1 = 0;
          compteur2 = 0;

          //Horizontalement
          for(j=0;j<NMAX;j++)
          {
               if(Gri[i][j].Contient_pion_blanc())
               {
                    compteur1++;
                    compteur2 = 0;

                    if(compteur1 == n)
                    {
                         j1++;
                    }
               }
               if(Gri[i][j].Contient_pion_noir())
               {
                    compteur2++;
                    compteur1 = 0;

                    if(compteur2 == n)
                    {
                         j2++;
                    }
               }
               else if(!Gri[i][j].Contient_pion_blanc() && !Gri[i][j].Contient_pion_noir())
                {
                compteur1 = 0;
                compteur2 = 0;
                }
          }
     }


        compteur1 = 0;
        compteur2 = 0;

    for(i=0;i<NMAX;i++)
        {
          compteur1 = 0;
          compteur2 = 0;

          //Verticalement
          for(j=0;j<NMAX;j++)
          {
               if(Gri[j][i].Contient_pion_blanc())
               {
                    compteur1++;
                    compteur2 = 0;

                    if(compteur1 == n)
                    {
                         j1++;
                    }
               }
               if(Gri[j][i].Contient_pion_noir())
               {
                    compteur2++;
                    compteur1 = 0;

                    if(compteur2 == n)
                    {
                         j2++;
                    }
               }
               else if(!Gri[j][i].Contient_pion_blanc() && !Gri[j][i].Contient_pion_noir())
              {
                compteur1 = 0;
                compteur2 = 0;
              }
          }
     }
     series[0]=j1;
     series[1]=j2;
     cout<<"series"<<series[0];
     cout<<"series"<<series[1];
     return series;
}




int Grille::gagnant()
{
     int* T;
     T=nb_series(5);
     int i,j;
     int j1=T[0],j2=T[1];

     if(j1)
     {
          return 1;
     }
     else if(j2)
     {
          return 2;
     }
     else
     {
          //Si le jeu n'est pas fini et que personne n'a gagné, on renvoie 0
          for(i=0;i<NMAX;i++)
          {
               for(j=0;j<NMAX;j++)
               {
                    if(!Gri[i][j].Contient_pion_noir() && !Gri[i][j].Contient_pion_blanc())
                    {
                         return 0;
                    }
               }
          }
     }

     //Si le jeu est fini et que personne n'a gagné, on renvoie 3
     return 3;
}



void Grille::printVictoire(Joueur& j1, Joueur& j2){

RenderWindow window(VideoMode(500,250),"Victoire !");
sf::Texture texture;
RectangleShape rectangle(sf::Vector2f(500,250));
if (!texture.loadFromFile("woodlight.jpg")){}
rectangle.setTexture(&texture);

Font font;
font.loadFromFile("black_jack.ttf");
Text text,text1;
text.setFont(font);
text.setColor(sf::Color::White);
text.setPosition(sf::Vector2f(100,70));
text.setCharacterSize(40);

text1.setFont(font);
text1.setColor(sf::Color::White);
text1.setPosition(sf::Vector2f(100,90));
text1.setCharacterSize(20);

//gagnant = 1 correspond à une victoire des pions blancs
// on vérifie ensuite quel joueur avait les pions blancs

 if((gagnant()==1 && j2.GetCouleur()==Joueur::BLANC) || gagnant()==2 && j2.GetCouleur()==Joueur::NOIR){

text.setString("Victoire de " + j2.GetPseudo() +" ! ");
j2.AjoutScore();

j1.Enregistrer_Score();
j2.Enregistrer_Score();

if(j2.GetScore_j()>j2.Meilleur_Score()){
                text1.setString("Nouveau Record !");
            }

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
            window.draw(text);
            window.draw(text1);
            window.display();
        }

    }

 if(gagnant()==2 && j1.GetCouleur()==Joueur::NOIR || gagnant()==1 && j1.GetCouleur()==Joueur::BLANC){

text.setString("Victoire de "+ j1.GetPseudo()+" !");
j1.AjoutScore();

j1.Enregistrer_Score();
j2.Enregistrer_Score();

if(j2.GetScore_j()>j2.Meilleur_Score()){
        text1.setString("Nouveau Record !");
            }
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
            window.draw(text);
            window.draw(text1);
            window.display();
        }

    }

     if(gagnant()==3){

text.setString("Match Nul !");

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
            window.draw(text);
            window.draw(text1);
            window.display();
        }

    }
}


