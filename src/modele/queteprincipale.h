#ifndef QUETEPRINCIPALE_H
#define QUETEPRINCIPALE_H

#include <map>
#include <string>
#include "objets/partiebus.h"
#include "survie/equipe.h"
#include "temps.h"

class QuetePrincipale
{

private:
    static const Heure TEMPS_ASSEMBLAGE; //TODO méthodes liées à l'assemblage du bus.

    int m_tempsActuel;

    std::string m_nom;
    std::string m_description;
    std::map<ObjetQuetePrincipale*,int> m_partiesBus;
    const std::map<PartieBus,int> m_nombrePartiesRequises;
    bool m_partiesBusReunies;
    bool m_fini;
    bool m_faitAssemblage;

    unsigned short m_avancement;

    bool m_estLance;

    void calculerPartiesBusReunies();

    static QuetePrincipale * m_instance;
    QuetePrincipale(std::string nom,std::string description);
public:
    bool obtenirEstLancer() const;
    bool obtenirFini() const;
    bool partiesBusReunies() const;
    std::map<ObjetQuetePrincipale*, int> obtenirProgression() const;
    void ajouterPartieBus(ObjetQuetePrincipale* partieBus);
    void ajouterTravail(Equipe * equipe); //TODO
    void lancerQuetePrincipale();

//    void mettreAjour

    static QuetePrincipale* obtenirInstance();
    static void detruireQuetePrincipale();


};

#endif // QUETEPRINCIPALE_H
