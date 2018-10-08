#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "Joueur.h"
using namespace sf;
using namespace std;



//Constucteur par défaut
Joueur::Joueur(): Id(0), Pseudo("Inconnu"),Nbp_j(60), Nb_tour(1), Score_j(0),couleurp_j(NOIR) {}

//Constructeur parametré avec choix id

Joueur::Joueur(int n): Id(n), Pseudo("Inconnu"), Nbp_j(60), Nb_tour(Id % 2 !=0 ? 0 : 1), Score_j(0), couleurp_j(Id % 2 !=0 ? BLANC: NOIR){}

//Constructeur parametré avec choix id et pseudo

Joueur::Joueur(unsigned int id, string n): Id(id), Pseudo(n), Nbp_j(60), Nb_tour(Id % 2 !=0 ? 0 : 1), Score_j(0), couleurp_j(Id % 2 !=0 ? BLANC: NOIR){}

//Accesseur en lecture du pseudo du joueur

string Joueur::GetPseudo(){return Pseudo;}

//Accesseur en écriture du nom du joueur

void Joueur::SetPseudo(std::string s){Pseudo=s;}


//Accesseur en lecture du score du joueur

unsigned int Joueur::GetScore_j()const {return Score_j; }

//Accesseur en écriture du score du joueur

void Joueur::SetScore(unsigned int s){Score_j=s;}


//Accesseur en lecture de la couleur du joueur

Joueur::Couleur Joueur::GetCouleur() const{return couleurp_j;}

//Accesseur en lecture du nombre de pions du joueur actuel

void Joueur::setCouleur(Joueur::Couleur c) {couleurp_j=c;}


unsigned int Joueur::GetNbp_j() const {return Nbp_j;}

//Accesseur en écriture du nombre de pions du joueur

void Joueur::SetNbp_j(unsigned int n) { Nbp_j=n;}

//Accesseur en lecture du nombre de tour actuel du joueur

unsigned int Joueur::GetNb_tour() const {return Nb_tour;}

//Accesseur en écriture du nombre de tour du joueur

void Joueur::SetNb_tour(unsigned int t){ Nb_tour=t;}

//Afficheur du score du joueur

void Joueur::Print_score(sf::RenderWindow& window){

    sf::Text textJ1;
    sf::Text textJ2;

    sf::Font font;
    if (!font.loadFromFile("black_jack.ttf")){}

    textJ1.setCharacterSize(30);
    textJ1.setColor(sf::Color::White);
    textJ1.setFont(font);
    textJ1.move(0,5);

    textJ2.setCharacterSize(30);
    textJ2.setColor(sf::Color::White);
    textJ2.setFont(font);
    textJ2.move(700, 5);

    if( Id % 2 ==0 ){
    textJ1.setString("Score "+Pseudo+": "+ intConvertString(GetScore_j()));
    }

    else{
    textJ2.setString("Score "+Pseudo+": "+ intConvertString(GetScore_j()));
    }

        if( Id % 2 ==0 ){

        window.draw(textJ1);

        }
        else{

        window.draw(textJ2);

        }

//En fin de partie, Affichage des scores finaux

//+ Si nouveaux record (Test avec la methode Meilleur_Score() ) de la part d'un des joueurs une fenetre affichant Nouveau Record ! avec son score

}

void Joueur::Enregistrer_Score(){
    ofstream PartieP("partie_prec.txt", ios::app);
            if (PartieP.is_open())
            {
                PartieP << Pseudo << "\n" << Score_j <<"\n";

                PartieP.close();
            }
    }

//Calcule le meilleur Score réalisé du jeu

unsigned int Joueur::Meilleur_Score(){

    unsigned int ScoreA = Score_j;
    unsigned int HS1,HS2,HS3;

//insere les 3 meilleurs scores realisé précedemment dans 3 variables HS1,HS2 et HS3
    ifstream MeilleurScore("scores.txt", ios::in);
    if( MeilleurScore.is_open())
    {
        MeilleurScore >> HS1 >> HS2 >> HS3 ;
        MeilleurScore.close();
    }

//On attribue le meilleur des 3 scores à la variable meilleur score

    unsigned int meilleurScore=HS1;

//On compare les 3 meilleurs scores avec le score réalisé durant la partie par le joueur actuel
//Réalise des échanges si le score du joueur est superieur à ceux deja enregistres

    if ((ScoreA == HS1 && ScoreA == HS2 && ScoreA == HS3) || ScoreA <= HS3){
        return meilleurScore;
    }

    else{
        if(ScoreA > HS3){
            if(ScoreA <= HS2){
                    HS3=ScoreA;
            }
            if(ScoreA >= HS2){
                HS3=HS2;
                if(ScoreA > HS1){
                    HS2=HS1;
                    HS1=ScoreA;
                    meilleurScore=HS1;
                }
                else{
                    HS2=ScoreA;
                }
            }
        }

//Modifie le fichier score.txt avec les nouvelles valeurs de meilleurs score

        ofstream MeilleurScore("scores.txt");
            if (MeilleurScore.is_open())
            {
                MeilleurScore << HS1 << "\n" << HS2 <<"\n" << HS3;

                MeilleurScore.close();
            }
    }

    return meilleurScore;
}

//Permet à l'utilisateur d'entrer son pseudo

void Joueur::Entrer_Pseudo(){


 sf::RenderWindow window(sf::VideoMode(800,200), "RENJU!");
    window.clear();
    sf::Texture texture;
    if (!texture.loadFromFile("woodlight.jpg")){}

    sf::Sprite sprite(texture);

    sf::Font font;

    sf::String PseudA;

    std::string PseudoE = "";

    if (!font.loadFromFile("black_jack.ttf"))
    {}

    sf::Text text,text1;

    text1.setFont(font);
    text1.setColor(sf::Color::White);
    text1.setCharacterSize(21);
    text1.move(30,20);

    if(Id % 2 == 0){
        text1.setString("ENTREZ LE NOM DU JOUEUR 1 : (APPUYEZ ENTREE POUR ARRETER LA SAISIE)");
    }
    else{
        text1.setString("ENTREZ LE NOM DU JOUEUR 2 : (APPUYEZ ENTREE POUR ARRETER LA SAISIE)");
    }

    text.setFont(font);
    text.setColor(sf::Color::Red);
    text.setCharacterSize(25);
    text.move(30,50);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type){

            case (sf::Event::Closed):
                window.close();
                break;

            //Insere la touche qui vient d'etre appuyer au pseudo et affiche la lettre à l'écran
            case (sf::Event::TextEntered) :
                PseudA = PseudA + event.text.unicode;
                PseudoE = PseudA;
                text.setString(PseudA);
                break;


            case (sf::Event::KeyPressed):
                switch(event.key.code)
                    {
                    //Permet d'effacer le dernier caractère entré
                    case(sf::Keyboard::BackSpace):
                    PseudoE.erase(PseudoE.length(),1);
                    PseudA.erase(PseudoE.length()-1,1);
                    break;

                    //Arrete la saisie du pseudo et enregistre le pseudo entré du joueur
                    case(sf::Keyboard::Return):
                    Pseudo=PseudoE;
                    window.close();
                    break;

                    default:
                    break;
                    }

             default:
                break;

        }
        }

        window.clear();
        window.draw(sprite);
        window.draw(text1);
        window.draw(text);
        window.display();

     }

}


void Joueur::AjoutScore(){
    Score_j++;
}

//Décrémente le nombre de pion du joueur
void Joueur::Decremente(){
    if (Nbp_j>0){
        Nbp_j--;
        Nb_tour++;
    }
}



std::string intConvertString(int i) {
     std::ostringstream oss;
     oss << i;
     return oss.str();
}



