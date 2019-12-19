#include "timer.h"

Timer::Timer(int nbJourMax)
{
    m_nbJourMax = nbJourMax;
    m_nbJour = 0;
}

bool Timer::estLance()
{
    return m_estLance;
}
void Timer::lancer()
{
    m_estLance = true;
}

int Timer::nbJoursPasse()
{
    return m_nbJour;
}
void Timer::incrementerNbJour()
{
    ++m_nbJour;
}
bool Timer::estFini()
{
    return m_nbJour >= m_nbJourMax && m_estLance;
}
int Timer::obtenirNbJoursMax()
{
    return m_nbJourMax;
}