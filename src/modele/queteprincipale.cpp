#include "queteprincipale.h"

const Heure TEMPS_ASSEMBLAGE(10);
QuetePrincipale * QuetePrincipale::m_instance = nullptr;

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
        {PartieBus::ROUE,4},
        {PartieBus::MOTEUR,1},
        {PartieBus::ESSENCE,4},
        {PartieBus::HUILE,1}
      },
      m_partiesBusReunies{false}, m_tempsActuel {0}, m_faitAssemblage {false},
      m_timer{new Timer(TEMPS_ASSEMBLAGE)}

{

}

bool QuetePrincipale::obtenirEstLance() const
{
    return m_timer->estLance();
}
bool QuetePrincipale::obtenirFini() const
{
    return m_timer->estFini();
}

void QuetePrincipale::ajouterTravail(Equipe *equipe)
{
    //TODO
}

void QuetePrincipale::lancerQuetePrincipale()
{
    m_timer->lancer();
}

void QuetePrincipale::incrementerTempQuetePrincipale()
{
    if(m_timer->estLance())
    {
         m_timer->incrementerNbJour();
    }
}

QuetePrincipale* QuetePrincipale::obtenirInstance(){
    if(m_instance == nullptr)
    {
        m_instance = new QuetePrincipale("Quete importante", "La construction du bus");
    }
    return m_instance;
}

void QuetePrincipale::detruireQuetePrincipale()
{
    delete m_instance;
}
bool QuetePrincipale::estLance()
{
    m_timer->estLance();
}
