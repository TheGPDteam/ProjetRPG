#include "dictionnairedeboutons.h"
#include "constantesbouton.h"


//!
//! \brief Constructeur par défaut de la map de boutons
//! \author pgutierrez
//! \date 20/11/16
//! \version 1.0
//!
//! Initialise la map de boutons d'un écran
//!

DictionnaireDeBoutons::DictionnaireDeBoutons(Controleur * controleur) : m_actionsBoutons(new ActionsBoutons(controleur))
{
}


//!
//! \brief Ajout un bouton avec sa fonction associé dans la map
//! \author pgutierrez
//! \date 20/11/16
//! @param bouton bouton au quel sera lié le second paramètre
//! @param action_bouton fonction de la classe ActionsBoutons stockées dans une variable, correspondant au bouton
//! \version 1.0
//!
//! On ne peut ajouter un bouton que si il n'est pas encore présent dns la map
//!

void DictionnaireDeBoutons::ajoutBoutonDansMapDeBoutons(Bouton *bouton, std::function<TypeEcran(ActionsBoutons &)> action_bouton)
{
    auto iterateurBouton = m_mapDeBoutons.find(bouton);

    if(iterateurBouton == m_mapDeBoutons.end())
    {
        m_mapDeBoutons[bouton] = action_bouton;
    }
}


//!
//! \brief Vérifie si le clique de la souris est sûr un bouton
//! \return TypeEcran retourne le nouveau type de l'écran ou reste inchangé
//! \author pgutierrez
//! \date 20/11/16
//! @param coord_x_souris coordonnées de la souris en x lors du clique de la souris
//! @param coord_y_souris coordonnées de la souris en y lors du clique de la souris
//! @param type_ecran_courant le type de l'écran courant afin de la modifier ou non
//! \version 0.2
//!
//! Le clique de la souris sur un bouton engendre un changement d'état de l'écran (donc de son type)
//!

TypeEcran DictionnaireDeBoutons::verificationCliqueSourisSurBouton(std::pair<int, int> coord_souris, TypeEcran type_ecran_courant)
{
    auto iterateurBouton = m_mapDeBoutons.begin();
    bool trouver = false;

    while(iterateurBouton != m_mapDeBoutons.end() && !trouver)
    {
        if(iterateurBouton->first->estCliquable() && iterateurBouton->first->contient(coord_souris))
        {
            trouver = true;
            type_ecran_courant = iterateurBouton->second(*m_actionsBoutons);
        }
        else
        {
            ++iterateurBouton;
        }
    }

    return type_ecran_courant;
}

//!
//! \brief Vérifie si la souris survole un bouton
//! \return Bool retourne si la souris est sur un bouton
//! \author mleothaud
//! \date 24/11/16
//! @param coord_x_souris coordonnées de la souris en x lors du clique de la souris
//! @param coord_y_souris coordonnées de la souris en y lors du clique de la souris
//! \version 0.1
//!
//! Change le sprite du bouton si on le survole
//!

void DictionnaireDeBoutons::verificationSourisSurBouton(Bouton* bouton, std::pair<int, int> coord_souris)
{
    SDL_Rect rect;

    if (bouton->contient(coord_souris))
    {
        rect.x = COORD_X_BOUTON_NORMAL_ACTIF;
        rect.y = COORD_Y_BOUTON_NORMAL_ACTIF;
        rect.w = WIDTH_BOUTON_NORMAL_ACTIF;
        rect.h = HEIGHT_BOUTON_NORMAL_ACTIF;

        bouton->obtenirSpriteBouton()->changementSprite(rect);
    }
    else
    {
        rect.x = COORD_X_BOUTON_NORMAL;
        rect.y = COORD_Y_BOUTON_NORMAL;
        rect.w = WIDTH_BOUTON_NORMAL;
        rect.h = HEIGHT_BOUTON_NORMAL;

        bouton->obtenirSpriteBouton()->changementSprite(rect);
    }
}


//!
//! \brief Vérifie si le clique de la souris est sûr un bouton
//! \author pgutierrez
//! \date 20/11/16
//! @param fenetre_affichage la fenetre d'affichage où l'objet doit s'afficher
//! \version 0.1
//!
//! Le clique de la souris sur un bouton engendre un changement d'état de l'écran (donc de son type)
//!

void DictionnaireDeBoutons::afficherBoutons(const std::pair<int, int> coord_souris, SDL_Surface *fenetre_affichage)
{ 
    for(auto iterateurBouton = m_mapDeBoutons.begin(); iterateurBouton != m_mapDeBoutons.end(); ++iterateurBouton)
    {
        if(iterateurBouton->first->estCliquable())
        {
            verificationSourisSurBouton(iterateurBouton->first, coord_souris);
        }

        iterateurBouton->first->afficher(fenetre_affichage);
    }
}


//!
//! \brief Destructeur
//! \author pgutierrez
//! \date 20/11/16
//! \version 0.1
//!
//! Désalloue une partie de la map (les boutons) si elle n'est pas vide, et désalloue m_actionsBoutons si il est initialisé
//!

DictionnaireDeBoutons::~DictionnaireDeBoutons()
{
    if(!m_mapDeBoutons.empty())
    {
        for(auto iterateur = m_mapDeBoutons.begin(); iterateur != m_mapDeBoutons.end(); ++iterateur)
        {
            delete iterateur->first;
        }

        m_mapDeBoutons.clear();
    }

    if(m_actionsBoutons != nullptr)
    {
        delete m_actionsBoutons;
    }
}
