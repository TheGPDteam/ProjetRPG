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

    int nbJourRestant();

    void incrementerNbJour();

    bool estFini();
};

#endif // TIMER_H
