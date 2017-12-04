#ifndef statistique_h
#define statistique_h

#include <ctime>
#include <random>
#include <vector>
#include <string>

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
    std::string serialiser() const;
    void charger(std::vector<std::string> donnees);
};

#endif
