#include "temps.h"
#include <ctime>

//! \file fichier temps
//! \date 17/11/16
//! \version 0.0.1

Temps::Temps()
    : m_tempsDureePause(0)
{
    m_tempsDebutjournee = time(nullptr);
    m_tempsPause = time(nullptr);
}

int Temps::obtenirTempsRestant() const
{
    return DUREE_JOURNEE-difftime(time(nullptr), m_tempsDebutjournee+m_tempsDureePause);
}

void Temps::mettreEnPause()
{
    m_tempsPause = time(nullptr);
}

void Temps::reprendre()
{
    m_tempsDureePause += difftime(time(nullptr), m_tempsPause);
}

int Temps::dureeJournee()
{
    return DUREE_JOURNEE;
}

void Temps::reinitialiserTemps()
{
    m_tempsDureePause = 0;
}
