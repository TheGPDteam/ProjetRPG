#ifndef SAISIR_H
#define SAISIR_H

#include <string>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "textesdl.h"
#include "./ressources/policetexte.h"
#include "../ecran/typeecran.h"

const int x_position = WIDTH_FENETRE_PRINCIPALE/2;
const int y_position = HEIGHT_FENETRE_PRINCIPALE/2;

const int TAILLE_NOM_MAX = 15;

class Saisir
{
private:
    std::string buffer;
    SDL_Rect m_rec;
    TexteSDL* m_bufferSDL;

public:
    Saisir();

    void afficher(SDL_Surface *fenetre_affichage);

    std::string obtenirBuffer();

    void setBuffer(std::string buffer);

    void ajouterChar(char *c);

    void enleverChar();

    void setbufferSDL();

    ~Saisir();
};

#endif // SAISIR_H
