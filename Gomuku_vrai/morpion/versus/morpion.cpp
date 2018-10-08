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
int etat_jeu();

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

void Grille::jouer(sf::RenderWindow &window,Event& a) {



CircleShape croix1(12),rond1(12);
Texture txt1,txt2;
txt1.loadFromFile("cross.png");
txt2.loadFromFile("noir.png");

croix1.setTexture(&txt1);
rond1.setTexture(&txt2);



        int x=convertX(a.mouseButton.x);
        int y=convertY(a.mouseButton.y);
        cout<<x<<" "<<y<<endl;

    if(!Gri[x][y].Has_Croix() && !Gri[x][y].Has_Rond() ) {

        cout<<"IM IN BRO "<<endl;

            if( nb_tours%2==0) {

                    cout<<"IL FAUT DESSINER ICI CROIX"<<endl;

        croix1.setPosition(a.mouseButton.x-7,a.mouseButton.y-5);
        window.draw(croix1);
        Gri[x][y].setCroix(true);
        nb_tours++;
        cout<<nb_tours<<endl;

            }

            else {


           cout<<"IL FAUT DESSINER ICI ROND"<<endl;


      rond1.setPosition(a.mouseButton.x-7,a.mouseButton.y-5);
        window.draw(rond1);
        Gri[x][y].setRond(true);
        nb_tours++;
        cout<<nb_tours<<endl;

            }
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

