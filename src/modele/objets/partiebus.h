#ifndef PARTIEBUS_H
#define PARTIEBUS_H

#include "objet.h"

enum PartieBus
{
    ROUE,
    ESSENCE,
    MOTEUR,
    HUILE
};

class ObjetQuetePrincipale : public Objet
{
private:
    PartieBus m_partie;
public:
    ObjetQuetePrincipale(std::string nom, std::string description, PartieBus partie);
    ObjetQuetePrincipale();
    TypeObjet obtenirType() const;
    PartieBus obtenirTypePartie() const;
    bool operator==(ObjetQuetePrincipale* obj);
    bool operator>(ObjetQuetePrincipale* obj);

};

#endif // PARTIEBUS_H
