#include "case.h"

//!
//! \brief Case
//! \param rect x, y, hauteur, largeur en pixel
//! \param donnee la donnee de la case
//!
Case::Case(SDL_Rect rect, Affichable * donnee)
    : Affichable(rect),
      m_donnee(donnee)
{
    redimensionner(rect);
}

//!
//! \brief Case
//! \param rect x, y, hauteur, largeur en pixel
//! \param donnee le texte de la case
//!
Case::Case(SDL_Rect rect, std::string * donnee)
    : Affichable(rect),
      m_donnee(new ZoneTexte(POLICE_COLLEGED, 12, std::make_pair(rect.x,rect.y), rect, donnee, SDL_Color{0,0,0,255}, COMPORTEMENT_TEXTE::REDIMENTIONNE, ALIGNEMENT_TEXTE::GAUCHE))
{
    redimensionner(rect);
}

//!
//! \brief Case::~Case
//!
Case::~Case()
{
    delete m_donnee;
}

//!
//! \brief Case::afficher
//! \param surface
//!
void Case::afficher(SDL_Surface *surface)
{
    m_donnee->afficher(surface);
}

//!
//! \brief Case::redimensionner redimmensione la donnee
//! \param m_rectangle
//!
void Case::redimensionner(SDL_Rect m_rectangle)
{
    m_donnee->redimensionner(m_rectangle);
}

//!
//! \brief Case::definirDonnee
//! \param donnee
//! Attention, la donnee precedente est efface
//!
void Case::definirDonnee(Affichable *donnee)
{
    delete m_donnee;
    m_donnee = donnee;
}

//!
//! \brief Case::obtenirDonnee
//! \return
//!
Affichable *Case::obtenirDonnee() const
{
    return m_donnee;
}
