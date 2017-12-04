#ifndef controleur_h
#define controleur_h

#include <string>

#include "modele/modele.h"

class Vue;

class Controleur
{
private:
    Vue* m_vue;
    Modele* m_modele;
public :
    Controleur() = default;
    Controleur(Vue* vue, Modele* modele);

    void definirVue(Vue *vue);
    void definirModele(Modele *modele);

    void nouvellePartie();

    void deroulementJournee();

    void chargerSauvegarde(std::string nomSauvegarde);

    void sauvegarderModele();
    void sauvegarderModele(std::string nomSauvegarde);

    void deplacementJoueur(Direction dir);

    Modele* obtenirModele();

    void choixNouvelArrivant(bool choix);
};

#endif
