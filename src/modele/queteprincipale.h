#ifndef QUETEPRINCIPALE_H
#define QUETEPRINCIPALE_H

#include <map>
#include <string>
#include "objets/partiebus.h"
#include "survie/equipe.h"

class QuetePrincipale
{
    static const int TEMPS_ASSEMBLAGE = 1000; //TODO méthodes liées à l'assemblage du bus.
private:
    std::string m_nom;
    std::string m_description;
    std::map<PartieBus*,int> m_partiesBus;
    const std::map<TypePartieBus,int> m_nombrePartiesRequises;
    bool m_partiesBusReunies;
    bool m_fini;
    unsigned short m_avancement;

    void calculerPartiesBusReunies();
public:
    QuetePrincipale(std::string nom,std::string description);

    bool obtenirFini() const;
    bool partiesBusReunies() const;
    std::map<PartieBus*, int> obtenirProgression() const;
    void ajouterPartieBus(PartieBus* partieBus);
    bool ajouterTravail(Equipe * equipe); //TODO
};

#endif // QUETEPRINCIPALE_H
