#include "temps.h"
#include <math.h>
#include <iostream>
#include <sstream>

//! \file fichier temps
//! \date 17/11/16
//! \version 0.0.2

Temps::Temps()
    :
      m_duree_pause(0),
      m_heure_fin_journee(+HEURE_FIN_JOURNEE),
      m_en_pause(false)
{
}

//!
//! \brief Convertit un temps en une chaine pour l'affichage
//! \author nlesne
//! \param temps : temps actuel pendant la quête
//! \return Une chaîne contenant le temps sous format heures + H + minutes
//!

const std::string Temps::obtenirTempsAffichable(Temps::heure_quete temps)
{
    double heures;
    double minutes = modf(temps.count(), &heures) * 60;

    std::string heures_affichables = std::to_string(static_cast<int>(heures));
    if (heures_affichables.size() < 2)
        heures_affichables.insert(0, "0");

    std::string minutes_affichables = std::to_string(static_cast<int>(minutes));
    if (minutes_affichables.size() < 2)
        minutes_affichables.insert(0,"0");

    return heures_affichables + "H" + minutes_affichables;
}


Temps::heure_quete Temps::obtenirTempsRestantJournee() const
{
    return m_heure_fin_journee - obtenirTemps();
}

//!
//! \brief donne l'heure actuelle de la journée pendant une quête
//! \author nlesne
//! \return l'heure actuelle de la journée (entre 8h et 18h)
//!

Temps::heure_quete Temps::obtenirTemps() const{
    return std::chrono::system_clock::now() - m_temps_debut_journee - m_duree_pause + heure_quete(8);
}

void Temps::mettreEnPause()
{
    m_temps_debut_pause = std::chrono::system_clock::now();
    m_en_pause = true;
}

void Temps::reprendre()
{
    if (m_en_pause)
    {
        m_duree_pause += std::chrono::system_clock::now() - m_temps_debut_pause;
        m_temps_debut_pause = {};
        m_en_pause = false;
    }
}

void Temps::reinitialiserTemps()
{
    m_temps_debut_journee = std::chrono::system_clock::now();
    m_temps_debut_pause = {};
    m_duree_pause = m_duree_pause.zero();
}
