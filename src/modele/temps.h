#ifndef temps_h
#define temps_h


#include <string>
#include <chrono>


//!
//! \brief Classe Temps : représente le temps dans une journée.
//! \author ??? && nlesne
//! \date 23/10/19
//!

typedef std::chrono::duration<double, std::ratio<60>> Heure;

class Temps
{
private:
    constexpr static float HEURE_FIN_JOURNEE = 18.0;

    std::chrono::system_clock::time_point m_temps_debut_journee;
    std::chrono::system_clock::time_point m_temps_debut_pause;
    Heure m_duree_pause;
    Heure m_heure_fin_journee;
    bool m_en_pause;
public:
    Temps();
    static const std::string obtenirTempsAffichable(Heure temps);
    Heure obtenirTempsRestantJournee() const;
    Heure obtenirTemps() const;
    Heure obtenirDureeJournee();
    void mettreEnPause();
    void reprendre();

    void debuterJournee();
    void reinitialiserTemps();
};

#endif
