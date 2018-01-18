#ifndef competence_h
#define competence_h

#include <string>
#include "utilitaires.h"

class Competence
{
private:
    unsigned short m_valeur;
    static const unsigned short M_VALEUR_MAX=20;
public:
    Competence();
    Competence(unsigned short valeur);
    void definirValeur(const unsigned short &valeur);
    unsigned short obtenirValeur() const;
    void augmenter(unsigned short valeur);
    unsigned short obtenirValeurMax() const;
    std::string serialiser() const;
    void charger(const std::string &donnees);
};

#endif
