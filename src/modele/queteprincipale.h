#ifndef QUETEPRINCIPALE_H
#define QUETEPRINCIPALE_H

#include <map>
#include <string>
#include "objets/partiebus.h"
#include "survie/equipe.h"

class QuetePrincipale
{
private:
    std::string m_nom;
    std::string m_description;
    std::map<PartieBus*,int> m_partiesBus;
    bool m_partiesBusReunies;
    bool m_fini;
    unsigned short m_avancement;

public:
    QuetePrincipale(std::string nom,std::string description);

    bool obtenirFini() const;
    bool partiesBusReunies() const;
    std::map<PartieBus*, int> obtenirProgression() const;
    void ajouterPartieBus(PartieBus* partieBus);
    bool ajouterTravail(Equipe * equipe);
};

#endif // QUETEPRINCIPALE_H
