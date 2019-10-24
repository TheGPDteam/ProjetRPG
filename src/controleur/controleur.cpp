#include "controleur.h"
#include "../vue/ecran/typeecran.h"
#include "../vue/vue.h"
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
        m_modele->deplacement(dir);
}


void Controleur::deroulementJournee(){
    if(m_modele->obtenirTemps()->obtenirTempsRestantJournee().count() <=0)
    {
        m_modele->finJournee();
        m_vue->changerEcran(TypeEcran::RecapitulatifNuit);
    }
}

void Controleur::chargerSauvegarde()
{
    Sauvegarde::chargerModele(m_modele);
}


void Controleur::sauvegarderModele()
{
    Sauvegarde::sauvegarderModele(m_modele);
}


void Controleur::nouvellePartie(){
    m_modele->premiereJournee();
}


Modele* Controleur::obtenirModele(){
    return m_modele;
}


Vue * Controleur::obtenirVue(){
    return m_vue;
}


/**
 * @brief Permet de reagir au chois de l'utilisateur à propos d'un nouvel arrivant
 * @param choix Le choix de l'utilisateur à propos du nouvel arrivant ; True si acceptation ; False si non
 */
void Controleur::choixNouvelArrivant(bool choix)
{
    if(choix)
    {
        m_modele->obtenirCampement()->ajouterPersonne(m_modele->obtenirNouvelArrivant());
        m_modele->changerNouvelArrivant(nullptr);
    }
}


Humain * Controleur::journeeSuivante()  {
    return m_modele->journeeSuivante();
}


void Controleur::finJournee() {
    m_modele->finJournee();
}
