#ifndef QUETEPRINCIPALE_H
#define QUETEPRINCIPALE_H

#include <map>
#include <string>
#include "objets/partiebus.h"
#include "survie/equipe.h"
#include "temps.h"
#include "timer.h"

class QuetePrincipale
{

private:
    static const int TEMPS_ASSEMBLAGE = 1;

    int m_tempsActuel;

    std::string m_nom;
    std::string m_description;
    std::map<ObjetQuetePrincipale*,int> m_partiesBus;
    const std::map<PartieBus,int> m_nombrePartiesRequises;
    bool m_partiesBusReunies;
    bool m_faitAssemblage;

    unsigned short m_avancement;


    Timer* m_timer;

    void calculerPartiesBusReunies();

    static QuetePrincipale * m_instance;
    QuetePrincipale(std::string nom,std::string description);
public:
    bool obtenirEstLance() const;
    bool obtenirFini() const;
    bool partiesBusReunies() const;
    std::map<ObjetQuetePrincipale*, int> obtenirProgression() const;
    void ajouterPartieBus(ObjetQuetePrincipale* partieBus);
    void ajouterTravail(Equipe * equipe); //TODO
    void lancerQuetePrincipale();
    void incrementerTempQuetePrincipale();
    bool estLance();
    int obtenirNbJoursRestants();
//    void mettreAjour

    static QuetePrincipale* obtenirInstance();
    static void detruireQuetePrincipale();


};

#endif // QUETEPRINCIPALE_H
