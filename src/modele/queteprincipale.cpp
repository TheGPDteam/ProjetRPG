#include "queteprincipale.h"

bool QuetePrincipale::partiesBusReunies() const
{
    return m_partiesBusReunies;
}

std::map<PartieBus*, int> QuetePrincipale::obtenirProgression() const
{
    return m_partiesBus;
}

QuetePrincipale::QuetePrincipale(std::string nom, std::string description)
    :
      m_nom{nom}, m_description{description}
{
}

bool QuetePrincipale::obtenirFini() const
{
    return m_fini;
}
