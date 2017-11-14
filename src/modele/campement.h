#ifndef campement_h
#define campement_h

#include "personnage.h"
#include "equipe.h"
#include "vivre.h"
#include <vector>
#include <string>

class Campement
{
private:
    unsigned short m_quantiteVivre;
    std::set <Vivre*> m_stockVivre;
    std::set <Personnage*> m_personnesNonAttribuees;
    Equipe m_equipeRecolte;
    Equipe m_equipeChasse;
public:
    Campement();

    void ajouterPersonne(Personnage *perso, Equipe *equipe);
    void ajouterVivre(Vivre vivre);
    unsigned short obtenirNbVivres() const;
    void consommerVivre(unsigned short nbVivresConsommes);

    std::set<Personnage*> obtenirNonAttribuees();

    Equipe* obtenirChasse();
    Equipe* obtenirRecolte();

    std::string serialiser() const;
    void charger(std::vector<std::string> donnees, std::vector<std::string> donnees_equipe_chasse, std::vector<std::string> donnees_equipe_recolte);
};

#endif
