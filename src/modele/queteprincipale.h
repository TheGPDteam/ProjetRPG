#ifndef QUETEPRINCIPALE_H
#define QUETEPRINCIPALE_H

#include <map>
#include <string>
#include "objets/partiebus.h"
#include "survie/equipe.h"
#include "temps.h"

class QuetePrincipale
{
    static const Heure TEMPS_ASSEMBLAGE; //TODO méthodes liées à l'assemblage du bus.
private:
    std::string m_nom;
    std::string m_description;
    std::map<ObjetQuetePrincipale*,int> m_partiesBus;
    const std::map<PartieBus,int> m_nombrePartiesRequises;
    bool m_partiesBusReunies;
    bool m_fini;
    unsigned short m_avancement;

    void calculerPartiesBusReunies();
public:
    QuetePrincipale(std::string nom,std::string description);
    bool obtenirFini() const;
    bool partiesBusReunies() const;
    std::map<ObjetQuetePrincipale*, int> obtenirProgression() const;
    void ajouterPartieBus(ObjetQuetePrincipale* partieBus);
    void ajouterTravail(Equipe * equipe); //TODO
};

#endif // QUETEPRINCIPALE_H
