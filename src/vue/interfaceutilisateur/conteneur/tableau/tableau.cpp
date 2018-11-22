#include "tableau.h"

Tableau::Tableau(SDL_Rect rect, float hauteur, float largeur, float hauteurLigne, Ligne *enTete, Controleur *controleur)
    :Affichable{rect}, m_hauteur{hauteur}, m_largeur{largeur}, m_hauteurLigne {hauteurLigne}, m_enTete{enTete}, m_controleur{controleur}
{
}

void Tableau::afficher(SDL_Surface *surface_affichage)
{
    m_enTete->afficher(surface_affichage);
    for (Ligne * l : m_lignes)
    {
        l->afficher(surface_affichage);
    }
}

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
//!
Ligne*
Tableau::ligneSurvole(std::pair<int, int> coord_souris){
    for(Ligne *l : m_lignes){
        if(l->contient(coord_souris))
            return l;
    }
 }

void
Tableau::ajouterElement(std::vector<Affichable*> affichables){

 }
//!
//! \brief Tableau::ajouterHumain
//! \param perso
//! \author Lacoste Dorian, Anthony Regnies
//! \date 22/11/18
//!
//!
void
Tableau::ajouterHumain(Humain* perso){
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

void
Tableau::ajouterObjet(Objet* obj){
    std::vector<std::string> tmp;
    tmp.insert(tmp.end(),obj->obtenirNom());
    tmp.insert(tmp.end(),obj->obtenirDescription());
    if(obj->obtenirType() == TypeObjet::Arme ) {
        Arme * arme = dynamic_cast<Arme *>(obj);
        tmp.insert(tmp.end(),std::to_string((int)arme->obtenirDegats()));
        tmp.insert(tmp.end(),std::to_string((int)arme->obtenirVitesse()));
        tmp.insert(tmp.end(),std::to_string((int)arme->obtenirChance()));
    }else if(obj->obtenirType() == TypeObjet::Vivre){
        Vivre * vivre = dynamic_cast<Vivre*>(obj);
        tmp.insert(tmp.end(),std::to_string(vivre->obtenirValeurNutritive()));
    }
    creerLigne(tmp);
}

void
Tableau::creerLigne(std::vector<std::string> donneesLigne){
    Ligne *l = new Ligne(donneesLigne, this->m_controleur, creerRectLigne());
    m_lignes.push_back(l);
}

SDL_Rect
Tableau::creerRectLigne(){
    SDL_Rect rectangleParLigne;
    rectangleParLigne.x=this->m_rectangle.x;
    rectangleParLigne.y=this->m_rectangle.y + this->m_hauteurLigne * m_lignes.size();
    rectangleParLigne.h= this->m_hauteurLigne;
    rectangleParLigne.w=this->m_rectangle.w;
}
