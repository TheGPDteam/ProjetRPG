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
    Equipe* obtenirChasse();
    Equipe* obtenirRecolte();
    std::vector<std::string> serialiser() const;
};

#endif
