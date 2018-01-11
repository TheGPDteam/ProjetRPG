#include "campement.h"

//! \file fichier campement
//! \date 17/11/16
//! \version 1.0

//!
//! \brief Constructeur par defaut de l'objet campement
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
//! Construit un objet de la classe campement en initialisant la quantite de vivres à 0
//!

Campement::Campement()
    :m_quantiteVivre{0}
{
}

//!
//! \brief Ajout d'un vivre au campement
//! \author mleothaud
//! \date 17/11/16
//! @param vivre : un vivre qui sera ajoute au stock des vivres
//! \version 1.0
//!
//! Ajout d'un vivre au stock du campement
//!

void Campement::ajouterVivre(Vivre vivre)
{
    Vivre *vivreBis = new Vivre(vivre);
    m_stockVivre.insert(m_stockVivre.begin(), vivreBis);
    m_quantiteVivre++;
}

//!
//! \brief Permet d'obtenir le nombre de vivres dans le campement
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return le nombre de vivres du campement
//!

unsigned short Campement::obtenirNbVivres() const
{
    return m_quantiteVivre;
}

//!
//! \brief Permet de consommer un Vivre
//! \author mleothaud
//! \date 17/11/16
//! @param nbVivresConsommes : Nombre de vivres que l'on doit consommer
//! \version 1.0
//!
//! Enleve les vivres du stock et decremente la quantite enregistree
//!

void Campement::consommerVivre(unsigned short nbVivresConsommes)
{
    for (int i=0; i<nbVivresConsommes;i++)
    {
        m_quantiteVivre--;
        m_stockVivre.erase(m_stockVivre.begin());
    }
}

//!
//! \brief Retourne la consommation totale de tous les humains du campement
//! \return Consommation totale du campement
//! \author adeguilhem
//! \date 20/11/16
//! \version 0.1
//!
int Campement::obtenirConsommation()
{
    int somme = 0;
    for (Personnage *p : m_equipeChasse.obtenirListePersonnage()) {
        Humain * h = (Humain *) p;
        somme += h->obtenirConsommation();
    }
    for (Personnage *p : m_equipeRecolte.obtenirListePersonnage()) {
        Humain * h = (Humain *) p;
        somme += h->obtenirConsommation();
    }
    for (Personnage *p : m_personnesNonAttribuees)
    {
        Humain * h = (Humain *) p;
        somme += h->obtenirConsommation();
    }
    return somme;
}

//!
//! \brief Permet d'ajouter une personne au campement et de l'integrer a une equipe
//! \author mleothaud
//! \date 17/11/16
//! @param perso : Personnage à integrer
//! @param equipe : Equipe dans laquelle integrer le personnage
//! \version 1.0
//!
//! Ajoute le personnage à l'equipe desiree
//!

void Campement::ajouterPersonne(Humain *perso, Equipe *equipe)
{
    equipe->ajouterPersonnage(perso);
}

//!
//! \brief Permet d'ajouter une personne au campement et de l'integrer a une equipe
//! \author mleothaud
//! \date 11/12/17
//! @param perso : Personnage à integrer
//! \version 1.0
//!
//! Ajoute le personnage dans le campement
//!

void Campement::ajouterPersonne(Humain *humain)
{
    m_personnesNonAttribuees.insert(humain);
}

//!
//! \brief Accesseur en lecture de l'equipe de chasse
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return l'equipe de chasse
//!

Equipe* Campement::obtenirChasse()
{
    return &m_equipeChasse;
}

//!
//! \brief Accesseur en lecture de l'equipe de recolte
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return l'equipe de recolte
//!

Equipe* Campement::obtenirRecolte()
{
    return &m_equipeRecolte;
}

//!
//! \brief Serialisation du campement
//! \author nlesne
//! \date 16/10/17
//! \version 0.1
//! \return les donnees du campement
//!

std::string Campement::serialiser() const
{
    std::string donnees_campement = "<Campement>\n"
                                    "   <QuantiteVivre>\n" + std::to_string(m_quantiteVivre) + "\n</QuantiteVivre>\n"
                                                                                               "   <StockVivre>\n";
    for (Vivre* v : m_stockVivre)
        donnees_campement += v->serialiser();
    donnees_campement += "\n</StockVivre>\n"
                         "   <EquipeRecolte>\n"
            + m_equipeRecolte.serialiser()
            + "\n</EquipeRecolte>\n"
              "   <EquipeChasse>\n"
            + m_equipeChasse.serialiser()
            + " \n</EquipeChasse>\n"
              " <PersonnesNonAttribuees>\n";
    for (Personnage* p : m_personnesNonAttribuees)
        donnees_campement += p->serialiser();
    donnees_campement += "\n</PersonnesNonAttribuees>\n"
                         "   \n</Campement>\n";

    return donnees_campement;
}

//!
//! \brief Accesseur en lecture / ecriture des personnages non attribués
//! \author mleothaud, adeguilhem
//! \date 06/11/17
//! \version 1.0
//!

std::set<Humain *> &Campement::obtenirNonAttribuees()
{
    return m_personnesNonAttribuees;
}

//!
//! \brief Chargement des attrubuts du campement
//! \author mpardo
//! \date 24/10/17
//! \version 1.0
//!

void Campement::charger(std::vector<std::string> donnees, std::vector<std::string> donnees_equipe_chasse, std::vector<std::string> donnees_equipe_recolte){
    //todo
}
