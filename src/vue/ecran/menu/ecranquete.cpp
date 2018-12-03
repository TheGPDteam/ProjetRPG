#include "ecranquete.h"
#include "interfaceutilisateur/conteneur/bouton/constantesbouton.h"
#include "interfaceutilisateur/conteneur/bouton/bouton.h"
#include "ecranrepartitionjoueur.h"
#include <utility>
#include "tableau.h"

EcranQuete::EcranQuete(Controleur *controleur) :
    EcranGeneral{controleur},
    //m_methodeVerificationCliqueSourisSurBouton(&DictionnaireDeBoutons::verificationCliqueSourisSurBouton),
    m_nomFenetre("Repartition des membres de votre equipe", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 30,
                 std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 60)),
    m_humain_a_affecter{nullptr}
{
    std::pair<int, int> coordB((WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL/2), (HEIGHT_FENETRE_PRINCIPALE)-(HEIGHT_BOUTON_NORMAL)-10);
    std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    //A SUPPRIMER
    SDL_Rect rect= {coordB.first, coordB.second, tailleB.first, tailleB.second};

    ajoutBoutonDansMapDeBoutons(new Bouton("Votre Quete", rect, m_controleur, nullptr,
                                           true, std::make_pair<float, float>(coordB.first+20,coordB.second+15), POLICE_COLLEGED), &ActionsBoutons::boutonChoixJoueur);
    //ajoutBoutonDansMapDeBoutons(new Bouton(Normal, true, "Votre quete", POLICE_COLLEGED, 20, coordB, tailleB, std::make_pair(coordB.first+35,coordB.second+15)), &ActionsBoutons::boutonChoixJoueur);

    m_fondPerso = {20,50,WIDTH_FENETRE_PRINCIPALE-20*2,HEIGHT_FENETRE_PRINCIPALE/2-20*2-10};
    m_fondRecolte = {MARGE_RECOLTE_CHASSE_CAMPEMENT , HEIGHT_FENETRE_PRINCIPALE/2+20 , WIDTH_FENETRE_PRINCIPALE/3-20*2+10 , HEIGHT_FENETRE_PRINCIPALE/2-20*2-HEIGHT_BOUTON_NORMAL};
    m_fondChasse = {WIDTH_FENETRE_PRINCIPALE/3+20-10 , HEIGHT_FENETRE_PRINCIPALE/2+20 , WIDTH_FENETRE_PRINCIPALE/3-20*2+10 , HEIGHT_FENETRE_PRINCIPALE/2-20*2-HEIGHT_BOUTON_NORMAL};
    m_fondCampement = {m_fondChasse.x + m_fondChasse.w + 20 , HEIGHT_FENETRE_PRINCIPALE/2+20 , WIDTH_FENETRE_PRINCIPALE/3-20*2+10 , HEIGHT_FENETRE_PRINCIPALE/2-20*2-HEIGHT_BOUTON_NORMAL};
    m_fondDescriptionPerso = {30, 60, WIDTH_FENETRE_PRINCIPALE - 20* 3, 40};

    m_CoordNom = std::make_pair(m_fondDescriptionPerso.x + 10, m_fondDescriptionPerso.y + 12);
    m_CoordPrenom = std::make_pair(m_CoordNom.first + 260, m_fondDescriptionPerso.y + 12);
    m_CoordChasse = std::make_pair(m_CoordPrenom.first + 170, m_fondDescriptionPerso.y + 12);
    m_CoordRecolte = std::make_pair(m_CoordChasse.first + 120, m_fondDescriptionPerso.y + 12);
    m_CoordCampement = std::make_pair(m_CoordRecolte.first + 120, m_fondDescriptionPerso.y + 12);

    m_zoneNomPersonnage = new TexteSDL("Nom", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, m_CoordNom);
    m_zonePrenomPersonnage = new TexteSDL("Prenom", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, m_CoordPrenom);
    m_zoneChassePersonnage = new TexteSDL("Chasse", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, m_CoordChasse);           // position imprécise **
    m_zoneRecoltePersonnage = new TexteSDL("Recolte", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, m_CoordRecolte);
    m_zoneCampementPersonnage = new TexteSDL("Campement", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, m_CoordCampement);
}

EcranQuete::~EcranQuete(){
    if(m_zoneNomPersonnage != nullptr) delete m_zoneNomPersonnage;
    if(m_zonePrenomPersonnage != nullptr) delete m_zonePrenomPersonnage;
    if(m_zoneChassePersonnage != nullptr) delete m_zoneChassePersonnage;
    if(m_zoneRecoltePersonnage != nullptr) delete m_zoneRecoltePersonnage;
    if(m_zoneCampementPersonnage != nullptr) delete m_zoneCampementPersonnage;

}


void EcranQuete::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage)
{
    std::pair<int, int> coordB((WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL/2), (HEIGHT_FENETRE_PRINCIPALE)-(HEIGHT_BOUTON_NORMAL)-10);
    std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    afficherFondEcran(fenetre_affichage);

    SDL_FillRect(fenetre_affichage, &m_fondPerso, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondRecolte, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondChasse, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondCampement, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondDescriptionPerso, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));
    m_nomFenetre.afficher(fenetre_affichage);

    Tableau tabHumain(m_fondPerso,32,m_controleur);
    tabHumain.ajouterEnTeteHumain();
    for (Humain *h : m_controleur->obtenirModele()->obtenirCampement()->obtenirNonAttribuees())
    {
        tabHumain.ajouterHumain(h);
    }
    tabHumain.afficher(fenetre_affichage);

    Tableau tabHumainRecolte(m_fondRecolte,32,m_controleur);
    tabHumainRecolte.ajouterEnTeteHumain();
    for (Personnage *p : m_controleur->obtenirModele()->obtenirCampement()->obtenirRecolte()->obtenirListePersonnage())
    {
        tabHumainRecolte.ajouterHumain(dynamic_cast <Humain *> (p));
    }
    tabHumainRecolte.afficher(fenetre_affichage);

    Tableau tabHumainChasse(m_fondChasse,32,m_controleur);
    tabHumainChasse.ajouterEnTeteHumain();
    for (Personnage *p : m_controleur->obtenirModele()->obtenirCampement()->obtenirChasse()->obtenirListePersonnage())
    {
        tabHumainChasse.ajouterHumain(dynamic_cast <Humain *> (p));
    }
    tabHumainChasse.afficher(fenetre_affichage);

    Tableau tabHumainCampement(m_fondCampement,32,m_controleur);
    tabHumainCampement.ajouterEnTeteHumain();
    for (Personnage *p : m_controleur->obtenirModele()->obtenirCampement()->obtenirCampement()->obtenirListePersonnage())
    {
        tabHumainCampement.ajouterHumain(dynamic_cast <Humain *> (p));
    }
    tabHumainCampement.afficher(fenetre_affichage);

    int l=0;
    for (Personnage *p : m_controleur->obtenirModele()->obtenirCampement()->obtenirCampement()->obtenirListePersonnage())
    {
        Humain *h = dynamic_cast <Humain *> (p);
        TexteSDL tempNomPersonnage(h->obtenirNom(), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 18, std::make_pair(1050,410+30*l));
        tempNomPersonnage.afficher(fenetre_affichage);
        TexteSDL tempPrenomPersonnage(h->obtenirPrenom(), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 18, std::make_pair(1250,410+30*l));
        tempPrenomPersonnage.afficher(fenetre_affichage);
        TexteSDL tempCampementPersonnage(std::to_string(h->obtenirCampement().obtenirValeur()), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 18, std::make_pair(1400,410+30*l));
        tempCampementPersonnage.afficher(fenetre_affichage);
        ++l;
    }

    //A SUPPRIMER
    afficherBoutons(coord_souris, fenetre_affichage);

    if(m_humain_a_affecter != nullptr){
        RepartitionJoueur repartition (m_humain_a_affecter, fenetre_affichage, m_controleur);
        int rep = repartition.affecter();
        if(rep == CHASSE){
            m_controleur->obtenirModele()->obtenirCampement()->obtenirChasse()->ajouterPersonnage(m_humain_a_affecter);
            m_controleur->obtenirModele()->obtenirCampement()->obtenirNonAttribuees().erase(m_humain_a_affecter);
        }
        if(rep == RECOLTE){
            m_controleur->obtenirModele()->obtenirCampement()->obtenirRecolte()->ajouterPersonnage(m_humain_a_affecter);
            m_controleur->obtenirModele()->obtenirCampement()->obtenirNonAttribuees().erase(m_humain_a_affecter);
        }
        if(rep == CAMPEMENT){
            m_controleur->obtenirModele()->obtenirCampement()->obtenirCampement()->ajouterPersonnage(m_humain_a_affecter);
            m_controleur->obtenirModele()->obtenirCampement()->obtenirNonAttribuees().erase(m_humain_a_affecter);
        }
        m_humain_a_affecter = nullptr;
    }
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

        case SDL_MOUSEBUTTONDOWN:
            if(evenements.button.button == SDL_BUTTON_LEFT)
            {
                if(evenements.button.y >= m_CoordPrenom.second+30 && evenements.button.y <= m_CoordPrenom.second+30+(8*30)
                        && evenements.button.x >= m_CoordNom.first ){
                      int idHumain = (evenements.button.y - m_CoordPrenom.second)/30;

                    int i=0;
                   for(Humain* h : m_controleur->obtenirModele()->obtenirCampement()->obtenirNonAttribuees())
                   {

                       i++;
                       if(i==idHumain)
                       {
                           m_humain_a_affecter = h;
                           break;
                       }
                   }


                }

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
