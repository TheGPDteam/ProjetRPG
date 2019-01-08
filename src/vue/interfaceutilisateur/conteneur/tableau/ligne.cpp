#include "ligne.h"

Ligne::Ligne(std::vector<Affichable *> donnees, Controleur * controleur, SDL_Rect rectangleLigne, int sombre, int idLigne, bool avecImage)
    : Affichable(rectangleLigne), Cliquable(controleur, /*action,*/ true), m_donnees(donnees), m_numCouleur(sombre), m_affichable(nullptr), m_idLigne(idLigne), m_possedeImage(avecImage)
{
    bool premiereColonne=true;

    for(Affichable *a: m_donnees) {
        this->creerCaseElement(a, premiereColonne);
        if (premiereColonne){
            premiereColonne=false;
        }
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
Ligne::creerCaseElement(Affichable* affichable, bool premiereColonne){
    SDL_Rect rect;
    if (premiereColonne && m_possedeImage)
        rect = creerRectImage();
    else
        rect = creerRectCase();

    this->m_cases.push_back(new Case(rect, affichable, m_controleur, m_cases.size()));
}

SDL_Rect
Ligne::creerRectCase(){
    return creerRectCase(this->m_cases.size());
}
//!
//! \brief cree Rectangle de la case
//! \author Lacoste Dorian, Anthony Regnies
//! \date 22/11/18
//! \return un rectangle de la case en fonction des autres cases
//!
SDL_Rect
Ligne::creerRectCase(int numCase){
    SDL_Rect recCase;
    int largeurCaseDefaut;
    if (m_possedeImage){
        largeurCaseDefaut=(this->m_rectangle.w-TAILLE_IMAGE)/(this->m_donnees.size()-1);
        recCase.x=this->m_rectangle.x + largeurCaseDefaut * (numCase-1) + TAILLE_IMAGE;
    }
    else {
        largeurCaseDefaut=(this->m_rectangle.w)/this->m_donnees.size();
        recCase.x=this->m_rectangle.x + largeurCaseDefaut * numCase;
    }
    recCase.y=this->m_rectangle.y;

    recCase.w= largeurCaseDefaut;
    recCase.h=this->m_rectangle.h;
    return recCase;
}

SDL_Rect Ligne::creerRectImage(){
    SDL_Rect recCase;
    recCase.y=this->m_rectangle.y;
    recCase.x=this->m_rectangle.x;
    recCase.w= TAILLE_IMAGE;
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
        couleurFond = SDL_MapRGB(surface->format, 200, 150, 50);
    }

    SDL_FillRect(surface, &m_rectangle,couleurFond);
    for (Case * c : m_cases)
    {
        c->afficher(surface);
    }
}

//!
//! \brief obtient la case a la position numCase dans la ligne
//! \param numCase le numero de la case a récuperer
//! \return la neme case de la ligne
//! \author Lacoste Dorian
//! \date 16/12/18
//!
Case *
Ligne::obtenirCase(int numCase) const{
    assert(numCase >=0 && numCase < (int)m_cases.size());
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
    SDL_Rect rect;
    for(int i =0 ; i<m_cases.size(); i++)
    {
        if(m_possedeImage && i==0 )
            rect = creerRectImage();
        else
            rect = creerRectCase(i);
        m_cases.at(i)->redimensionner(rect);
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
