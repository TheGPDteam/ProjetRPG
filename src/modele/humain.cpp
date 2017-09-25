#include "humain.h"

//! \file fichier Humain
//! \date 17/11/16
//! \version 1.0


//!
//! \brief Donne un nom au personnage humain
//! \param nomFichier : le nom du fichier dans lequel sont enregistrés les noms
//! \return un string qui sera le nom du personnage
//!

std::string donnerNom(std::string nomFichier)
{
    srand(time(NULL));
    std::vector<std::string> noms;

    std::ifstream fichier(nomFichier.c_str(), std::ifstream::in);
    if(fichier.good()){
        std::string nom ;
        fichier >> nom;
        while (!fichier.eof())
        {
            noms.push_back(nom);
            fichier >> nom;
        }
        fichier.close();

        return noms[rand()%noms.size()];
    }
    return "unknown";
}

//! \brief constructeur de base
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//! Contient les attributs
//!

Humain::Humain()
    :m_coutEntretien{0},
      m_arme{new Arme()}
{
    m_chasse.definirValeur(rand()%m_chasse.obtenirValeurMax());
    m_recolte.definirValeur(rand()%m_recolte.obtenirValeurMax());
    m_niveau.definirNiveauActuel(1);
    int genre=rand()%2;

    if (genre==0)
    {
        m_prenom=donnerNom("./../rsc/identites/prenomsF.txt");
        m_genre=Genre::Femme;
    }
    else {
        m_prenom=donnerNom("./../rsc/identites/prenomsM.txt");
        m_genre=Genre::Homme;
    }

    m_nom=donnerNom("./../rsc/identites/noms.txt");
}

//!
//! \brief obtenir la competence chasse
//! \return la competence chasse
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//! Contient le return
//!

Competence Humain::obtenirChasse() const
{
    return m_chasse;
}

//!
//! \brief obtenir la competence recolte
//! \return la competence recolte
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//! Contient le return
//!

Competence Humain::obtenirRecolte() const
{
    return m_recolte;
}

//!
//! \brief obtenir le nom de l'humain
//! \return le nom
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//! Contient le return
//!

std::string Humain::obtenirNom() const
{
    return m_nom;
}

//!
//! \brief definir le nom de l'humain
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//! @param nom : nouveau nom de l'humin
//! Contient une affectation de variable
//!

void Humain::definirNom(std::string nom)
{
    m_nom=nom;
}

//!
//! \brief definir l'arme de l'humain
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//! @param une arme
//! Contient une affectation de variable
//!

void Humain::definirArme(Arme *arme)
{
    m_arme=arme;
}

//!
//! \brief obtenir une arme pour un humain
//! \return l'arme
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//! Contient le return
//!

Arme *Humain::obtenirArme() const
{
    return m_arme;
}

//!
//! \brief obtenir un entretien pour un humain
//! \return le cout de l'entretien
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//! Contient le return
//!

unsigned short Humain::obtenirEntretien() const
{
    return m_coutEntretien;
}

//!
//! \brief definir le cout de l'entretien de l'humain
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//! @param une valeur du cout d'entretien
//! Contient une affectation de variable
//!

void Humain::definirEntretien(unsigned short entretien)
{
    m_coutEntretien=entretien;
}

//!
//! \brief obtenir le niveau de l'humain
//! \return le niveau de l'humain
//! \author mleothaud
//! \date 16/11/2016
//! \version 1.0
//! Contient le return
//!

Niveau Humain::obtenirNiveau()
{
    return m_niveau;
}

//!
//! \brief Accesseur en lecture des dégâts
//! \return les dégâts de l'humain associés à la puissance de son arme
//! \author mleothaud
//! \date 17/11/2016
//! \version 1.0
//!

unsigned short Humain::obtenirDegats()
{
    return m_force.obtenirValeur() * m_arme->obtenirDegats();
}


//!
//! \brief Accesseur en lecture de la vitesse
//! \return la vitesse de l'humain associée à la vitesse de son arme
//! \author mleothaud
//! \date 17/11/2016
//! \version 1.0
//!

unsigned short Humain::obtenirVitesse()
{
    return m_vitesse.obtenirValeur() * m_arme->obtenirVitesse();
}

//!
//! \brief Augmentation de l'experience du niveau
//! \author mleothaud
//! \date 18/04/2017
//! \version 1.0
//!

void Humain::augmenterExperience(int exp)
{
    if (this->obtenirNiveau().ajouterExperience(exp))
    {
        this->m_chasse.augmenter(1);
        this->m_force.augmenter(1);
        this->m_intelligence.augmenter(1);
        this->m_recolte.augmenter(1);
        this->m_vie.definirValeurMax(this->m_vie.obtenirValeurMax()+1);
        this->m_vie.definirValeur(this->m_vie.obtenirValeurMax());
        this->m_vitesse.augmenter(1);
    }
}
