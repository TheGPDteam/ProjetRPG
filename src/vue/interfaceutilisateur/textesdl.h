#ifndef TEXTESDL_H
#define TEXTESDL_H


#include <utility>
#include <string>
#include <iostream>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <map>
#include "../affichable.h"

class TexteSDL : public Affichable
{
private:
    SDL_Surface* m_texte;
    std::string m_texteStr;
    SDL_Color m_couleurTexte;

    static std::map<int, TTF_Font *> m_fonts;
    TTF_Font* m_policeTexte;
    SDL_Rect m_positionTexte;

public:
    static constexpr SDL_Color COULEUR_BLANC{255,255,255, 255};

    TexteSDL(const std::string texte, const SDL_Color couleur_texte, const std::string chemin_police, const int taille_police,
             const std::pair<int, int> coord_rectangle, const std::pair<int, int> taille_rectangle);

    TexteSDL(const std::string texte, const SDL_Color couleur_texte, const std::string chemin_police, const int taille_police,
             const std::pair<int, int> coord_texte);

    void afficher(SDL_Surface *surface_affichage);

    void redimensionner(SDL_Rect nouvelleDimension);

    void mettreAJourTexte(std::string nouveauTexte);

    std::string getTexteStr() const;
    int getHauteurFont() const;

    ~TexteSDL();
};

#endif // TEXTESDL_H
