#ifndef vivre_h
#define vivre_h

#include "../objets/objet.h"
#include "../abstrait/utilitaires.h"
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
    ~Vivre() override = default;
    int obtenirValeurNutritive() const;
    void definirValeurNutritive(const int &valeurNutritive);
    std::string serialiser() const override;
    TypeObjet obtenirType() const override;
    void charger(const std::string &donnees);
};

#endif
