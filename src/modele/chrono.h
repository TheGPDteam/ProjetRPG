#ifndef CHRONO_H
#define CHRONO_H
#include <chrono>

class Chrono
{
private:
    std::chrono::system_clock::time_point m_tempsDebut;
    std::chrono::system_clock::time_point m_tempsActuel;

public:
    Chrono();
    Chrono(int tempsMaximal);

    bool estFini();


};

#endif // CHRONO_H
