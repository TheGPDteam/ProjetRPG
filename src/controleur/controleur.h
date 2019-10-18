#ifndef controleur_h
#define controleur_h

#include <string>

#include "modele/modele.h"
#include "save/sauvegarde.h"

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

    void chargerSauvegarde();

    void sauvegarderModele();
    void sauvegarderModele(std::string nom_sauvegarde);

    void deplacementJoueur(Direction dir);

    Modele* obtenirModele();
    Vue * obtenirVue();

    Humain * journeeSuivante();
  
    void choixNouvelArrivant(bool choix);

    void finJournee();


};

#endif
