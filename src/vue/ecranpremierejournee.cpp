#include "ecranpremierejournee.h"
#include "constantesbouton.h"

#include <list>

EcranPremiereJournee::EcranPremiereJournee()
{
    short unsigned int largeurFond, hauteurFond;
    largeurFond = WIDTH_FENETRE_PRINCIPALE - 2*DECALAGE_FOND_RECAP_NUIT;
    hauteurFond = HEIGHT_FENETRE_PRINCIPALE - 2*DECALAGE_FOND_RECAP_NUIT;

    m_fondRecapitulatif = {(short int)DECALAGE_FOND_RECAP_NUIT, (short int)DECALAGE_FOND_RECAP_NUIT, largeurFond, hauteurFond};

    recupererHistoire();

    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Suivant", POLICE_COLLEGED, 20,
                                           std::make_pair(DECALAGE_FOND_RECAP_NUIT + 300, DECALAGE_FOND_RECAP_NUIT + hauteurFond - 100),
                                           std::make_pair(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL),
                                           std::make_pair(DECALAGE_FOND_RECAP_NUIT + 310, DECALAGE_FOND_RECAP_NUIT + hauteurFond - 90)),
                                &ActionsBoutons::boutonChoixPersonnage);
}



void EcranPremiereJournee::recupererHistoire()
{
    std::ifstream fichier(CHEMIN_HISTOIRE, std::ifstream::in);
    std::string ligne;

    int coordY = m_fondRecapitulatif.y + 15;
    TexteSDL* tmpTexte;

    if(fichier.good())
    {
        do
        {
            std::getline(fichier, ligne);
            tmpTexte = new TexteSDL(ligne, SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_fondRecapitulatif.x + 15, coordY));
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
        texte->afficherTexte(fenetre_affichage);
    }

    afficherBoutons(coord_souris, fenetre_affichage);
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