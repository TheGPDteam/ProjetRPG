#include "ligne.h"

Ligne::Ligne(std::vector<std::string> donnees, Controleur * controleur, SDL_Rect rectangleLigne)
    : Affichable(rectangleLigne), Cliquable(controleur, /*action,*/ true), m_donnees(donnees)
{
    for(std::string d : m_donnees) {
        creerCaseString(d);
    }
}

void
Ligne::creerCaseString(std::string donnee){
    this->m_cases.push_back(new Case(creerRectCase(), donnee));
}
void
Ligne::creerCaseElement(Affichable* affichable){
    this->m_cases.push_back(new Case(creerRectCase(), affichable));
}

SDL_Rect
Ligne::creerRectCase(){
    SDL_Rect recCase;
    int largeurCaseDefaut=this->m_rectangle.w/this->m_donnees.size();
    recCase.y=this->m_rectangle.y;
    recCase.x=this->m_rectangle.x + largeurCaseDefaut * this->m_cases.size();
    recCase.w= largeurCaseDefaut;
    recCase.h=this->m_rectangle.h;
}

void Ligne::afficher(SDL_Surface *surface)
{
    for (Case * c : m_cases)
    {
        c->afficher(surface);
    }
}

void Ligne::redimensionner(SDL_Rect nouvelleDimension)
{
    m_rectangle = nouvelleDimension;
    SDL_Rect rectCase = nouvelleDimension;
    int nouvelleLargeurCase=this->m_rectangle.w/this->m_donnees.size();
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
