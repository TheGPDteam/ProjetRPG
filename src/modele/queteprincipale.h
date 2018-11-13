#ifndef QUETEPRINCIPALE_H
#define QUETEPRINCIPALE_H

#include <map>
#include <string>
#include "objets/partiebus.h"

class QuetePrincipale
{
private:
    std::string m_nom;
    std::string m_description;
    std::map<PartieBus*,int> m_partiesBus;
    bool m_partiesBusReunies;
    bool m_fini;

public:
    QuetePrincipale(std::string nom,std::string description);

    bool obtenirFini() const;
    bool partiesBusReunies() const;
    std::map<PartieBus*, int> obtenirProgression() const;
    void ajouter_partie_bus(PartieBus* partie_bus); // TODO
};

#endif // QUETEPRINCIPALE_H
