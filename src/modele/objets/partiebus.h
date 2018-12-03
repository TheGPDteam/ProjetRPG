#ifndef PARTIEBUS_H
#define PARTIEBUS_H

#include "objet.h"

enum TypePartieBus
{
    ROUE,
    ESSENCE,
    MOTEUR,
    HUILE
};

class PartieBus : public Objet
{
private:
    TypePartieBus m_partie;
public:
    PartieBus(std::string nom, std::string description, TypePartieBus partie);
    PartieBus();
    TypeObjet obtenirType() const;
    TypePartieBus obtenirTypePartie() const;
    bool operator==(PartieBus* obj);
    bool operator>(PartieBus* obj);

};

#endif // PARTIEBUS_H
