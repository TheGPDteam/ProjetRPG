#include "niveau.h"

//! \file fichier niveau
//! \date 17/11/16
//! \version 1.0

//!
//! \brief constructeur de base
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//!

Niveau::Niveau()
    : m_niveauActuel{1},
      m_pointsExperienceActuels{0},
      m_pointsExperiencePourNiveauSuivant{100}
{

}

//!
//! \brief obtenir le niveau du joueur
//! \return le niveau actuel
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//!

int Niveau::obtenirNiveauActuel()
{
    return m_niveauActuel;
}

//! \brief obtenir le niveau max du joueur
//! \return le niveau max qu'il peut atteindre
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//!

int Niveau::obtenirNiveauMaxActuel() const
{
    return m_NIVEAUMAX;
}

//! \brief definir le niveau du joueur
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//! @param niveau : valeur du nouveau niveau
//! Contient une affectation de variable
//!

void Niveau::definirNiveauActuel(int niveau)
{
    m_niveauActuel=niveau;
}

//! \brief obtenir les points d'expérience
//! \return les points d'experience
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//!

int Niveau::obtenirPointsExperienceActuel() const
{
    return m_pointsExperienceActuels;
}

//! \brief obtenir les points d'expérience pour le prochain niveau
//! \return les points d'experience requis
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//!

int Niveau::obtenirPointsExperiencePourNiveauSuivant() const
{
    return m_pointsExperiencePourNiveauSuivant;
}

//! \brief ajouter de l'experience
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//! @param valeur : valeur d'experience à ajouter
//!
//! Verifie si le nombre d'experience a ajouter est suffisant pour passer au niveau superieur,
//! si oui on passe au niveau superieur et on affecte aux points d'experience actuels la valeur restante
//! si non on incremente les points d'experience de la valeur a ajouter
//!

bool Niveau::ajouterExperience(int valeur)
{
    if (valeur<m_pointsExperiencePourNiveauSuivant)
    {
        m_pointsExperienceActuels+=valeur;
        return false;
    }
    else
    {
        m_pointsExperienceActuels=valeur-m_pointsExperiencePourNiveauSuivant;
        niveauSuperieur();
        return true;
    }
}

//! \brief passage au niveau supérieur
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//! Incremente le niveau et donne aux points d'experience pour niveau suivant la valeur du niveau multipliee par 100.
//! Ainsi, pour le niveau 1 il faudra 100 points d'experience, 200 pour le niveau 2 et ainsi de suite
//!

void Niveau::niveauSuperieur()
{
    m_niveauActuel++;
    m_pointsExperiencePourNiveauSuivant=m_niveauActuel*100;
}

//! \brief serialise les attributs de la classe niveau
//! \author parMarius,nlesne
//! \date 19/10/17
//! \version 0.2
//!
std::string Niveau::serialiser() const{
    return "<Niveau>"
            "   <NiveauActuel>" + std::to_string(m_niveauActuel) + "</NiveauActuel>"
            "   <ExperienceActuelle>" + std::to_string(m_pointsExperienceActuels) + "</ExperienceActuelle>"
            "   <ExperiencePourNiveauSuivant>" + std::to_string(m_pointsExperiencePourNiveauSuivant) + "</ExperiencePourNiveauSuivant>"
            "</Niveau>";

}

//! \brief charger les attributs de la classe Niveau
//! \author parMarius,nlesne
//! \date 18/01/18
//! \version 1.0
//!

void Niveau::charger(const std::string &donnees)
{
    m_niveauActuel = std::stoi(obtenirSousChaineEntre2Predicats(donnees,"<NiveauActuel>","</NiveauActuel>"));
    m_pointsExperienceActuels = std::stoi(obtenirSousChaineEntre2Predicats(donnees,"<ExperienceActuelle>","</ExperienceActuelle>"));
    m_pointsExperiencePourNiveauSuivant = std::stoi(obtenirSousChaineEntre2Predicats(donnees,"<ExperiencePourNiveauSuivant>","</ExperiencePourNiveauSuivant>"));
}
