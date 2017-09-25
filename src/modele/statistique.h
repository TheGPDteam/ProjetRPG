#ifndef statistique_h
#define statistique_h

#include <ctime>
#include <random>

class Statistique
{
private:
    int m_statActuelle;
    const static int m_STATMAX=20;
public:
    Statistique();
    int obtenirValeur() const;
    int obtenirValeurMax() const;
    void definirValeur(int valeur);
    void augmenter(int valeur);
};

#endif
