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

void Controleur::miseAJourVue()
{
    // TO-DO
}

void Controleur::deplacementJoueur(Direction dir)
{
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
