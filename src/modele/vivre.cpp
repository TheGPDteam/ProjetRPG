#include "vivre.h"

//! \file fichier vivre
//! \date 17/11/16
//! \version 1.0

using namespace std;

Vivre::Vivre(string nom, string description, int valeurNutritive)
    : Objet{nom,description},
      m_valeurNutritive{valeurNutritive}
{
}

Vivre::Vivre()
    : Objet{"",""},
      m_valeurNutritive{0}
{
    chargerVivre("./../rsc/objets/vivres/vivres.txt");
}

int Vivre::obtenirValeurNutritive() const
{
    return m_valeurNutritive;
}

void Vivre::definirValeurNutritive(const int &valeurNutritive)
{
    m_valeurNutritive = valeurNutritive;
}


void Vivre::chargerVivre(std::string nomFichier)
{
    //Lire dans le fichier vivre.txt
    srand(time(NULL));
    std::vector<std::string> lignesAliments;

    std::ifstream fichier(nomFichier.c_str(), std::ifstream::in);
    if(fichier.good())
    {
        std::string ligne;
        std::getline(fichier,ligne);
        while (!fichier.eof())
        {
            lignesAliments.push_back(ligne);
            std::getline(fichier,ligne);
        }
        fichier.close();
    }
    std::string ligneChoisie;
    ligneChoisie = lignesAliments[rand()%lignesAliments.size()];
    affecterValeurs(ligneChoisie);
}

void Vivre::affecterValeurs(string ligne)
{
    string nom="";
    string valeurNutritive="";
    string description="";

    bool separateurNomPasse=false;
    bool separateurNutritivePasse=false;

    for (int i=0;i<ligne.size();++i)
    {
        if (!separateurNomPasse)
        {
            if(ligne[i]=='/')
            {
                separateurNomPasse=true;
            }
            else
            {
                nom+=ligne[i];
            }
        }
        else if(!separateurNutritivePasse)
        {
            if (ligne[i]=='/')
            {
                separateurNutritivePasse=true;
            }
            else
            {
                valeurNutritive+=ligne[i];
            }
        }
        else
        {
            description+=ligne[i];
        }
    }
    m_nom=nom;
    m_valeurNutritive=std::stoi(valeurNutritive);
    m_description=description;
}

//!
//! \brief Sérialise les attributs de l'objet
//! \return un vecteur des attributs
//! \author nlesne
//! \date 16/10/17
//! \version 0.1
//!

std::vector<std::string> Vivre::serialiser() const
{
    std::vector<std::string> donnees_vivre {std::to_string(m_valeurNutritive)};
    return donnees_vivre;
}
