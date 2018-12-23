#include "cliquable.h"

Cliquable::Cliquable(Controleur * controleur,  /*std::function<void *>& action,*/ bool actif)
    : m_controleur{controleur}, m_actif{actif}//, m_action{action}
{
}

bool Cliquable::estCliquable() const
{
    return m_actif;
}

void Cliquable::definirCliquable(bool actif){
    m_actif = actif;
}

bool Cliquable::contient(std::pair<int, int> coord_souris) const {
    SDL_Rect z = zone();

    return (estCliquable() && coord_souris.first > z.x && coord_souris.first < z.x + z.w &&
            coord_souris.second > z.y && coord_souris.second < z.y + z.h);
}

