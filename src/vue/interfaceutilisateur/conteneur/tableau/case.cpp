#include "case.h"

//!
//! \brief Case
//! \param rect x, y, hauteur, largeur en pixel
//! \param donnee la donnee de la case
//!
Case(SDL_Rect rect, Affichable * donnee)
    : Affichable(rect),
      donne(donnee)
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
    donnee->redimensionner(rect);
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
