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

std::string remplirAvecZero(double temps)
{
    std::string temps_affichable = std::to_string(static_cast<int>(temps));
    if (temps_affichable.size() < 2)
        temps_affichable.insert(0, "0");

    return temps_affichable;
}

const std::string Temps::obtenirTempsAffichable(Heure temps)
{
    double heures;
    double minutes = modf(temps.count(), &heures) * 60;

    std::string heures_affichables = remplirAvecZero(heures);
    std::string minutes_affichables = remplirAvecZero(minutes);

    return heures_affichables + "H" + minutes_affichables;
}


Heure Temps::obtenirTempsRestantJournee() const
{
    return m_heure_fin_journee - obtenirTemps();
}

//!
//! \brief donne l'heure actuelle de la journée pendant une quête
//! \author nlesne
//! \return l'heure actuelle de la journée (entre 8h et 18h)
//!

Heure Temps::obtenirTemps() const{
    return std::chrono::system_clock::now() - m_temps_debut_journee - m_duree_pause + Heure(8);
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

