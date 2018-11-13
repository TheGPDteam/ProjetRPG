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
      m_nom{nom}, m_description{description}, m_avancement{0}
{
    m_partiesBus.insert(std::make_pair(new PartieBus("Roue", "Pour rouler",TypePartieBus::ROUE),0));
    m_partiesBus.insert(std::make_pair(new PartieBus("Essence", "Pour carburer",TypePartieBus::ESSENCE),0));
    m_partiesBus.insert(std::make_pair(new PartieBus("Moteur", "Eh comment tu veux avancer sans ça ?",TypePartieBus::MOTEUR),0));
}

bool QuetePrincipale::obtenirFini() const
{
    return m_fini;
}


void QuetePrincipale::ajouterPartieBus(PartieBus *partieBus)
{
    m_partiesBus.at(partieBus) += 1;
    //A verifier si on a toutes les parties, dans ce cas on passe le booléen à true
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
    if (m_avancement >= 100)
    {
        m_fini = true;
    }
    return m_fini;
}
