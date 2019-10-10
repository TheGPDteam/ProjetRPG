#ifndef ZONEDEFILABLE_H
#define ZONEDEFILABLE_H

#include "affichable.h"
#include "cliquable.h"
#include "sprite.h"

class ZoneDefilable : public Cliquable, public Affichable
{
private:
    const float VITESSE_DEFILEMENT = 0.17;
    SDL_Rect m_fenetreGlissante;
    Affichable * m_contenu;
    SDL_Color m_couleur;
    Sprite * m_defilementBas;
    Sprite * m_defilementHaut;
    SDL_Rect posBarreDefilable;
    SDL_Rect zone() const override;
public:
    ZoneDefilable() = delete;
    ZoneDefilable(Affichable *contenu, SDL_Color couleur, Controleur * controleur, bool actif, SDL_Rect obtenirRectangle);
    virtual ~ZoneDefilable() override;
    void afficher(SDL_Surface *surface) override;
    void redimensionner(SDL_Rect obtenirRectangle) override;
    bool gestionEvenementDefilableClique(std::pair<int, int> &coord_souris);
    std::pair<int, int> coordSourisElement(std::pair<int, int> &coord_sourisEcran);
    void clique() override;
    void defiler(bool haut);
};

#endif // ZONEDEFILABLE_H
