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
	std::string m_nom;
	std::string m_description;
    void affecterValeurs(std::string ligne);
public:
    Arme();
    Arme(unsigned short degats, std::string nom, std::string description);
    unsigned short obtenirDegats() const;
    void definirDegats(const int &degats);
    unsigned short obtenirVitesse();
    unsigned short obtenirChance();
};

#endif
