#ifndef vie_h
#define vie_h

//!
//! \brief Classe de gestion de la vie
//! \date 03/11/2016
//!

#include <vector>
#include <string>

class Vie
{
private:
    int m_valeur; /// Valeur de la vie
    int m_valeurMax; /// Valeur maximale de la Vie
public:
    Vie();
    Vie(int valeurMax);
    int obtenirValeur() const;
    int obtenirValeurMax() const;
    void definirValeur(int nouvelleValeur);
    void definirValeurMax(int nouvelleValeurMax);
    void diminuer(int valeur);
    void augmenter(int valeur);
    std::string serialiser()const;
    void charger(std::vector<std::string> donnees);
};

#endif
