#include "controleur.h"
#include <iostream>

Controleur::Controleur(Vue* vue, Modele *modele)
{
    definirModele(modele);
    definirVue(vue);
}

void Controleur::definirModele(Modele* modele)
{
    m_modele=modele;
}

void Controleur::definirVue(Vue *vue)
{
    m_vue = vue;
}

void Controleur::deplacementJoueur(Direction dir)
{
    if(!m_modele->testChangementDeCarte(dir))
        m_modele->deplacement(dir);


}
void Controleur::deroulementJournee(){
    m_modele->obtenirTemps()->obtenirTempsRestant();
}

void Controleur::nouvellePartie(){
    m_modele->premiereJournee();
}

Modele* Controleur::obtenirModele(){
    return m_modele;
}

/**
 * @brief Permet de reagir au chois de l'utilisateur à propos d'un nouvel arrivant
 * @param choix Le choix de l'utilisateur à propos du nouvel arrivant ; True si acceptation ; False si non
 */
void Controleur::choixNouvelArrivant(bool choix)
{
    if(choix)
    {
        m_modele->obtenirCampement()->obtenirNonAttribuees().insert(m_modele->m_nouvelArrivant);
        m_modele->m_nouvelArrivant = nullptr;
    }
}

Vue* Controleur::obtenirVue(){
     return m_vue ;
 }
