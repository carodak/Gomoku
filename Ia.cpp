#include "Ia.h"
#include <iostream>
using namespace std;
int nb_tours=0;


/*On crée les méthodes qui vont dessiner un pion noir et un pion blanc
il faut aussi vérifier qu'on est bien sur une cellule et pas en dehors du plateau
*/


void Ia::jouer(Grille& G,sf::RenderWindow &window,Curseur &B, Joueur& J1, Joueur &J2) {
Pions p;

if ( nb_tours==2) { cout<<"YES"<<endl; G.choix(J2,J1);

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
if (nb_tours==0) { B.restriction(p,window,G.getCellule((int)NMAX/2,(int)NMAX/2)); nb_tours++;return;}

for(int i=0; i<NMAX; i++){

    for (int j=0 ;j<NMAX; j++){

/*getCellule(i,j) est une méthode de la classe Grille qui retourne Gri[i][j] c'est à dire la cellule du tableau
qui est aux coordonnées (i,j)
*/

/*
get_entity est une méthode de la classe Cellule qui utilise la méthode
 sf::Sprite::getGlobalBounds() qui retourne la position et la dimension du sprite
 -> on vérifie donc si le curseur est sur le rectangle de la cellule de coordonnées (i,j)
*/

   if (G.getCellule(i,j).get_entity().contains(B.getX(), B.getY()) && G.getCellule(i,j).Contient_pion_noir()== false && G.getCellule(i,j).Contient_pion_blanc()== false){
if(J2.GetCouleur()==Joueur::NOIR)
    draw_pion_noir(window, G.getCellule(i,j));
    else draw_pion_blanc(window, G.getCellule(i,j));

    if (nb_tours!=1 && nb_tours!=2){
        IA_jouer(2,window,G, J1);
}

    }

}
}
}


int Ia::eval(Grille& A)
{
   int vainqueur=A.gagnant(),nb_de_pions = 0;
     int i,j;

     //On compte le nombre de pions présents sur le plateau
     for(i=0;i<NMAX;i++)
     {
     //NMAX VAUT 15 POUR LE RENJU , démarre de 0 à 14 donc
          for(j=0;j<NMAX;j++)
          {
               if(A.getCellule(i,j).Contient_pion_noir()  || A.getCellule(i,j).Contient_pion_blanc())
               {
                    nb_de_pions++;
               }
          }
     }

     if( vainqueur != 0)
     {
          if( vainqueur == 1 )
          {
            	cout<<" JOUEUR 1 "<<endl;
               return 1000 - nb_de_pions;
          }
          else if( vainqueur == 2 )
          {

            		cout<<" JOUEUR 2 "<<endl;
               return -1000 + nb_de_pions;
          }
          else
          {
            cout<<" NUL "<<endl;
               return 0;
          }
     }

     //On compte le nombre de séries de 2 pions alignés de chacun des joueurs
     int* series;

     series=A.nb_series(2);
     int series1=series[0];
     int series2=series[1];
     cout<<"serieseval"<<series[0];
     cout<<"serieseval"<<series[1]<<endl;

     return series1 - series2;

}



void Ia::draw_pion_blanc(sf::RenderWindow& window, Cellule &A) {
sf::Sprite sprite;

    sf::Texture pionB;

    if(!pionB.loadFromFile("blanc.png")){}
            {
        sprite.setPosition(A.getX(),A.getY());
        sprite.setTexture(pionB);
        window.draw(sprite);
        A.set_pion_present_blanc(true);
        nb_tours++;
        }
}

void Ia::draw_pion_noir(sf::RenderWindow& window, Cellule &A) {
sf::Sprite sprite;

    sf::Texture pionB;

    if(!pionB.loadFromFile("noir.png")){}
            {
        sprite.setPosition(A.getX(),A.getY());
        sprite.setTexture(pionB);
        window.draw(sprite);
        A.set_pion_present_noir(true);
        nb_tours++;
        }

}

void Ia::IA_jouer(int profondeur,sf::RenderWindow& window, Grille& A, Joueur &J1)
{

     int tmp;
     int i,j;
    int maxi=-1,maxj=-1;
    int alpha = -10000;
    int beta = 10000;


     for(i=0;i<NMAX;i++)
     {
          for(j=0;j<NMAX;j++)
          {
                if(!(A.getCellule(i,j)).Contient_pion_blanc() && !(A.getCellule(i,j).Contient_pion_noir()))
                {
                      A.getCellule(i,j).set_pion_present_blanc(true);
                      tmp = Min(profondeur-1,window, alpha, beta,A);
                        if(alpha<tmp)
                        {

                        alpha = tmp;
                        maxi = i;
                        maxj = j;
                        }

                       A.getCellule(i,j).set_pion_present_blanc(false);
                       cout<<"tessssst222"<<endl;
                }
          }
     }
     cout<<"tessssst"<<endl;
     // (A.getCellule(maxi,maxj)).set_pion_present_blanc(true);
     if(J1.GetCouleur()==Joueur::BLANC)
    draw_pion_blanc(window,A.getCellule(maxi,maxj));
    else
    draw_pion_noir(window,A.getCellule(maxi,maxj));
}

int Ia::Min(int profondeur,sf::RenderWindow& window, int alpha, int beta, Grille &A)

{

     if(profondeur == 0 || A.gagnant() != 0)

     {

          return eval(A);

     }

     int i,j,tmp;


     for(i=0;i<NMAX;i++)

     {

          for(j=0;j<NMAX;j++)

          {

                if(!(A.getCellule(i,j)).Contient_pion_blanc()&& !(A.getCellule(i,j)).Contient_pion_noir())

                {

                      (A.getCellule(i,j)).set_pion_present_noir(true);

                      tmp = Max(profondeur-1, window, alpha, beta, A);

                      (A.getCellule(i,j)).set_pion_present_noir(false);
            if(beta>tmp)
		    {
		    beta = tmp;
		    }

            if(beta<=alpha)
			{
		        return beta;
			}
                }
            }
            }
    return beta;
}

int Ia::Max(int profondeur,sf::RenderWindow &window, int alpha, int beta, Grille& A)

{


     if(profondeur == 0 || A.gagnant() != 0)

     {

          return eval(A);

     }

     int i,j,tmp;


     for(i=0;i<NMAX;i++)

     {

          for(j=0;j<NMAX;j++)

          {

                if(!(A.getCellule(i,j)).Contient_pion_blanc() && !(A.getCellule(i,j)).Contient_pion_noir())

                {

                      (A.getCellule(i,j)).set_pion_present_blanc(true);

                      tmp = Min(profondeur-1,window, alpha,beta,A);

                      (A.getCellule(i,j)).set_pion_present_blanc(false);
        if(alpha<tmp)
		    {
		    alpha = tmp;
		    }

		if(beta <= alpha)
		    {
		    return alpha;
		    }
                }
            }
            }

    return alpha;
}



void Ia::printVictoire(Grille& G){

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

 if(G.gagnant()==1){

text.setString("Victoire de joueur1");


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


 if(G.gagnant()==2){

text.setString("Victoire de joueur2 !");

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

     if(G.gagnant()==3){

text.setString("Match nul!");

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


///////////////////////////////////Algorithme min-max//////////////////////////////////////
int Ia::Min2(int profondeur,sf::RenderWindow &window,Grille& A)

{
   // cout<<"min";

     if(profondeur == 0 || A.gagnant() != 0)
     {
          return eval(A);
     }

     int min = 10000;

     int i,j,tmp;

     for(i=0;i<NMAX;i++)
     {
          for(j=0;j<NMAX;j++)
          {
                if(!(A.getCellule(i,j)).Contient_pion_blanc() && !(A.getCellule(i,j)).Contient_pion_noir())
                {
                      (A.getCellule(i,j)).set_pion_present_noir(true);

                      tmp = Max2(profondeur-1,window,A);

                      if(tmp < min)
                      {
                            min = tmp;
                      }
                      (A.getCellule(i,j)).set_pion_present_noir(false);
                }
          }
     }
    cout<<" min "<<min;
     return min;

}

int Ia::Max2(int profondeur,sf::RenderWindow &window,Grille& A)
{
    //cout<<"max";

     if(profondeur == 0 || A.gagnant() != 0)

     {
          return eval(A);
     }

     int max = -10000;

     int i,j,tmp;

     for(i=0;i<NMAX;i++)
     {
          for(j=0;j<NMAX;j++)
          {
                if(!(A.getCellule(i,j)).Contient_pion_blanc() && !(A.getCellule(i,j)).Contient_pion_noir())
                {
                      (A.getCellule(i,j)).set_pion_present_blanc(true);

                      tmp = Min2(profondeur-1,window, A);

                      if(tmp > max)
                      {
                            max = tmp;
                      }

                      (A.getCellule(i,j)).set_pion_present_blanc(false);
                }
          }
     }
     cout<<" max "<<max;
     return max;

}


void Ia::IA_jouer2(int profondeur,sf::RenderWindow& window, Grille& A)
{

    cout<<"FONCTION IA DEDANS "<<endl;
     int maximum = -10000;
     int tmp;
     int i,j;
     int maxi=-1;
     int maxj=-1;

     for(i=0;i<NMAX;i++)
     {

          for(j=0;j<NMAX;j++)
          {
                 if(!(A.getCellule(i,j)).Contient_pion_blanc() && !(A.getCellule(i,j).Contient_pion_noir()))
                {
                      A.getCellule(i,j).set_pion_present_blanc(true);
                      tmp = Min2(profondeur-1,window,A);
                      if(tmp > maximum)
                      {
                            cout<<" TMP PLUS GRAND QUE MAX OK "<<endl;
                            maximum = tmp;
                            maxi = i;
                            maxj = j;
                           cout<<"maxi : "<<maxi<<" max j : "<<maxj<<endl;
                           cout<<"maxi : "<<i<<" max j : "<<j<<endl;


                      }
                      A.getCellule(i,j).set_pion_present_blanc(false);
                }
          }
     }
    cout<<"FINI DE JOUER IA "<<endl;
     // (A.getCellule(maxi,maxj)).set_pion_present_blanc(true);
     cout<<"maxi : "<<maxi<<" max j : "<<maxj<<endl;
     draw_pion_blanc(window,A.getCellule(maxi,maxj));
}

void Ia::jouer2(Grille& G,sf::RenderWindow &window,Curseur &B) {


for(int i=0; i<NMAX; i++){

    for (int j=0 ;j<NMAX; j++){

/*getCellule(i,j) est une méthode de la classe Grille qui retourne Gri[i][j] c'est à dire la cellule du tableau
qui est aux coordonnées (i,j)
*/

/*
get_entity est une méthode de la classe Cellule qui utilise la méthode
 sf::Sprite::getGlobalBounds() qui retourne la position et la dimension du sprite
 -> on vérifie donc si le curseur est sur le rectangle de la cellule de coordonnées (i,j)
*/

   if (G.getCellule(i,j).get_entity().contains(B.getX(), B.getY()) && G.getCellule(i,j).Contient_pion_noir()== false && G.getCellule(i,j).Contient_pion_blanc()== false){


            if(nb_tours%2==0) {

    draw_pion_noir(window, G.getCellule(i,j));
        IA_jouer2(2,window,G);

        }
    }

}
}
}


