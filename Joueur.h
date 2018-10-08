#ifndef JOUEUR_H
#define JOUEUR_H
#include <SFML/Graphics.hpp>


class Joueur{


    public:
        enum Couleur{
            NOIR,
            BLANC,
            NB_COULEURS
            };

    private:
        unsigned int Id;
        std::string Pseudo;
        unsigned int Nbp_j;
        unsigned int Nb_tour;
        unsigned int Score_j;
        Couleur couleurp_j;

    public:
        Joueur();
        Joueur(int n);
        Joueur(unsigned int id, std::string n);
        std::string GetPseudo();
        unsigned int GetScore_j() const;
        unsigned int GetNbp_j() const;
        unsigned int GetNb_tour() const;
        Couleur GetCouleur() const;
        void SetPseudo(std::string);
        void SetNbp_j(unsigned int n);
        void SetScore(unsigned int s);
        void SetNb_tour(unsigned int t);
        void setCouleur(Joueur::Couleur);
        void AjoutScore();
        void Entrer_Pseudo();
        void Print_score(sf::RenderWindow &);
        void Enregistrer_Score();
        unsigned int Meilleur_Score();
        void Decremente();

};

std::string intConvertString(int i);

#endif
