#include "ecranpremierejournee.h"
#include "../../interfaceutilisateur/conteneur/bouton/constantesbouton.h"

#include <list>

EcranPremiereJournee::EcranPremiereJournee(Controleur* controleur)
    : EcranGeneral{controleur}
{
   m_fondRecapitulatif = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};

    recupererHistoire();
    //A SUPPRIMER
    /*
    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Suivant", POLICE_COLLEGED, 20,
                                           std::make_pair(DECALAGE_FOND_RECAP_NUIT + 300, HEIGHT_FENETRE_PRINCIPALE - 100),
                                           std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL),
                                           std::make_pair(DECALAGE_FOND_RECAP_NUIT + 360, HEIGHT_FENETRE_PRINCIPALE - 87)),
                                &ActionsBoutons::boutonChoixNom);
                                */
}



void EcranPremiereJournee::recupererHistoire()
{
    std::ifstream fichier(CHEMIN_HISTOIRE, std::ifstream::in);
    std::string ligne;

    int coordY = m_fondRecapitulatif.y + 90;
    TexteSDL* tmpTexte;

    if(fichier.good())
    {
        do
        {
            std::getline(fichier, ligne);
            tmpTexte = new TexteSDL(ligne, SDL_Color{255,255,255,255}, POLICE_COLLEGED, 18, std::make_pair(m_fondRecapitulatif.x + 60, coordY));
            m_zoneHistoire.push_back(tmpTexte);
            coordY += tmpTexte->getHauteurFont();
        }
        while(!fichier.eof());

        fichier.close();
    }
}



void EcranPremiereJournee::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage)
{
    SDL_FillRect(fenetre_affichage, &m_fondRecapitulatif, SDL_MapRGB(fenetre_affichage->format, 100, 100, 100));

    for (TexteSDL* texte : m_zoneHistoire)
    {
        texte->afficher(fenetre_affichage);
    }

    //A SUPPRIMER
    //afficherBoutons(coord_souris, fenetre_affichage);
}



void EcranPremiereJournee::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris)
{
    SDL_Event evenements;
    while(SDL_PollEvent(&evenements))
    {
        switch(evenements.type)
        {
        case SDL_QUIT:
            quitter_jeu = true;
            break;

        case SDL_MOUSEBUTTONUP:
            if(evenements.button.button == SDL_BUTTON_LEFT)
            {
                clique_souris = true;
                coord_souris.first = evenements.button.x;
                coord_souris.second = evenements.button.y;
            }
            break;
        default:
            coord_souris.first = evenements.button.x;
            coord_souris.second = evenements.button.y;
            break;
        }
    }
}



void EcranPremiereJournee::obtenirChangement(Observable &obj)
{
}



EcranPremiereJournee::~EcranPremiereJournee()
{
    for (unsigned int cpt = 0; cpt < m_zoneHistoire.size(); cpt++)
    {
        if (m_zoneHistoire[cpt] != nullptr)
        {
            delete m_zoneHistoire[cpt];
        }
    }
}
