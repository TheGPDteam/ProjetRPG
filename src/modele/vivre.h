#ifndef vivre_h
#define vivre_h

#include "objet.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Vivre: public Objet
{
private:
    int m_valeurNutritive;
    void chargerVivre(std::string nomFichier);
    void affecterValeurs(std::string ligne);
public:
    Vivre();
    Vivre(std::string nom, std::string description, int valeurNutritive);
    int obtenirValeurNutritive() const;
    void definirValeurNutritive(const int &valeurNutritive);
    std::string serialiser() const override;
};

#endif
