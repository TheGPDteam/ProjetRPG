#include "ligne.h"

Ligne::Ligne(std::vector<Affichable *> donnees, Controleur * controleur, SDL_Rect rectangleLigne, int sombre, int idLigne)
    : Affichable(rectangleLigne), Cliquable(controleur, /*action,*/ true), m_donnees(donnees), m_affichable(nullptr), m_numCouleur(sombre), m_idLigne(idLigne)
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
    if(m_numCouleur == 1)
        couleurFond = SDL_MapRGB(surface->format, 200, 200, 200);
    else if (m_numCouleur == 2)
        couleurFond = SDL_MapRGB(surface->format, 170, 170, 170);
    else if (m_numCouleur == 3) {
        couleurFond = SDL_MapRGB(surface->format, 250, 250, 100);
    }


    SDL_FillRect(surface, &m_rectangle,couleurFond);
    for (Case * c : m_cases)
    {
        c->afficher(surface);
    }
}

//!
//! \brief obtient la case a la neme position dans la ligne
//! \param numCase le numero de la case a récuperer
//! \return la neme case de la ligne
//! \author Lacoste Dorian
//! \date 16/12/18
//!
Case *
Ligne::obtenirCase(int numCase) const{
    assert(numCase >=0 && numCase < m_cases.size());
    return m_cases.at(numCase);
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

//bool
//Ligne::operator< (const Ligne &otherLig) const{
//    int idCase=0;
//    ZoneTexte * zone1 = dynamic_cast<ZoneTexte * >(this->obtenirCase(idCase)->obtenirDonnee());
//    ZoneTexte * zone2 = dynamic_cast<ZoneTexte * >(otherLig.obtenirCase(idCase)->obtenirDonnee());
//    return (zone1->obtenirTexte() < zone2->obtenirTexte());
//}

void Ligne::definirNumCaseSelectionnerTri(int numCase){
    this->numCaseSelTri = numCase;
}

int Ligne::obtenirNumCaseSelectionnerTri(){
    return this->numCaseSelTri ;
}
void Ligne::definirNumCouleur(int sombre){
    this->m_numCouleur = sombre;
}

void Ligne::clique() {
    //TODO
}

SDL_Rect Ligne::zone() const{
    return m_rectangle;
}
