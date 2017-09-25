#include "temps.h"
#include <ctime>

//! \file fichier temps
//! \date 17/11/16
//! \version 0.0.1

Temps::Temps()
{
    m_tempsDebutjournee = time(nullptr);
    m_tempsPause = time(nullptr);
}

int Temps::obtenirTempsRestant() const
{
    return difftime(time(nullptr), m_tempsDebutjournee);
}

void Temps::mettreEnPause()
{

}

void Temps::reprendre()
{

}

int Temps::dureeJournee()
{
    return DUREE_JOURNEE;
}
