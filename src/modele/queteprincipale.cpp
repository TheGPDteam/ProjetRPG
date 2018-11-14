#include "queteprincipale.h"

bool QuetePrincipale::partiesBusReunies() const
{
    return m_partiesBusReunies;
}

std::map<PartieBus*, int> QuetePrincipale::obtenirProgression() const
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

void QuetePrincipale::ajouterPartieBus(PartieBus *partieBus)
{
    auto it = m_partiesBus.find(partieBus);
    if (it != m_partiesBus.end() && it->second < m_nombrePartiesRequises.find(partieBus->obtenirTypePartie())->second )
    {
        it->second++;
        calculerPartiesBusReunies();
    }
}

QuetePrincipale::QuetePrincipale(std::string nom, std::string description)
    :
      m_nom{nom}, m_description{description},
      m_partiesBus{
{new PartieBus("Roue","",TypePartieBus::ROUE),0},
{new PartieBus("Moteur","",TypePartieBus::MOTEUR),0},
{new PartieBus("Essence","",TypePartieBus::ESSENCE),0}},
      m_nombrePartiesRequises{
{TypePartieBus::ROUE,6},
{TypePartieBus::MOTEUR,1},
{TypePartieBus::ESSENCE,1}}
{
}

bool QuetePrincipale::obtenirFini() const
{
    return m_fini;
}
