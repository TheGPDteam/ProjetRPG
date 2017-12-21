#ifndef SAISIR_H
#define SAISIR_H

#include <string>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "textesdl.h"
#include "policetexte.h"

const int x_position = 360;
const int y_position = 200;

const int TAILLE_NOM_MAX = 15;

class Saisir
{
private:
    std::string buffer;
    TexteSDL* m_bufferSDL;
    SDL_Rect rec;

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
