#include "partiebus.h"


PartieBus::PartieBus(std::string nom, std::string description, TypePartieBus partie)
    :
      Objet (nom,description), m_partie{partie}
{
}

PartieBus::PartieBus() :
    Objet ("nom","description")

{
    int typePartie = rand()%4;
    this->definirDescription("Une partie du bus");
    switch (typePartie) {
    case 0:
        this->definirNom("Roue");
        this->m_partie = TypePartieBus::ROUE;
        break;
    case 1:
        this->definirNom("Essence");
        this->m_partie = TypePartieBus::ESSENCE;
        break;
    case 2:
        this->definirNom("Moteur");
        this->m_partie = TypePartieBus::MOTEUR;
        break;
    case 3:
        this->definirNom("Huile");
        this->m_partie = TypePartieBus::HUILE;
        break;
    }
}

TypeObjet PartieBus::obtenirType() const
{
    return TypeObjet::Partie_bus;
}

TypePartieBus PartieBus::obtenirTypePartie() const
{
    return m_partie;
}

bool PartieBus::operator==(PartieBus *obj)
{
    if (this != obj)
        return false;
    return m_partie == obj->m_partie;
}

bool PartieBus::operator>(PartieBus *obj)
{
    if (this < obj)
        return false;
    return m_partie > obj->m_partie;
}
