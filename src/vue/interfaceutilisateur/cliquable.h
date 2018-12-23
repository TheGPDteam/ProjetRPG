#ifndef CLIQUABLE_H
#define CLIQUABLE_H

#include <string>
#include <functional>
#include "controleur/controleur.h"
#include <SDL/SDL.h>

//const std::string DEFAUT_SON_CLIC = "../rsc/audio/default_clic.wav";

class Cliquable
{
protected:
    Controleur * m_controleur;

    bool m_actif; // Si on peut cliquer l'objet
    //std::function<void> m_action; // Pointeur vers la fonction à appeler pour réaliser l'action associée à l'objet cliquable

    virtual SDL_Rect zone() const = 0;

public:
    Cliquable() = delete;
    Cliquable(Controleur * controleur/*, std::function<void *>& action*/, bool actif);

    virtual ~Cliquable() = default;

    virtual bool contient(std::pair<int, int> coord_souris) const;
    virtual void clique() = 0;

    bool estCliquable() const;
    virtual void definirCliquable(bool actif);
};

#endif // CLIQUABLE_H
