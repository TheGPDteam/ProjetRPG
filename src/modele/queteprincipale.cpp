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

void QuetePrincipale::ajouterPartieBus(PartieBus *partie_bus)
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
        {new PartieBus("Roue","",TypePartieBus::ROUE),0},
        {new PartieBus("Moteur","",TypePartieBus::MOTEUR),0},
        {new PartieBus("Essence","",TypePartieBus::ESSENCE),0},
        {new PartieBus("Huile","",TypePartieBus::HUILE),0},
      },
      m_nombrePartiesRequises{
        {TypePartieBus::ROUE,6},
        {TypePartieBus::MOTEUR,1},
        {TypePartieBus::ESSENCE,1},
        {TypePartieBus::HUILE,2}
      },
      m_partiesBusReunies{false}

{

}

bool QuetePrincipale::obtenirFini() const
{
    return m_fini;
}

bool QuetePrincipale::ajouterTravail(Equipe *equipe)
{
    if (m_partiesBusReunies)
    {
        for (Personnage *p : equipe->obtenirListePersonnage())
        {
            Humain * h = dynamic_cast<Humain *>(p);
            m_avancement += h->obtenirCampement().obtenirValeur();
        }
    }
    if (m_avancement >= TEMPS_ASSEMBLAGE)
    {
        m_fini = true;
    }
    return m_fini;
}
