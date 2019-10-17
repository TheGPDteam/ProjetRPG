#include "arme.h"

//! \file fichier arme
//! \date 17/11/16
//! \version 1.0

//!
//! \brief Constructeur parametre de l'objet Arme
//! \author mleothaud
//! \date 17/11/16
//! @param degats : degats que l'arme engrange en cas d'attaque
//! @param nom : nom de l'arme
//! @param description : description de l'arme
//! \version 1.0
//!
//! Construit un objet de la classe arme
//!

Arme::Arme(unsigned short degats, std::string nom, std::string description, int image_x, int image_y)
    :Objet{nom,description, image_x, image_y},
      m_degats{degats}
{
}

//!
//! \brief Constructeur par défaut d'une arme
//! \author mleothaud
//! \date 18/04/17
//! \version 1.0
//!
//! Construit un objet aléatoire de la classe arme
//! Cet objet est construit en fonction d'un fichier texte présent dans les ressources
//!

Arme::Arme()
    :Objet("","")
{
    std::vector<std::string> lignesArmes;

    std::ifstream fichier("./../rsc/objets/armes/armes.txt", std::ifstream::in);
    if(fichier.good())
    {
        std::string ligne;
        std::getline(fichier,ligne);
        while (!fichier.eof())
        {
            lignesArmes.push_back(ligne);
            std::getline(fichier,ligne);
        }
        fichier.close();
    }
    std::string ligneChoisie;
    ligneChoisie = lignesArmes[rand()%lignesArmes.size()];
    affecterValeurs(ligneChoisie);
}

//!
//! \brief Accesseur en lecture de l'attribut m_degats de l'arme
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return les degats que peut faire l'arme
//!

unsigned short Arme::obtenirDegats() const
{
    return m_degats;
}

//!
//! \brief Accesseur en ecriture de l'attribut m_degats de l'arme
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
//! Definit les degats que peut faire l'arme
//!

void Arme::definirDegats(const int &degats)
{
    m_degats=degats;
}


//!
//! \brief Cette fonction affecte les valeurs présentes dans le fichier des armes à l'objet instancié
//! \param ligne : la ligne du fichier que l'on a récupérée
//! \author mleothaud
//! \version 1.0
//!
//! Utilise les charactères et notamment les séparateurs que sont les '/' pour affecter des valeurs à l'objet
//!

void Arme::affecterValeurs(std::string ligne)
{
    std::string nom="";
    std::string valeurDegats="";
    std::string valeurVitesse="";
    std::string valeurChance="";
    std::string description="";
    std::string emplacementImageX="";
    std::string emplacementImageY="";

    bool separateurNomPasse=false;
    bool separateurDegatsPasse=false;
    bool separateurVitessePasse=false;
    bool separateurChancePasse=false;
    bool separateurDescriptionPasse=false;
    bool separateurEmplacementImageX=false;

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
        else if (!separateurDegatsPasse)
        {
            if(ligne[i]=='/')
            {
                separateurDegatsPasse=true;
            }
            else
            {
                valeurDegats+=ligne[i];
            }
        }
        else if (!separateurVitessePasse)
        {
            if(ligne[i]=='/')
            {
                separateurVitessePasse=true;
            }
            else
            {
                valeurVitesse+=ligne[i];
            }
        }
        else if (!separateurChancePasse)
        {
            if(ligne[i]=='/')
            {
                separateurChancePasse=true;
            }
            else
            {
                valeurChance+=ligne[i];
            }
        }
        else if (!separateurDescriptionPasse)
        {
            if(ligne[i]=='/')
            {
                separateurDescriptionPasse=true;
            }
            else
            {
                description+=ligne[i];
            }
        }
        else if (!separateurEmplacementImageX)
        {
            if(ligne[i]=='/')
            {
                separateurEmplacementImageX=true;
            }
            else
            {
                emplacementImageX+=ligne[i];
            }
        }
        else
        {
            emplacementImageY+=ligne[i];
        }
    }
    m_nom=nom;
    m_degats=std::stoi(valeurDegats);
    m_vitesse=std::stoi(valeurVitesse);
    m_chance=std::stoi(valeurChance);
    m_description=description;
    m_sprite->changementSprite(SDL_Rect{std::stoi(emplacementImageX)*64,std::stoi(emplacementImageY)*64,64,64});

}

//!
//! \brief Accesseur en lecture de la chance
//! \return la valeur de la chance de l'arme
//! \author mleothaud
//! \version 1.0
//!

unsigned short Arme::obtenirChance()
{
    return m_chance;
}

//!
//! \brief Accesseur en lecture de la vitesse
//! \return la valeur de la vitesse de l'arme
//! \author mleothaud
//! \version 1.0
//!

unsigned short Arme::obtenirVitesse()
{
    return m_vitesse;
}

//!
//! \brief Serialise les données des armes
//! \author nlesne
//! \date 16/10/17
//! \version 1.0
//! \return les données des armes
//!

std::string Arme::serialiser() const
{
    return "<Arme>"
           "    <Nom>" + m_nom + "</Nom>"
            "   <Description>" + m_description + "</Description>"
            "   <Degats>" + std::to_string(m_degats) + "</Degats>"
            "   <Vitesse>" + std::to_string(m_vitesse) + "</Vitesse>"
            "   <Chance>" + std::to_string(m_chance) + "</Chance>"
            "</Arme>";
}

TypeObjet Arme::obtenirType() const {
    return TypeObjet::Arme;
}

void Arme::charger(const std::string &donnees)
{
    m_nom = obtenirSousChaineEntre2Predicats(donnees,"<Nom>","</Nom>");
    m_description = obtenirSousChaineEntre2Predicats(donnees,"<Description>","</Description>");
    m_degats = std::stoi(obtenirSousChaineEntre2Predicats(donnees,"<Degats>","</Degats>"));
    m_vitesse = std::stoi(obtenirSousChaineEntre2Predicats(donnees,"<Vitesse>","</Vitesse>"));
    m_chance = std::stoi(obtenirSousChaineEntre2Predicats(donnees,"<Chance>","</Chance>"));
}
