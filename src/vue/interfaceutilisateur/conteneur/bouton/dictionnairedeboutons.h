#ifndef MAPDEBOUTONS_H
#define MAPDEBOUTONS_H

#include <functional>

#include "actionsboutons.h"
#include "bouton.h"
#include "constantesbouton.h"


class DictionnaireDeBoutons
{
private :
    const SDL_Rect RECT_BOUTON_NORMAL_ACTIF;
    const SDL_Rect RECT_BOUTON_NORMAL;
    void verificationSourisSurBouton(Bouton* bouton, std::pair<int, int> coord_souris);
protected:
    ActionsBoutons* m_actionsBoutons;
    std::map<Bouton *, std::function<TypeEcran(ActionsBoutons&)>> m_mapDeBoutons;
    void remiseAZeroBoutons();
    void ajoutBoutonDansMapDeBoutons(Bouton* bouton, std::function<TypeEcran(ActionsBoutons &)> action_bouton);
    void afficherBoutons(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage);

public:
    DictionnaireDeBoutons(Controleur *controleur);
    Bouton * obtenirBouton(std::string nomBouton);
    bool boutonValiderEntree(std::string nomBouton,SDL_Event evenement,bool &clique_souris, std::pair<int, int> &coord_souris);
    TypeEcran verificationCliqueSourisSurBoutons(const std::pair<int, int> coord_souris, TypeEcran type_ecran_courant);
//    void verificationSourisSurBouton(Bouton* bouton, std::pair<int, int> coord_souris);

    virtual ~DictionnaireDeBoutons();

};

#endif // MAPDEBOUTONS_H
