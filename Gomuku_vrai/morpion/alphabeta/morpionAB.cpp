#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#define NMAX 3

using namespace std;
using namespace sf;



class Cellule {


private :


unsigned int x;
unsigned int y;
bool croix;
bool rond;
//On crée un rectangle représentant la cellule
sf::RectangleShape rectangle;


public :


Cellule();  //Constructeur par défaut
void Print_cellule(sf::RenderWindow &); //Doit se faire avec une interface graphique
float getX() const;
float getY() const;
bool Has_Croix() const;
bool Has_Rond() const;
void setCroix(bool);
void setRond(bool);
void setX(float x);
void setY(float y);
void set_rectangle(float,float);
sf::FloatRect get_entity();
};



Cellule::Cellule()
{
//taille du rectangle représentant la cellule de 35 par défaut
    rectangle.setSize(sf::Vector2f(35, 35));
    x=0;
    y=0;
    rectangle.setFillColor(Color::White);
    rectangle.setOutlineThickness(2);
    rectangle.setOutlineColor(sf::Color(250, 150, 100));
    rond,croix=false;

}


void Cellule::Print_cellule(sf::RenderWindow &window)
{
//Les coordonées du rectangle sont celles de la cellule
    rectangle.setPosition(getX(),getY());
    window.draw(rectangle);
} //Ce fera avec sfml , test en cours ...

//Accesseur en intérrogation





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


bool Cellule::Has_Croix() const {

return croix;

}


bool Cellule::Has_Rond() const {


return rond;

}

void Cellule::setRond(bool a) {

rond=a;

}



void Cellule::setCroix(bool a) {

croix=a;

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




void Cellule::set_rectangle(float i, float j)
{
//rectangle.setPosition(372, 270);
    rectangle.setPosition(i,j);
}


sf::FloatRect Cellule::get_entity()
{
// sf::Sprite::getGlobalBounds() : retourne la position et la dimension du sprite
    return rectangle.getGlobalBounds();
}



class Grille {

private :


Cellule Gri[NMAX][NMAX];

public :

Grille();
void printGrille(sf::RenderWindow &window);

void jouer(sf::RenderWindow &window,Event &);
int convertX (int);
int convertY (int);
int reverser(int);
int etat_jeu();
void draw_croix(int,int,RenderWindow&);
void draw_rond(int,int,RenderWindow&);
void IA_jouer(int profondeur,RenderWindow& window);
int Min(int profondeur,RenderWindow &, int, int);
int Max(int profondeur,RenderWindow &, int, int);
int* nb_series(int n);
int eval();
int gagnant();
};







float v = 45;
float w = 40;



Grille::Grille(){
    for (int i=0; i<NMAX; i++){
        for (int j=0 ; j<NMAX; j++){
            Gri[i][j].setX(v);
            Gri[i][j].setY(w);
            Gri[i][j].setCroix(false);
            Gri[i][j].setRond(false);
          Gri[i][j].set_rectangle(v,w);
            w+=40;
        }
        v+=40;
        w = 40;
    }
}

int Grille::reverser(int a){

return ((a <= 0 ) ? 60 : ((a==1) ? 95 : 135));


}

int Grille::convertX (int a) {

return ((a <= 80 ) ? 0 : a/60);


}

int Grille::convertY (int a) {

return ((a <= 80 ) ? 0 : a/60);


}

void Grille::printGrille(sf::RenderWindow &window){


 for (int i=0; i<NMAX; i++){
        for (int j=0 ; j<NMAX; j++){
        Gri[i][j].Print_cellule(window);
        }
    }
}

int nb_tours=0;

void Grille::draw_croix(int x,int y,RenderWindow & window) {

CircleShape croix1(12);
Texture txt1;
txt1.loadFromFile("cross.png");
croix1.setTexture(&txt1);
croix1.setPosition(x,y);
window.draw(croix1);
Gri[convertX(x)][convertY(y)].setCroix(true);
nb_tours++;





}

void Grille::draw_rond(int x,int y,RenderWindow& window) {


cout<<"ROND DRAWED "<<endl;

CircleShape croix1(12);
Texture txt1;
txt1.loadFromFile("noir.png");
croix1.setTexture(&txt1);
croix1.setPosition(x,y);
window.draw(croix1);
Gri[convertX(x)][convertY(y)].setRond(true);
nb_tours++;





}



void Grille::jouer(sf::RenderWindow &window,Event& a) {
int alpha=0, beta=0;

        int x=convertX(a.mouseButton.x);
        int y=convertY(a.mouseButton.y);
        cout<<a.mouseButton.x<<" "<<a.mouseButton.y<<endl;
        cout<<x<<" "<<y<<endl;

    if(!Gri[x][y].Has_Croix() && !Gri[x][y].Has_Rond() ) {


            if( nb_tours%2==0) {



        draw_croix(a.mouseButton.x-7,a.mouseButton.y-5,window);







        IA_jouer(9,window);


    }
             if(nb_tours>=5){
                int gagnant=etat_jeu();
                cout<<"gagnant:"<<gagnant<<endl;
                if (gagnant==1){
                    cout<<"La croix a gagné"<<endl;
                }
                if (gagnant==2){
                    cout<<"Le rond a gagné"<<endl;
                }
            }

            if(nb_tours==9){
                int gagnant=etat_jeu();
                if (gagnant==-1){
                cout<<"Match Nul"<<endl;
            }
            }
}
}


void Grille::IA_jouer(int profondeur,RenderWindow& window)
{

     int tmp;
     int i,j;
    int maxi=-1,maxj=-1;
    int alpha = -10000;
    int beta = 10000;


     for(i=0;i<3;i++)
     {
          for(j=0;j<3;j++)
          {
                if(!Gri[i][j].Has_Rond() && !Gri[i][j].Has_Croix())
                {



                      Gri[i][j].setRond(true);
                      tmp = Min(profondeur-1,window, alpha, beta);
                        if(alpha<tmp)
                        {

                        alpha = tmp;
                        maxi = i;
                        maxj = j;
                        }

                      Gri[i][j].setRond(false);
                }
          }
     }
     Gri[maxi][maxj].setRond(true);
    draw_rond(reverser(maxi),reverser(maxj),window);


}

//Juste après l'appel de IA_jouer , on appel draw_rond(maxi,maxi,window) , ne pas oublier de mettre maxi en globale

int Grille::Min(int profondeur,RenderWindow& window, int alpha, int beta)

{

     if(profondeur == 0 || gagnant() != 0)

     {

          return eval();

     }

     int i,j,tmp;


     for(i=0;i<3;i++)

     {

          for(j=0;j<3;j++)

          {

                if(!Gri[i][j].Has_Rond() && !Gri[i][j].Has_Croix())

                {

                      Gri[i][j].setCroix(true);

                      tmp = Max(profondeur-1, window, alpha, beta);

                      Gri[i][j].setCroix(false);
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

int Grille::Max(int profondeur,sf::RenderWindow &window, int alpha, int beta)

{


     if(profondeur == 0 || gagnant() != 0)

     {

          return eval();

     }

     int i,j,tmp;


     for(i=0;i<3;i++)

     {

          for(j=0;j<3;j++)

          {

                if(!Gri[i][j].Has_Rond() && !Gri[i][j].Has_Croix())

                {

                      Gri[i][j].setRond(true);

                      tmp = Min(profondeur-1,window, alpha,beta);

                      Gri[i][j].setRond(false);
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



int* Grille::nb_series(int n) //Compte le nombre de séries de n pions alignés de chacun des joueurs
{
     int compteur1, compteur2, i, j,j1=0,j2=0;

     int series[3];

     compteur1 = 0;
     compteur2 = 0;

      //Diagonale descendante
     for(i=0;i<3;i++)
     {
          if(Gri[i][i].Has_Rond())
          {
               compteur1++;
               compteur2 = 0;

               if(compteur1 == n)
               {
                    j1++;
               }
          }
          else if(Gri[i][i].Has_Croix())
          {
               compteur2++;
               compteur1 = 0;

               if(compteur2 == n)
               {
                     j2++;
               }
          }
     }

     compteur1 = 0;
     compteur2 = 0;

     //Diagonale montante
     for(i=0;i<3;i++)
     {
          if(Gri[i][2-i].Has_Rond())
          {
               compteur1++;
               compteur2 = 0;

               if(compteur1 == n)
               {
                    j1++;
               }
          }
          else if(Gri[i][2-i].Has_Croix())
          {
               compteur2++;
               compteur1 = 0;

               if(compteur2 == n)
               {
                     j2++;
               }
          }
     }

     //En ligne
     for(i=0;i<3;i++)
     {
          compteur1 = 0;
          compteur2 = 0;

          //Horizontalement
          for(j=0;j<3;j++)
          {
               if(Gri[i][j].Has_Rond())
               {
                    compteur1++;
                    compteur2 = 0;

                    if(compteur1 == n)
                    {
                         j1++;
                    }
               }
               else if(Gri[i][j].Has_Croix())
               {
                    compteur2++;
                    compteur1 = 0;

                    if(compteur2 == n)
                    {
                         j2++;
                    }
               }
          }

          compteur1 = 0;
          compteur2 = 0;

          //Verticalement
          for(j=0;j<3;j++)
          {
               if(Gri[j][i].Has_Rond())
               {
                    compteur1++;
                    compteur2 = 0;

                    if(compteur1 == n)
                    {
                         j1++;
                    }
               }
               else if(Gri[j][i].Has_Croix())
               {
                    compteur2++;
                    compteur1 = 0;

                    if(compteur2 == n)
                    {
                         j2++;
                    }
               }
          }
     }
     series[0]=j1;
     series[1]=j2;
     return series;
}


int Grille::eval()
{
     int vainqueur=gagnant(),nb_de_pions = 0;
     int i,j;

     //On compte le nombre de pions présents sur le plateau
     for(i=0;i<3;i++)
     {
          for(j=0;j<3;j++)
          {
               if(Gri[i][j].Has_Rond() || Gri[i][j].Has_Croix())
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

     series=nb_series(2);
     int series1=series[0];
     int series2=series[1];

     return series1 - series2;

}




int Grille::gagnant()
{
     int* T;
     T=nb_series(3);
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
          for(i=0;i<3;i++)
          {
               for(j=0;j<3;j++)
               {
                    if(!Gri[i][j].Has_Rond() && !Gri[i][j].Has_Croix())
                    {
                         return 0;
                    }
               }
          }
     }

     //Si le jeu est fini et que personne n'a gagné, on renvoie 3
     return 3;
}


int Grille::etat_jeu(){

int cpt=0;

int y=0; //Cordonnés y
for(int i=0;i<NMAX;i++) {

        if(Gri[i][y].Has_Croix()) {
            cpt++;
        }
}

if(cpt==3){return 1;}

cpt=0;

for(int i=0;i<NMAX;i++) {

        if(Gri[i][y].Has_Rond()) {
            cpt++;
        }
}

if(cpt==3){return 2;}

cpt=0;


for(int i=0;i<NMAX;i++) {

        if(Gri[i][y+1].Has_Rond()) {

            cpt++;
        }
}

if(cpt==3){return 2;}

cpt=0;


for(int i=0;i<NMAX;i++) {

        if(Gri[i][y+1].Has_Croix()) {

            cpt++;
        }
}

if(cpt==3){return 1;}

cpt=0;


for(int i=0;i<NMAX;i++) {

        if(Gri[i][y+2].Has_Croix()) {

            cpt++;
        }
}

if(cpt==3){return 1;}

cpt=0;


for(int i=0;i<NMAX;i++) {

        if(Gri[i][y+2].Has_Rond()) {

            cpt++;
        }
}

if(cpt==3){return 2;}

cpt=0;

int x=0; //Cordonnés x
for(int j=0;j<NMAX;j++) {

        if(Gri[x][j].Has_Croix()) {

            cpt++;
        }

}

if(cpt==3){return 1;}

cpt=0;

for(int j=0;j<NMAX;j++) {

        if(Gri[x][j].Has_Rond()) {

            cpt++;
        }


}

if(cpt==3){return 2;}

cpt=0;


for(int j=0;j<NMAX;j++) {

        if(Gri[x+1][j].Has_Rond()) {

            cpt++;
        }
}

if(cpt==3){return 2;}

cpt=0;


for(int j=0;j<NMAX;j++) {

        if(Gri[x+1][j].Has_Croix()) {

            cpt++;
        }
}

if(cpt==3){return 1;}

cpt=0;


for(int j=0;j<NMAX;j++) {

        if(Gri[x+2][j].Has_Croix()) {

            cpt++;
        }
}

if(cpt==3){return 1;}

cpt=0;


for(int j=0;j<NMAX;j++) {

        if(Gri[x+2][j].Has_Rond()) {

            cpt++;
        }
}

if(cpt==3){return 2;}

cpt=0;


for(int i=0;i<NMAX;i++){
    if(Gri[i][i].Has_Croix()){
        cpt++;
    }
}

if(cpt==3){return 1;}

cpt=0;


for(int i=0;i<NMAX;i++){
    if(Gri[i][i].Has_Rond()){
        cpt++;
    }
}

if(cpt==3){return 2;}

cpt=0;

int d=2;
for(int i=0;i<NMAX;i++){
    if(Gri[i][d-i].Has_Croix()){
        cpt++;
    }
}

if(cpt==3){return 1;}

cpt=0;

d=2;
for(int i=0;i<NMAX;i++){
    if(Gri[i][d-i].Has_Rond()){
        cpt++;
    }
}

if(cpt==3){return 2;}

return -1;

}




int main () {

Cellule B;



Grille A;
int a;
sf::RenderWindow win (VideoMode(200,200),"MORPION");
win.clear();
A.printGrille(win);

  while (win.isOpen())
        {
            Event event;
            while (win.pollEvent(event))
            {

              switch (event.type)
                    {
                case sf::Event::Closed:
                        {
                        win.close();
                        }
                case Event::MouseButtonPressed:

                A.jouer(win,event);


                    default:
                    break;
                    }
            }

            win.display();
        }




return 0;
cin>>a;
}

