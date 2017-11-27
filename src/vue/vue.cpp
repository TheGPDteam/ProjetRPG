#include "vue.h"


//!
//! \brief Constructeur paramétré d'une vue
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.3
//!
//! Initialise la vue (elle démarreras toujours sur l'écran du menu princiapal)
//!

Vue::Vue()
{    
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();
    }

    m_fenetrePrincipale = SDL_SetVideoMode(WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE, BPP, SDL_HWSURFACE);
    SDL_WM_SetCaption("Projet RPG", NULL);

    m_typeEcran = MenuPrincipal;

    //Les nouveaux écrans avec sprites doivent être déclarés après avoir initialisé la fenêtre
    m_menuPrincipal = new EcranMenuPrincipal();
    m_jeuPrincipal = new EcranJeuPrincipal();
    m_ecranEquipe = new EcranEquipe();
    m_ecranInventaire = new EcranInventaire();
    m_ecranChoixPersonnage = new EcranChoixPersonnage();
    m_ChoixQuete = new EcranQuete();
    m_QueteJoueur = new EcranQueteJoueur();
    m_ecranPremiereJournee = new EcranPremiereJournee();
    m_ecranRecapitulatifNuit = new EcranRecapitulatifNuit();

    m_cliqueSouris = false;
    m_coordSouris = {0,0};
    m_quitterJeu = false;
}

//!
//! \brief Initialise le controleur de la vue
//! \author mleothaud, fvain
//! @param controleur controleur de l'architecture du modèle MVC
//! \date 15/11/16
//! \version 1.0
//!
//! Initialise le controleur de la vue en fonction du controleur en paramètre
//!

void Vue::definirControleur(Controleur *controleur)
{
    m_controleur=controleur;

    m_controleur->obtenirModele()->obtenirJoueur()->ajouterObservateur(*m_jeuPrincipal);
    m_controleur->obtenirModele()->obtenirJoueur()->ajouterObservateur(*m_ecranInventaire);
    m_controleur->obtenirModele()->obtenirJoueur()->ajouterObservateur(*m_ecranRecapitulatifNuit);
    m_controleur->obtenirModele()->obtenirJoueur()->ajouterObservateur(*m_ecranPremiereJournee);
    m_jeuPrincipal->definirCarte(m_controleur->obtenirModele()->obtenirCarte());

    m_ecranInventaire->definirEtatQuantite(m_controleur->obtenirModele()->obtenirJoueur()->obtenirInventaireJoueur()->obtenirNombreObjet());
    m_ecranInventaire->definirObjetPourAffichage(m_controleur->obtenirModele()->obtenirJoueur()->obtenirInventaireJoueur()->obtenirObjets());

    // m_ecranChoix ?
}


//!
//! \brief Affiche la vue
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.2
//!
//! Affiche la vue en fonction de son type d'écran (correspondant à m_typeEcran)
//!

void Vue::affichageVue()
{
    switch(m_typeEcran)
    {
    case MenuPrincipal:
        afficherEcran(m_menuPrincipal);
        break;
    case JeuPrincipal:
        afficherEcran(m_jeuPrincipal);
        break;
    case Equipe:
        afficherEcran(m_ecranEquipe);
        break;
    case Inventaire:
        afficherEcran(m_ecranInventaire);
        break;
    case ChoixPersonnage:
         afficherEcran(m_ecranChoixPersonnage);
         break;
    case ChoixQuete:
        afficherEcran(m_ChoixQuete);
        break;
    case PopUpJoueur:
        afficherEcran(m_QueteJoueur);
        break;
    case PremiereJournee:
        afficherEcran(m_ecranPremiereJournee);
        break;
    case RecapitulatifNuit:
        afficherEcran(m_ecranRecapitulatifNuit);
        break;
    case Quitter:
        m_quitterJeu = true;
        break;
    default:
        std::cout << "Erreur d'initialisation du type d'affichage !" << std::endl;
        break;
    }

    if(!m_quitterJeu) // Sans cette condition segfault à cause du SDL_Quit() de gestionEvenementJoueur
    {
        SDL_Flip(m_fenetrePrincipale);
#ifndef EMSCRIPTEN
        SDL_Delay(DELAI);
#endif
    }
}



//!_FL
//! \author pgutierrez
//! @param ecran affiche l'écran en paramètre
//! \date 23/11/16
//! \version 1.1
//!
//! Affiche tout le contenu de l'écran placé en paramètre et vérifie si il n,'y a pas un clique souris
//!

void Vue::afficherEcran(EcranGeneral* ecran_courant)
{
    if(ecran_courant != nullptr)
    {
        ecran_courant->afficherEcran(m_coordSouris, m_fenetrePrincipale);
        ecran_courant->gestionDesEvenements(m_controleur, m_quitterJeu, m_cliqueSouris, m_coordSouris);

        if(m_cliqueSouris)
        {
            m_typeEcran = ecran_courant->verificationCliqueSourisSurBouton(m_coordSouris, m_typeEcran);
            m_cliqueSouris = false;
        }
    }
}



//!
//! \brief Accesseur m_quitterJeu
//! \return bool
//! \author pgutierrez
//! \date 21/11/16
//! \version 1.0
//!
//! Retourne la valeur de m_quitterJeu
//!

bool Vue::getFermerJeu()
{
    return m_quitterJeu;
}



//!
//! \brief Destructeur de la vue
//! \author pgutierrez
//! \date 11/11/16
//! \version 0.1
//!
//! Détruit l'écran du menu princiapal si il était initialisé
//!

Vue::~Vue()
{

    if(m_menuPrincipal != nullptr)
    {
        delete m_menuPrincipal;
    }

    if(m_jeuPrincipal != nullptr)
    {
        delete m_jeuPrincipal;
    }

    if(m_ecranEquipe != nullptr)
    {
        delete m_ecranEquipe;
    }

    if(m_ecranInventaire != nullptr)
    {
        delete m_ecranInventaire;
    }

    if (m_ecranRecapitulatifNuit)
    {
        delete m_ecranRecapitulatifNuit;
    }

    if (m_ecranPremiereJournee != nullptr)
    {
        delete m_ecranPremiereJournee;
    }

    SDL_FreeSurface(m_fenetrePrincipale);
    TTF_Quit();
    SDL_Quit();
}

//!
//! \brief Vue::changerEcran
//! \param nouvelEcran
//!
void Vue::changerEcran(TypeEcran nouvelEcran){
    m_typeEcran = nouvelEcran;
}

