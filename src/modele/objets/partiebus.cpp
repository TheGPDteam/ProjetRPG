#include "partiebus.h"


ObjetQuetePrincipale::ObjetQuetePrincipale(std::string nom, std::string description, PartieBus partie)
    :
      Objet (nom,description), m_partie{partie}
{
}

ObjetQuetePrincipale::ObjetQuetePrincipale() :
    Objet ("nom","description")

{
    int typePartie = rand()%4;
    this->definirDescription("Une partie du bus");
    switch (typePartie) {
    case 0:
        this->definirNom("Roue");
        this->m_partie = PartieBus::ROUE;
        break;
    case 1:
        this->definirNom("Essence");
        this->m_partie = PartieBus::ESSENCE;
        break;
    case 2:
        this->definirNom("Moteur");
        this->m_partie = PartieBus::MOTEUR;
        break;
    case 3:
        this->definirNom("Huile");
        this->m_partie = PartieBus::HUILE;
        break;
    }
}

TypeObjet ObjetQuetePrincipale::obtenirType() const
{
    return TypeObjet::QuetePrincipale;
}

PartieBus ObjetQuetePrincipale::obtenirTypePartie() const
{
    return m_partie;
}

bool ObjetQuetePrincipale::operator==(ObjetQuetePrincipale *obj)
{
    if (this != obj)
        return false;
    return m_partie == obj->m_partie;
}

bool ObjetQuetePrincipale::operator>(ObjetQuetePrincipale *obj)
{
    if (this < obj)
        return false;
    return m_partie > obj->m_partie;
}
