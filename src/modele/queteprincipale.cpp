#include "queteprincipale.h"

const Heure TEMPS_ASSEMBLAGE(10);

bool QuetePrincipale::partiesBusReunies() const
{
    return m_partiesBusReunies;
}

std::map<ObjetQuetePrincipale*, int> QuetePrincipale::obtenirProgression() const
{
    return m_partiesBus;
}

void QuetePrincipale::calculerPartiesBusReunies()
{
    for (auto const &it : m_partiesBus)
    {
        if (it.second < m_nombrePartiesRequises.find(it.first->obtenirTypePartie())->second)
            return;
    }
    m_partiesBusReunies = true;
}

void QuetePrincipale::ajouterPartieBus(ObjetQuetePrincipale *partie_bus)
{
    auto it = m_partiesBus.find(partie_bus);
    if (it != m_partiesBus.end() && it->second < m_nombrePartiesRequises.find(partie_bus->obtenirTypePartie())->second )
    {
        it->second++;
        calculerPartiesBusReunies();
    }
}

QuetePrincipale::QuetePrincipale(std::string nom, std::string description)
    :
      m_nom{nom}, m_description{description},
      m_partiesBus{
        {new ObjetQuetePrincipale("Roue","",PartieBus::ROUE),0},
        {new ObjetQuetePrincipale("Moteur","",PartieBus::MOTEUR),0},
        {new ObjetQuetePrincipale("Essence","",PartieBus::ESSENCE),0},
        {new ObjetQuetePrincipale("Huile","",PartieBus::HUILE),0},
      },
      m_nombrePartiesRequises{
        {PartieBus::ROUE,6},
        {PartieBus::MOTEUR,1},
        {PartieBus::ESSENCE,1},
        {PartieBus::HUILE,2}
      },
      m_partiesBusReunies{false}

{

}

bool QuetePrincipale::obtenirFini() const
{
    return m_fini;
}

void QuetePrincipale::ajouterTravail(Equipe *equipe)
{
    //TODO
}
