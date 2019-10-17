#include "humain.h"

//! \file fichier Humain
//! \date 17/11/16
//! \version 1.0


//!
//! \brief Donne un nom au personnage humain
//! \param nomFichier : le nom du fichier dans lequel sont enregistrés les noms
//! \return un string qui sera le nom du personnage
//!

std::string donnerNom(std::string nom_fichiers)
{
    std::vector<std::string> noms;

    std::ifstream fichier(nom_fichiers.c_str(), std::ifstream::in);
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
      m_arme{new Arme()}, m_consommation{30}
{
    m_chasse.definirValeur((rand()%m_chasse.obtenirValeurMax())+1);
    m_recolte.definirValeur((rand()%m_recolte.obtenirValeurMax())+1);
    m_campement.definirValeur((rand()%m_campement.obtenirValeurMax())+1);
    m_force.definirValeur((rand()%m_force.obtenirValeurMax())+1);
    m_intelligence.definirValeur((rand()%m_intelligence.obtenirValeurMax())+1);
    m_vitesse.definirValeur((rand()%m_vitesse.obtenirValeurMax())+1);

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
//! \brief obtenir la competence campement
//! \return la competence campement
//! \author mpin & lgbarrere
//! \date 12/11/2018
//! \version 1.0
//! Contient le return
//!

Competence Humain::obtenirCampement() const
{
    return m_campement;
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
//! \brief obtenir le prenom de l'humain
//! \return le prenom
//! \author mleothaud
//! \date 13/01/2018
//! \version 1.0
//! Contient le return
//!

std::string Humain::obtenirPrenom() const
{
    return m_prenom;
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
//! \brief Accesseur en lecture des dégâts + coups critiques
//! \return les dégâts de l'humain associés à la puissance de son arme + le coup critique
//! \author mleothaud, mpardo
//! \date 17/11/2016 - 26/10/2017
//! \version 2.0
//!

unsigned short Humain::obtenirDegats()
{
    bool coupCritique = (rand() % 100) < ((m_CHANCE_CC_BASE + (2) * (m_intelligence.obtenirValeur())) * m_arme->obtenirChance());
    if(coupCritique){
        return m_force.obtenirValeur() * 1.5;
    }
    else{
        return m_force.obtenirValeur();
    }
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
        this->m_campement.augmenter(1);
        this->m_intelligence.augmenter(1);
        this->m_recolte.augmenter(1);
        this->m_vie.definirValeurMax(this->m_vie.obtenirValeurMax()+1);
        this->m_vie.definirValeur(this->m_vie.obtenirValeurMax());
        this->m_vitesse.augmenter(1);
    }
}

//!
//! \brief Retourne la consommation d'un humain
//! \return Consommation d'un humain
//! \author adeguilhem
//! \date 20/11/2017
//! \version 1.0
//!
int Humain::obtenirConsommation() const
{
    return m_consommation;
}

//!
//! \brief Serialise la classe Humain
//! \return Chaine contenant les données de l'objet
//! \author nlesne
//! \date 13/11/17
//! \version 0.2
//!

std::string Humain::serialiser() const
{
    std::string genre;
    if (m_genre == Genre::Homme)
        genre = "Homme";
    else if (m_genre == Genre::Femme)
        genre = "Femme";
    else
        genre = "Inconnu";

    return "<Humain>"
            "   <Nom>" + m_nom + "</Nom>"
            "   <Prenom>" + m_prenom + "</Prenom>"
            "   <Genre>" + genre + "</Genre>"
            + m_vie.serialiser()
            +
            "   <Force>"
            + m_force.serialiser()
            +
            "   </Force>"
            "   <Intelligence>"
            + m_intelligence.serialiser()
            +
            "   </Intelligence>"
            "   <Vitesse>"
            + m_vitesse.serialiser()
            +
            "   </Vitesse>"
            + m_vie.serialiser()
            +
            "   <CompetenceChasse>"
            + m_chasse.serialiser()
            +
            "  </CompetenceChasse>"
            "   <CompetenceRecolte>"
            + m_recolte.serialiser()
            +
            "   </CompetenceRecolte>"
            "   <CompetenceCampement>"
            + m_campement.serialiser()
            +
            "  </CompetenceCampement>"
            "   <CoutEntretien>" + std::to_string(m_coutEntretien) + "</CoutEntretien>"
            + m_niveau.serialiser()
            + m_arme->serialiser()
            +
            "</Humain>";
}

void Humain::charger(const std::string &donnees)
{
    m_nom = obtenirSousChaineEntre2Predicats(donnees,"<Nom>","</Nom>");
    m_prenom = obtenirSousChaineEntre2Predicats(donnees,"<Prenom>","</Prenom>");

    std::string donneesGenre = obtenirSousChaineEntre2Predicats(donnees,"<Genre>","</Genre>");
    if (donneesGenre == "Homme")
        m_genre = Genre::Homme;
    else if (donneesGenre == "Femme")
        m_genre = Genre::Femme;
    else
        m_genre = Genre::Inconnu;


    m_force = Statistique();
    m_force.charger(obtenirSousChaineEntre2Predicats(donnees,"<Force>","</Force>"));

    m_intelligence = Statistique();
    m_intelligence.charger(obtenirSousChaineEntre2Predicats(donnees,"<Intelligence>","</Intelligence>"));

    m_vitesse = Statistique();
    m_vitesse.charger(obtenirSousChaineEntre2Predicats(donnees,"<Vitesse>","</Vitesse>"));

    m_chasse = Competence();
    m_chasse.charger(obtenirSousChaineEntre2Predicats(donnees,"<CompetenceChasse>","</CompetenceChasse>"));

    m_recolte = Competence();
    m_recolte.charger(obtenirSousChaineEntre2Predicats(donnees,"<CompetenceRecolte>","</CompetenceRecolte>"));

    m_campement = Competence();
    m_campement.charger(obtenirSousChaineEntre2Predicats(donnees,"<CompetenceCampement>","</CompetenceCampement>"));

    m_coutEntretien = std::stoi(obtenirSousChaineEntre2Predicats(donnees,"<CoutEntretien>","</CoutEntretien>"));

    m_niveau = Niveau();
    m_niveau.charger(obtenirSousChaineEntre2Predicats(donnees,"<Niveau>","</Niveau>"));

    m_arme = new Arme();
    m_arme->charger(obtenirSousChaineEntre2Predicats(donnees,"<Arme>","</Arme>"));
}

