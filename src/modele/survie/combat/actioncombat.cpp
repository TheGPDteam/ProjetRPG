#include "actioncombat.h"

ActionCombat::ActionCombat(TypeActionCombat typeAction, Personnage *source, Personnage *cible)
    : m_typeAction{typeAction}, m_source{source}, m_cible{cible}
{
}
