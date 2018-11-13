#include "partiebus.h"


PartieBus::PartieBus(std::string nom, std::string description, TypePartieBus partie)
    :
      Objet (nom,description), m_partie{partie}
{
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
