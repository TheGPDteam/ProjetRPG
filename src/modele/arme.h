#ifndef arme_h
#define arme_h

#include "objet.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Arme : public Objet
{
private:
    unsigned short m_degats;
    unsigned short m_vitesse;
    unsigned short m_chance;
    void affecterValeurs(std::string ligne);
public:
    Arme();
    Arme(unsigned short degats, std::string nom, std::string description);
    ~Arme() override = default;
    unsigned short obtenirDegats() const;
    void definirDegats(const int &degats);
    unsigned short obtenirVitesse();
    unsigned short obtenirChance();
    std::string serialiser() const override;
    void charger(std::vector<std::string> donnees);
    TypeObjet obtenirType() const override;
};

#endif
