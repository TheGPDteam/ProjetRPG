#include "cliquable.h"

Cliquable::Cliquable(Controleur * controleur, void* action, bool actif)
    : m_controleur{controleur}, m_actif{actif}, m_action{action}
{
}
