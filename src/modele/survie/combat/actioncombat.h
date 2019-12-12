#ifndef ACTIONCOMBAT_H
#define ACTIONCOMBAT_H

#include "typeactioncombat.h"
#include "../personnage.h"

class ActionCombat
{
private:
    TypeActionCombat m_typeAction;
    Personnage* m_source;
    Personnage* m_cible;
public:
    ActionCombat(TypeActionCombat typeAction, Personnage* source, Personnage* cible);
};

#endif // ACTIONCOMBAT_H
