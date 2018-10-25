#ifndef ZONETEXTE_H
#define ZONETEXTE_H

#include <string>
#include <vector>

#include "../affichable.h"
#include "textesdl.h"

enum COMPORTEMENT_TEXTE { REDIMENTIONNE, SAUT_DE_LIGNE };

enum ALIGNEMENT_TEXTE { GAUCHE, CENTRE };

class ZoneTexte : public Affichable
{
//private:
//    std::vector<TexteSDL*> m_texteSDL;
//    std::string m_texte;
//    COMPORTEMENT_TEXTE m_comportement;
//    ALIGNEMENT_TEXTE m_alignement;

//    void initialiserTexte(const std::string chemin_police, const int taille_police, const std::pair<int, int> coord_texte,
//                          std::string texte, const SDL_Color couleur_texte);

//public:
//    //Constructeurs destructeurs
//    ZoneTexte() = delete;
//    ZoneTexte(const std::string chemin_police, const int taille_police, const std::pair<int, int> coord_texte,
//              std::string texte, const SDL_Color couleur_texte = SDL_Color(0,0,0), COMPORTEMENT_TEXTE ct = REDIMENTIONNE, ALIGNEMENT_TEXTE at = CENTRE);

//    virtual ~ZoneTexte();

//    virtual void afficher(SDL_Surface *surface_affichage);
//    virtual void redimensionner(SDL_Rect nouvelleDimension);
};

#endif // ZONETEXTE_H
