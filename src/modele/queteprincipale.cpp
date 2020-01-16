#include "queteprincipale.h"

const Heure TEMPS_ASSEMBLAGE(10);
QuetePrincipale * QuetePrincipale::m_instance = nullptr;

bool QuetePrincipale::partiesBusReunies() const
{
    return m_partiesBusReunies;
}

std::map<PartieBus, int> QuetePrincipale::obtenirProgression() const
{
    return m_partiesBus;
}

void QuetePrincipale::calculerPartiesBusReunies()
{
    std::cout << "calcul partie bus" << std::endl;
    for (auto const &it : m_partiesBus)
    {
        std::cout << "partie bus : " << it.first << " nb = " << it.second << std::endl;
        if (it.second < m_nombrePartiesRequises.find(it.first)->second)
            return;
    }

    m_partiesBusReunies = true;
}

void QuetePrincipale::ajouterPartieBus(ObjetQuetePrincipale *partie_bus)
{
    std::cout << "mklkmlklmmklmklklmklmmkl" << std::endl;
    auto it = m_partiesBus.find(partie_bus->obtenirTypePartie());

    if (it != m_partiesBus.end()){
        std::cout << "oipoipopipoipoipopoiipoiopipoopipoipioiop" << std::endl;
        it->second++;
        calculerPartiesBusReunies();
    }
}

QuetePrincipale::QuetePrincipale(std::string nom, std::string description)
    :
      m_nom{nom}, m_description{description},
      m_partiesBus{
{PartieBus::ROUE,0},
{PartieBus::MOTEUR,0},
{PartieBus::ESSENCE,0},
{PartieBus::HUILE,0},
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
int QuetePrincipale::obtenirNbJoursRestants()
{
    return m_timer->obtenirNbJoursMax() - m_timer->nbJoursPasse();
}
