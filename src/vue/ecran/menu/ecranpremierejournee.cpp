#include "ecranpremierejournee.h"
#include "constantesbouton.h"


#include <iostream>
#include <list>

const float MARGE_RATIO = 0.15;

EcranPremiereJournee::EcranPremiereJournee(Controleur* controleur)
    : EcranGeneral{controleur}, m_zoneTexte{POLICE_COLLEGED, 18, /*std::make_pair(m_fondRecapitulatif.x + 60, 0),*/
                                            SDL_Rect {MARGE_RATIO*WIDTH_FENETRE_PRINCIPALE,MARGE_RATIO*HEIGHT_FENETRE_PRINCIPALE,(1.-2*MARGE_RATIO)*WIDTH_FENETRE_PRINCIPALE,(1.-2*MARGE_RATIO)*HEIGHT_FENETRE_PRINCIPALE},
                                            recupererHistoire(), SDL_Color{255,255,255,255}, COMPORTEMENT_TEXTE::SAUT_DE_LIGNE, ALIGNEMENT_TEXTE::CENTRE}
{
    m_fondRecapitulatif = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};

    std::pair<int, int> coordB((WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL/2)  , (HEIGHT_FENETRE_PRINCIPALE/2)-(HEIGHT_BOUTON_NORMAL/2)+ 300 );
    std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);
    SDL_Rect rect= {coordB.first, coordB.second, tailleB.first, tailleB.second};

    ajoutBoutonDansMapDeBoutons(new Bouton("Suivant", rect, m_controleur, nullptr,
                                           true, POLICE_COLLEGED), &ActionsBoutons::boutonChoixNom);
    recupererHistoire();
}



std::string EcranPremiereJournee::recupererHistoire()
{
    std::ifstream fichier(CHEMIN_HISTOIRE, std::ifstream::in);
    std::string ligne;

    int coordY = m_fondRecapitulatif.y + 90;
    TexteSDL* tmpTextes;
    std::string tmpTexte="";

    if(fichier.good())
    {
        do
        {
            std::getline(fichier, ligne);
            tmpTexte+="\n"+ligne;
            tmpTextes = new TexteSDL(ligne, SDL_Color{255,255,255,255}, POLICE_COLLEGED, 18, std::make_pair(m_fondRecapitulatif.x + 60, coordY));
            m_zoneHistoire.push_back(tmpTextes);
            coordY += tmpTextes->obtenirHauteurFont();
        }
        while(!fichier.eof());



        fichier.close();
        return tmpTexte;
    }
    return "";
}



void EcranPremiereJournee::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage)
{
    SDL_FillRect(fenetre_affichage, &m_fondRecapitulatif, SDL_MapRGB(fenetre_affichage->format, 100, 100, 100));

    m_zoneTexte.afficher(fenetre_affichage);

    //A SUPPRIMER
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
            if(DictionnaireDeBoutons::boutonValiderEntree("Suivant",evenements,clique_souris,coord_souris)) break;
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
