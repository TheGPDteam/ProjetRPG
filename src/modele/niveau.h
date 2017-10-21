#ifndef NIVEAU_H
#define NIVEAU_H

#include <vector>
#include <string>

class Niveau
{
private:
    int m_niveauActuel;
    const static int m_NIVEAUMAX=20;
    int m_pointsExperienceActuels;
    int m_pointsExperiencePourNiveauSuivant;
public:
    Niveau();
    int obtenirNiveauActuel() ;
    int obtenirNiveauMaxActuel() const;
    void definirNiveauActuel(int niveau);
    int obtenirPointsExperienceActuel() const;
    int obtenirPointsExperiencePourNiveauSuivant() const;
    bool ajouterExperience(int valeur);
    void niveauSuperieur();
    std::vector<std::string> serialiser() const;
    void charger(std::vector<std::string> donnees);
};

#endif // NIVEAU_H
