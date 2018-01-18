#ifndef MAPDEBOUTONS_H
#define MAPDEBOUTONS_H

#include <functional>

#include "actionsboutons.h"
#include "bouton.h"


class DictionnaireDeBoutons
{
protected:
    ActionsBoutons* m_actionsBoutons;
    std::map<Bouton *, std::function<TypeEcran(ActionsBoutons&)>> m_mapDeBoutons;

    void ajoutBoutonDansMapDeBoutons(Bouton* bouton, std::function<TypeEcran(ActionsBoutons &)> action_bouton);
    void afficherBoutons(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage);

public:
    DictionnaireDeBoutons(Controleur *controleur);

    TypeEcran verificationCliqueSourisSurBouton(const std::pair<int, int> coord_souris, TypeEcran type_ecran_courant);
    void verificationSourisSurBouton(Bouton* bouton, std::pair<int, int> coord_souris);

    virtual ~DictionnaireDeBoutons();
};

#endif // MAPDEBOUTONS_H
