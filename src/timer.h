#ifndef TIMER_H
#define TIMER_H
#include "iostream"

class Timer
{
private:

    bool m_estLance;
    int m_nbJourMax;
    int m_nbJour;

public:
    Timer(int nbJourMax);
    bool estLance();
    void lancer();

    int nbJoursPasse();

    void incrementerNbJour();

    bool estFini();

    int obtenirNbJoursMax();
};

#endif // TIMER_H
