#ifndef temps_h
#define temps_h


#include <string>
#include <chrono>


//!
//! \brief Classe Temps : représente le temps dans une journée.
//! \author ??? && nlesne
//! \date 23/10/19
//!
class Temps
{
private:
    typedef std::chrono::duration<float, std::ratio<60>> heure_quete;
    static const int HEURE_FIN_JOURNEE = 18;

    std::chrono::system_clock::time_point m_temps_debut_journee;
    std::chrono::system_clock::time_point m_temps_debut_pause;
    heure_quete m_duree_pause;
    heure_quete m_heure_fin_journee;
    bool m_en_pause;
public:
    Temps();
    static const std::string obtenirTempsAffichable(heure_quete temps);
    heure_quete obtenirTempsRestantJournee() const;
    heure_quete obtenirTemps() const;
    heure_quete obtenirDureeJournee();
    void mettreEnPause();
    void reprendre();

    void debuterJournee();
    void reinitialiserTemps();
};

#endif
