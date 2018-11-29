#include "tableau.h"

Tableau::Tableau(SDL_Rect rect, float hauteurLigne, Controleur *controleur)
    :Affichable{rect},m_hauteurLigne {hauteurLigne}, m_controleur{controleur}, m_nbLignes{0}
{
}


//!
//! \brief affiche le contenu du tableau
//! \param surface_affichage
//! \author Lacoste Dorian
//! \date 15/11/2018
//!
void Tableau::afficher(SDL_Surface *surface_affichage)
{
    m_enTete->afficher(surface_affichage);
    for (Ligne * l : m_lignes)
    {
        l->afficher(surface_affichage);
    }
}
//!
//! \brief redimensionne la tableau
//! \param nouvelleDimension
//! \author Lacoste Dorian, Regnies Anthony
//! \date 15/11/18
//!
void Tableau::redimensionner(SDL_Rect nouvelleDimension)
{
    m_rectangle = nouvelleDimension;
    SDL_Rect rectangleLigne = nouvelleDimension;
    rectangleLigne.h = rectangleLigne.h / m_lignes.size();
    for (Ligne * l : m_lignes)
    {
        l->redimensionner(rectangleLigne);
        rectangleLigne.y += m_hauteurLigne;
    }
}
//!
//! \brief indique la ligne survolé
//! \param coord_souris
//! \return la ligne survolé par la souris
//! \author Lacoste Dorian, Regnies Anthony
//! \date 22/11/18
//!
Ligne*
Tableau::ligneSurvole(std::pair<int, int> coord_souris){
    for(Ligne *l : m_lignes){
        if(l->contient(coord_souris))
            return l;
    }
}

void
Tableau::ajouterEnTeteHumain(){
    std::vector<std::string> tmp;
    tmp.push_back("Nom");
    tmp.push_back("Prénom");
    tmp.push_back("Chasse");
    tmp.push_back("Recolte");
    tmp.push_back("Campement");
    tmp.push_back("Arme");
    tmp.push_back("Niveau");
    m_enTete = new Ligne(tmp, m_controleur,creerRectLigne());
    m_nbLignes++;
}

void
Tableau::ajouterEnTeteObjet(){
    std::vector<std::string> tmp;
    tmp.push_back("Nom");
    tmp.push_back("Description");
//    if(typeObjet == TypeObjet::Arme ) {
//        tmp.push_back("Degats");
//        tmp.push_back("Vitesse");
//        tmp.push_back("Chance");
//    }else if(typeObjet == TypeObjet::Vivre){
//        tmp.push_back("ValeurNutritive");
//    }
m_enTete = new Ligne(tmp, m_controleur, creerRectLigne());
m_nbLignes++;
}


void
Tableau::ajouterElement(std::vector<Affichable*> affichables){

}
//!
//! \brief Ajouter un humain dans le tableau
//! \param perso
//! \author Lacoste Dorian, Anthony Regnies
//! \date 22/11/18
//!
//!
void
Tableau::ajouterHumain(Humain* perso){
    assert (m_enTete != nullptr); //l'entete doit etre defini avant d'ajouter des objets
    std::vector<std::string> tmp;
    tmp.insert(tmp.end(),perso->obtenirNom());
    tmp.insert(tmp.end(),perso->obtenirPrenom());
    tmp.insert(tmp.end(),std::to_string((int)perso->obtenirChasse().obtenirValeur()));
    tmp.insert(tmp.end(),std::to_string((int)perso->obtenirRecolte().obtenirValeur()));
    tmp.insert(tmp.end(),std::to_string((int)perso->obtenirCampement().obtenirValeur()));
    tmp.insert(tmp.end(),perso->obtenirArme()->obtenirNom());
    tmp.insert(tmp.end(),std::to_string((int)perso->obtenirNiveau().obtenirNiveauActuel()));
    creerLigne(tmp);
}

//!
//! \brief Ajouter un objet dans le tableau
//! \param obj
//! \author Lacoste Dorian
//! \date 15/11/2018
void
Tableau::ajouterObjet(Objet* obj){
    assert (m_enTete != nullptr); //l'entete doit etre defini avant d'ajouter des objets
    std::vector<std::string> tmp;
    tmp.insert(tmp.end(),obj->obtenirNom());
    tmp.insert(tmp.end(),obj->obtenirDescription());
//    if(obj->obtenirType() == TypeObjet::Arme ) {
//        Arme * arme = dynamic_cast<Arme *>(obj);
//        tmp.insert(tmp.end(),std::to_string((int)arme->obtenirDegats()));
//        tmp.insert(tmp.end(),std::to_string((int)arme->obtenirVitesse()));
//        tmp.insert(tmp.end(),std::to_string((int)arme->obtenirChance()));
//    }else if(obj->obtenirType() == TypeObjet::Vivre){
//        Vivre * vivre = dynamic_cast<Vivre*>(obj);
//        tmp.insert(tmp.end(),std::to_string(vivre->obtenirValeurNutritive()));
//    }
    creerLigne(tmp);
}
//!
//! \brief Créer une ligne
//! \param donneesLigne
//! \author Lacoste Dorian
//! \date 15/11/2018
void
Tableau::creerLigne(std::vector<std::string> donneesLigne){
    Ligne *l = new Ligne(donneesLigne, this->m_controleur, creerRectLigne());
    m_lignes.push_back(l);
    m_nbLignes++;
}

//!
//! \brief Créer le rectangle ou s'affichera la ligne
//! \return SDL_Rect : la rectangle de la ligne
//! \author Lacoste Dorian, Anthony Regnies
//! \date 22/11/18
//!
SDL_Rect
Tableau::creerRectLigne(){
    SDL_Rect rectangleParLigne = m_rectangle;
    rectangleParLigne.y=this->m_rectangle.y + this->m_hauteurLigne * m_nbLignes;
    rectangleParLigne.h= this->m_hauteurLigne;
    return rectangleParLigne;
}
