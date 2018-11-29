#include "ligne.h"

Ligne::Ligne(std::vector<std::string> donnees, Controleur * controleur, SDL_Rect rectangleLigne)
    : Affichable(rectangleLigne), Cliquable(controleur, /*action,*/ true), m_donnees(donnees), m_affichable(nullptr)
{
    for(std::string d : m_donnees) {
        creerCaseString(d);
    }
}

void
Ligne::ajouterAffichable(Affichable *affichable){
    m_affichable= affichable;
    this->redimensionner(m_rectangle);
}

//!
//! \brief cree une case
//! \param donnee
//! \author Lacoste Dorian, Anthony Regnies
//! \date 22/11/18
//! cree une case a partir d'une donnee string
//!
void
Ligne::creerCaseString(std::string donnee){
    this->m_cases.push_back(new Case(creerRectCase(), donnee));
}
//!
//! \brief cree une case
//! \param affichable
//! \author Lacoste Dorian, Anthony Regnies
//! \date 22/11/18
//! cree une case  à partir d'une donnee Affichable
//!
void
Ligne::creerCaseElement(Affichable* affichable){
    this->m_cases.push_back(new Case(creerRectCase(), affichable));
}

//!
//! \brief cree Rectangle de la case
//! \author Lacoste Dorian, Anthony Regnies
//! \date 22/11/18
//! \return un rectangle de la case en fonction des autres cases
//!
SDL_Rect
Ligne::creerRectCase(){
    SDL_Rect recCase;
    int largeurCaseDefaut=this->m_rectangle.w/this->m_donnees.size();
    recCase.y=this->m_rectangle.y;
    recCase.x=this->m_rectangle.x + largeurCaseDefaut * this->m_cases.size();
    recCase.w= largeurCaseDefaut;
    recCase.h=this->m_rectangle.h;
    return recCase;
}

//!
//! \brief affiche la ligne
//! \param surface
//! \author Lacoste Dorian, Anthony Regnies
//! \date 22/11/18
//!
void Ligne::afficher(SDL_Surface *surface)
{
    for (Case * c : m_cases)
    {
        c->afficher(surface);
    }
}

//!
//! \brief redimmensionne une ligne
//! \param nouvelleDimension
//!\author Lacoste Dorian, Anthony Regnies
//! \date 22/11/18
//!
void Ligne::redimensionner(SDL_Rect nouvelleDimension)
{
    m_rectangle = nouvelleDimension;
    SDL_Rect rectCase = nouvelleDimension;
    int nouvelleLargeurCase=this->m_rectangle.w/this->m_donnees.size();
    if(m_affichable != nullptr)
        nouvelleLargeurCase=this->m_rectangle.w/(this->m_donnees.size()+1);
    rectCase.w = nouvelleLargeurCase;
    for (Case * c : m_cases)
    {
        c->redimensionner(rectCase);
        rectCase.x += nouvelleLargeurCase;
    }
}

void Ligne::clique() {
    //TODO
}

SDL_Rect Ligne::zone() const{
    return SDL_Rect();
}
