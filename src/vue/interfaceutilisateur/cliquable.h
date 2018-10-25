#ifndef CLIQUABLE_H
#define CLIQUABLE_H

#include <string>
#include "controleur/controleur.h"
#include <SDL/SDL.h>

//const std::string DEFAUT_SON_CLIC = "../rsc/audio/default_clic.wav";

class Cliquable
{
private:
    Controleur * m_controleur;

    bool m_actif; // Si on peut cliquer le bouton
    void* m_action; // Pointeur vers la fonction à appeler pour réaliser l'action associée à l'objet cliquable

    //std::string m_clic_son = DEFAUT_SON_CLIC; // Peut-être géré ailleurs dans le futur
public:
    Cliquable() = delete;
    Cliquable(Controleur * controleur, void* action, bool actif);
    bool estSurvole(SDL_Rect zone);
    bool estClique(SDL_Rect zone);
};

#endif // CLIQUABLE_H
