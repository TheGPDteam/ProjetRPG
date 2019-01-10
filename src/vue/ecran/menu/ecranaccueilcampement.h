#ifndef ECRANACCUEILCAMPEMENT_H
#define ECRANACCUEILCAMPEMENT_H

#include "ecrangeneral.h"
#include "outilsvue.h"
#include "tableaudefilable.h"

class EcranAccueilCampement : public EcranGeneral
{
private:
    const std::string TEXTE_NOMBRE_OBJETS = "Nombre d'objets dans le camp : ";
    const std::string TEXTE_CONSOMMATION = "Valeur nutritive necessaire pour survivre : ";
    const std::string TEXTE_CONSOMMATION_DISPONIBLE = "Valeur nutritive disponible actuellement : ";
    SDL_Surface * m_fond;

    TexteSDL m_nomFenetre;
    TexteSDL m_nombreObjets;
    TexteSDL m_consommation;
    TexteSDL m_consoDispo;
    TableauDefilable * m_tableau_objets;
public:
    EcranAccueilCampement(Controleur* controleur);

    void afficherEcran(std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage) override;
    void gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris) override;

    ~EcranAccueilCampement();

    void obtenirChangement(Observable &obj) override;


};

#endif // ECRANACCUEILCAMPEMENT_H
