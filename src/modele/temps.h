#ifndef temps_h
#define temps_h

#include <string>

#include <time.h>
#include <ctime>

class Temps
{
private:
    static const int DUREE_JOURNEE = 600;
    time_t m_tempsDebutjournee;
    time_t m_tempsDureePause;
    time_t m_tempsPause;

public:
    Temps();
    int obtenirTempsRestantJournee() const;
    int obtenirTemps() const;
    void mettreEnPause();
    void reprendre();

    void reinitialiserTemps();
    static int dureeJournee();
};

#endif
