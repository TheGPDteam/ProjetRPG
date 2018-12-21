#ifndef joueur_h
#define joueur_h

#include <utility>
#include <string>
#include "observable.h"
#include "./personnages/humain.h"
#include "./survie/equipe.h"
#include "./environnement/campement.h"
#include "./survie/inventaire.h"
#include "./survie/quetes/quete.h"
#include "direction.h"
#include "./utilitaires.h"
#include "queteprincipale.h"

class Joueur : public Observable
{
private:
    std::pair<int,int> m_position;
    Quete m_queteJoueur;
    std::string m_nom;
    //Campement* m_camp;
    Equipe* m_equipe;
    Humain m_personnageJoueur;
    Inventaire* m_inventaireJoueur;
    QuetePrincipale m_quetePrincipale;
public:
    Joueur(const Quete &quete);
    ~Joueur();

    std::pair<int,int> obtenirPosition() const;
    std::string obtenirNom() const;
    void definirPosition(std::pair<int,int> nouvellePosition);
    void deplacerJoueur(Direction dir);
    void definirNom(std::string nom );
    Humain* obtenirPersonnageJoueur();
    Equipe* obtenirEquipe() const;
    void definirEquipe(Equipe* equipe);
    void nouvelleQuete(TypeQuete tq, std::string nom, std::string description, int valeurObjectif, int recompenseExperience, Objet* recompense);//Quete quete);
    Inventaire* obtenirInventaireJoueur();
    Quete* obtenirQuete();
    std::string serialiser() const;
    void charger(const std::string &donnees);
    QuetePrincipale obtenirQuetePrincipale();
};

#endif
