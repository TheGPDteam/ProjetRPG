#include "ligne.h"

Ligne::Ligne(std::vector<Affichable *> donnees, Controleur * controleur, SDL_Rect rectangleLigne, int sombre, int idLigne)
    : Affichable(rectangleLigne), Cliquable(controleur, /*action,*/ true), m_donnees(donnees), m_affichable(nullptr), m_sombre(sombre), m_idLigne(idLigne)
{
    for(Affichable *a: m_donnees) {
        this->creerCaseElement(a);
    }
}


//!
//! \brief indique la case cliqué
//! \param coord_souris
//! \return la case cliqué par la souris ou nullptr
//! \author Lacoste Dorian
//! \date 13/12/18
//!
Case *
Ligne::caseClique(std::pair<int, int> coord_souris){
    for(Case *c : m_cases){
        if(c->contient(coord_souris)){
            return c;
        }
    }
    return nullptr;
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
    this->m_cases.push_back(new Case(creerRectCase(), affichable, m_controleur, m_cases.size()));
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
    Uint32 couleurFond = SDL_MapRGB(surface->format, 100, 100, 100);
    if(m_sombre == 1)
        couleurFond = SDL_MapRGB(surface->format, 200, 200, 200);
    else if (m_sombre == 2)
        couleurFond = SDL_MapRGB(surface->format, 170, 170, 170);


    SDL_FillRect(surface, &m_rectangle,couleurFond);
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
    return m_rectangle;
}
