#include "ecranquete.h"
#include "constantesbouton.h"
#include "bouton.h"
#include <utility>

EcranQuete::EcranQuete(Controleur *controleur) :
    EcranGeneral{controleur},
    m_methodeVerificationCliqueSourisSurBouton(&DictionnaireDeBoutons::verificationCliqueSourisSurBouton),
    m_nomFenetre("Repartition des membres de votre equipe", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 30,
                 std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 60))
{
    std::pair<int, int> coordB((WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL/2), (HEIGHT_FENETRE_PRINCIPALE)-(HEIGHT_BOUTON_NORMAL)-10);
    std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Votre quete", POLICE_COLLEGED, 20, coordB, tailleB, std::make_pair(coordB.first+10,coordB.second+10)), &ActionsBoutons::boutonChoixJoueur);

    m_fondPerso = {20,50,WIDTH_FENETRE_PRINCIPALE-20*2,HEIGHT_FENETRE_PRINCIPALE/2-20*2-10};
    m_fondRecolte = {20,HEIGHT_FENETRE_PRINCIPALE/2+20,WIDTH_FENETRE_PRINCIPALE/2-20*2+10,HEIGHT_FENETRE_PRINCIPALE/2-20*2-HEIGHT_BOUTON_NORMAL};
    m_fondChasse = {WIDTH_FENETRE_PRINCIPALE/2+20-10,HEIGHT_FENETRE_PRINCIPALE/2+20,WIDTH_FENETRE_PRINCIPALE/2-20*2+10,HEIGHT_FENETRE_PRINCIPALE/2-20*2-HEIGHT_BOUTON_NORMAL};
    m_fondDescriptionPerso = {30, 60, WIDTH_FENETRE_PRINCIPALE - 20* 3, 40};
    m_fondDescriptionChasse = {WIDTH_FENETRE_PRINCIPALE/2+20, HEIGHT_FENETRE_PRINCIPALE/2+30, WIDTH_FENETRE_PRINCIPALE/2-20*2-10, 40};
    m_fondDescriptionRecolte = {30, HEIGHT_FENETRE_PRINCIPALE/2+30, WIDTH_FENETRE_PRINCIPALE/2-20*2-10, 40};

    m_CoordNom = std::make_pair(m_fondDescriptionPerso.x + 10, m_fondDescriptionPerso.y + 12);
    m_CoordPrenom = std::make_pair(m_CoordNom.first + 260, m_fondDescriptionPerso.y + 12);
    m_CoordChasse = std::make_pair(m_CoordPrenom.first + 170, m_fondDescriptionPerso.y + 12);
    m_CoordRecolte = std::make_pair(m_CoordChasse.first + 120, m_fondDescriptionPerso.y + 12);

    m_zoneNomPersonnage = new TexteSDL("Nom", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, m_CoordNom);
    m_zonePrenomPersonnage = new TexteSDL("Prenom", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, m_CoordPrenom);
    m_zoneChassePersonnage = new TexteSDL("Chasse", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, m_CoordChasse);           // position imprécise **
    m_zoneRecoltePersonnage = new TexteSDL("Recolte", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, m_CoordRecolte);



    //Equipe* equipe = controleur->obtenirModele()->obtenirJoueur()->obtenirEquipe();
//    Humain* h = new Humain;
//    h->definirNom("nn");
//    equipe->ajouterPersonnage(h);

 //   for (auto p: equipe->obtenirListePersonnage())
  //  {
    //    m_equipe.push_back(dynamic_cast<Humain*>(p));
   // }

}
EcranQuete::~EcranQuete(){}


void EcranQuete::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage)
{
    std::pair<int, int> coordB((WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL/2), (HEIGHT_FENETRE_PRINCIPALE)-(HEIGHT_BOUTON_NORMAL)-10);
    std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

//    SDL_Rect ecran = {0, 0, WIDTH_FENETRE_PRINCIPALE, HEIGHT_FENETRE_PRINCIPALE};
//    SDL_FillRect(fenetre_affichage, &ecran, SDL_MapRGB(fenetre_affichage->format, 150, 150, 150));
    afficherFondEcran(fenetre_affichage);

    SDL_FillRect(fenetre_affichage, &m_fondPerso, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondRecolte, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondChasse, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondDescriptionPerso, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));
    SDL_FillRect(fenetre_affichage, &m_fondDescriptionChasse, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));
    SDL_FillRect(fenetre_affichage, &m_fondDescriptionRecolte, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));


    m_nomFenetre.afficherTexte(fenetre_affichage);
    m_zoneNomPersonnage->afficherTexte(fenetre_affichage);
    m_zonePrenomPersonnage->afficherTexte(fenetre_affichage);
    m_zoneChassePersonnage->afficherTexte(fenetre_affichage);
    m_zoneRecoltePersonnage->afficherTexte(fenetre_affichage);

    //Fonction interessante mais probleme avec obtenirModele()
    int i=0;
    for (Humain *h : m_controleur->obtenirModele()->obtenirCampement()->obtenirNonAttribuees())
    {
        ++i;
        //m_fondDescriptionPerso.x + 10, m_fondDescriptionPerso.y + m_fondDescriptionPerso.h*i));
        TexteSDL tempNomPersonnage(h->obtenirNom(), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_CoordNom.first,m_CoordNom.second+30*i));
        tempNomPersonnage.afficherTexte(fenetre_affichage);
        TexteSDL tempPrenomPersonnage(h->obtenirPrenom(), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_CoordPrenom.first,m_CoordPrenom.second+30*i));
        tempPrenomPersonnage.afficherTexte(fenetre_affichage);
        TexteSDL tempChassePersonnage(std::to_string(h->obtenirChasse().obtenirValeur()), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_CoordChasse.first,m_CoordChasse.second+30*i));           // position imprécise **
        tempChassePersonnage.afficherTexte(fenetre_affichage);
        TexteSDL tempRecoltePersonnage(std::to_string(h->obtenirRecolte().obtenirValeur()), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_CoordRecolte.first,m_CoordRecolte.second+30*i));
        tempRecoltePersonnage.afficherTexte(fenetre_affichage);
        //ajoutBoutonDansMapDeBoutons(new Bouton(Normal, false, "Attribuer", POLICE_COLLEGED, 20, coordB, tailleB, std::make_pair(m_CoordRecolte.first + 150, m_CoordRecolte.second + 30 * i)), &ActionsBoutons::boutonChoixJoueur);

    }
    afficherBoutons(coord_souris, fenetre_affichage);
}


void EcranQuete::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris)
{
    SDL_Event evenements;



    while(SDL_PollEvent(&evenements))
    {
        switch(evenements.type)
        {
        case SDL_QUIT:
            quitter_jeu = true;
            SDL_Quit();
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

void EcranQuete::obtenirChangement(Observable &obj){}
