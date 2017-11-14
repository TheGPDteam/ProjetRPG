#ifndef joueur_h
#define joueur_h

#include <utility>
#include <string>
#include "observable.h"
#include "humain.h"
#include "equipe.h"
#include "campement.h"
#include "inventaire.h"
#include "quete.h"
#include "direction.h"

class Joueur : public Observable
{
private:
    std::pair<int,int> m_position;
    std::string m_nom;
    Campement* m_camp;
    Equipe* m_equipe;
    Humain m_personnageJoueur;
    Quete m_queteJoueur;
    Inventaire* m_inventaireJoueur;
public:
    Joueur();
    Joueur(Quete quete);
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
};

#endif
