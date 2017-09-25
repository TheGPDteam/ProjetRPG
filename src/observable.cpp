#include "observable.h"
#include "observateur.h"
#include <iostream>

Observable::Observable()
    : m_aChange{false}
{
}

//!
//! \brief Indique si l'objet a changé d'état
//! \return Vrai si la valeur de l'objet a changé et faux sinon
//! \date 24/11/2016
//!
bool Observable::aChange(){
    return m_aChange;
}

//!
//! \brief Met a jour l'objet pour dire qu'il a été modifié
//! La methode aChange de l'objet retournera vrai à partir de maintenant
//!
void Observable::mettreAChange(){
    m_aChange = true;
}

//!
//! \brief Ajoute un observateur à l'objet observé
//! \param obs Observateur à ajouter à la liste d'observateur
//!
void Observable::ajouterObservateur(Observateur& obs){
    m_listeObservateur.push_back(&obs);
}

//!
//! \brief Notifie à l'observateur passé en paramètre que l'objet à changé
//! \param obs Observateur à qui passer la notification
//!
//! Lance la méthode obetnirChangement() de l'Observateur passé en paramètre.
//! Remet le booléen m_aChange de l'objet à faux
//!
void Observable::notifier(Observateur &obs){
    if(aChange()){
        obs.obtenirChangement(*this);
        m_aChange =false;
    }
}

//!
//! \brief Notifie tout les obervateurs de l'objet qu'il a été changé
//!
//! Lance la méthode obtenirChangement() de chaques Observateur de la liste.
//! Remet le booléen m_aChange à faux
//!
void Observable::notifierTous(){
    if(aChange()){
        for(Observateur* obs : m_listeObservateur){
            obs->obtenirChangement(*this);
        }
        m_aChange =false;
    }
}
