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
public:
    Joueur();
    Joueur(const Quete &quete);
    Joueur(Quete quete, std::string nom);
    ~Joueur();

    std::pair<int,int> obtenirPosition() const;
    std::string obtenirNom() const;
    void definirPosition(std::pair<int,int> nouvellePosition);
    void deplacerJoueur(Direction dir);
    void definirNom(std::string nom );
    Humain* obtenirPersonnageJoueur();
    Equipe* obtenirEquipe() const;
    void definirEquipe(Equipe* equipe);
    void nouvelleQuete(Quete quete);
    Inventaire* obtenirInventaireJoueur();
    Quete* obtenirQuete();
    std::string serialiser() const;
    void charger(const std::string &donnees);
};

#endif
