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
    if (!lignesAliments.empty())
    {
        std::string ligneChoisie;
        int random_line =  rand()%(lignesAliments.size());
        ligneChoisie = lignesAliments[random_line];
        affecterValeurs(ligneChoisie);
    }
}

void Vivre::affecterValeurs(string ligne)
{
    string nom="";
    string valeurNutritive="";
    string description="";

    bool separateurNomPasse=false;
    bool separateurNutritivePasse=false;

    for (unsigned int i=0;i+1<=ligne.size();++i)
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
//! \return Une chaine contenant les données de la vivre au format XML
//! \author nlesne
//! \date 12/11/17
//! \version 0.2
//!

std::string Vivre::serialiser() const
{
    return "<Vivre>"
           "   <Nom>" + m_nom + "</Nom>"
                                "   <Description>" + m_description + "</Description>"
                                                                     "   <ValeurNutritive>" + std::to_string(m_valeurNutritive) + "</ValeurNutritive>"
                                                                                                                                  "</Vivre>";
}

TypeObjet Vivre::obtenirType() const {
    return TypeObjet::Vivre;
}

void Vivre::charger(const std::string &donnees)
{
    m_nom = obtenirSousChaineEntre2Predicats(donnees,"<Nom>","</Nom>");
    m_description = obtenirSousChaineEntre2Predicats(donnees,"<Description>","</Description>");
    m_valeurNutritive = std::stoi(obtenirSousChaineEntre2Predicats(donnees,"<ValeurNutritive>","</ValeurNutritive>"));
}
