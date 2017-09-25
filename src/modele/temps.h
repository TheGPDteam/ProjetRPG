#ifndef temps_h
#define temps_h

#include <time.h>
#include <ctime>

class Temps
{
private:
    static const int DUREE_JOURNEE = 600;
    time_t m_tempsDebutjournee;
    time_t m_tempsPause;
public:

    Temps();
    int obtenirTempsRestant() const;
    void mettreEnPause();//TO-DO
    void reprendre();//TO-DO

    static int dureeJournee();
};

#endif
