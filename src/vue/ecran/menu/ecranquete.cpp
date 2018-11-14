#include "ecranquete.h"
#include "../../interfaceutilisateur/conteneur/bouton/constantesbouton.h"
#include "../../interfaceutilisateur/conteneur/bouton/bouton.h"
#include "ecranrepartitionjoueur.h"
#include <utility>

EcranQuete::EcranQuete(Controleur *controleur) :
    EcranGeneral{controleur},
    //m_methodeVerificationCliqueSourisSurBouton(&DictionnaireDeBoutons::verificationCliqueSourisSurBouton),
    m_nomFenetre("Repartition des membres de votre equipe", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 30,
                 std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 60)),
    m_titreRecolte("Recolte", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(200,HEIGHT_FENETRE_PRINCIPALE/2+40)),
    m_titreChasse("Chasse", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 20, std::make_pair(700,HEIGHT_FENETRE_PRINCIPALE/2+40)),
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
}

EcranQuete::~EcranQuete(){
    if(m_zoneNomPersonnage != nullptr) delete m_zoneNomPersonnage;
    if(m_zonePrenomPersonnage != nullptr) delete m_zonePrenomPersonnage;
    if(m_zoneChassePersonnage != nullptr) delete m_zoneChassePersonnage;
    if(m_zoneRecoltePersonnage != nullptr) delete m_zoneRecoltePersonnage;

}


void EcranQuete::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage)
{
    std::pair<int, int> coordB((WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL/2), (HEIGHT_FENETRE_PRINCIPALE)-(HEIGHT_BOUTON_NORMAL)-10);
    std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    afficherFondEcran(fenetre_affichage);

    SDL_FillRect(fenetre_affichage, &m_fondPerso, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondRecolte, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondChasse, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondDescriptionPerso, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));
    SDL_FillRect(fenetre_affichage, &m_fondDescriptionChasse, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));
    SDL_FillRect(fenetre_affichage, &m_fondDescriptionRecolte, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));

    m_nomFenetre.afficher(fenetre_affichage);
    m_zoneNomPersonnage->afficher(fenetre_affichage);
    m_zonePrenomPersonnage->afficher(fenetre_affichage);
    m_zoneChassePersonnage->afficher(fenetre_affichage);
    m_zoneRecoltePersonnage->afficher(fenetre_affichage);
    m_titreChasse.afficher(fenetre_affichage);
    m_titreRecolte.afficher(fenetre_affichage);

    int i=0;
    for (Humain *h : m_controleur->obtenirModele()->obtenirCampement()->obtenirNonAttribuees())
    {
        ++i;
        //m_fondDescriptionPerso.x + 10, m_fondDescriptionPerso.y + m_fondDescriptionPerso.h*i));
        TexteSDL tempNomPersonnage(h->obtenirNom(), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_CoordNom.first,m_CoordNom.second+30*i));
        tempNomPersonnage.afficher(fenetre_affichage);
        TexteSDL tempPrenomPersonnage(h->obtenirPrenom(), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_CoordPrenom.first,m_CoordPrenom.second+30*i));
        tempPrenomPersonnage.afficher(fenetre_affichage);
        TexteSDL tempChassePersonnage(std::to_string(h->obtenirChasse().obtenirValeur()), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_CoordChasse.first,m_CoordChasse.second+30*i));           // position imprécise **
        tempChassePersonnage.afficher(fenetre_affichage);
        TexteSDL tempRecoltePersonnage(std::to_string(h->obtenirRecolte().obtenirValeur()), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_CoordRecolte.first,m_CoordRecolte.second+30*i));
        tempRecoltePersonnage.afficher(fenetre_affichage);
        TexteSDL tempCampementPersonnage(std::to_string(h->obtenirCampement().obtenirValeur()), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(m_CoordCampement.first,m_CoordCampement.second+30*i));
        tempCampementPersonnage.afficher(fenetre_affichage);
        //ajoutBoutonDansMapDeBoutons(new Bouton(Normal, false, "Attribuer", POLICE_COLLEGED, 20, coordB, tailleB, std::make_pair(m_CoordRecolte.first + 150, m_CoordRecolte.second + 30 * i)), &ActionsBoutons::boutonChoixJoueur);
        if(i==8)
            break;
    }
    int j=0;
    for (Personnage *p : m_controleur->obtenirModele()->obtenirCampement()->obtenirRecolte()->obtenirListePersonnage())
    {
        Humain *h = dynamic_cast <Humain *> (p);
        TexteSDL tempNomPersonnage(h->obtenirNom(), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 18, std::make_pair(50,410+30*j));
        tempNomPersonnage.afficher(fenetre_affichage);
        TexteSDL tempPrenomPersonnage(h->obtenirPrenom(), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 18, std::make_pair(250,410+30*j));
        tempPrenomPersonnage.afficher(fenetre_affichage);
        TexteSDL tempRecoltePersonnage(std::to_string(h->obtenirRecolte().obtenirValeur()), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 18, std::make_pair(400,410+30*j));
        tempRecoltePersonnage.afficher(fenetre_affichage);
        ++j;
    }
    int k=0;
    for (Personnage *p : m_controleur->obtenirModele()->obtenirCampement()->obtenirChasse()->obtenirListePersonnage())
    {
        Humain *h = dynamic_cast <Humain *> (p);
        TexteSDL tempNomPersonnage(h->obtenirNom(), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 18, std::make_pair(550,410+30*k));
        tempNomPersonnage.afficher(fenetre_affichage);
        TexteSDL tempPrenomPersonnage(h->obtenirPrenom(), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 18, std::make_pair(750,410+30*k));
        tempPrenomPersonnage.afficher(fenetre_affichage);
        TexteSDL tempRecoltePersonnage(std::to_string(h->obtenirChasse().obtenirValeur()), SDL_Color{255,255,255,255}, POLICE_COLLEGED, 18, std::make_pair(900,410+30*k));
        tempRecoltePersonnage.afficher(fenetre_affichage);
        ++k;
    }
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
        RepartitionJoueur repartition (m_humain_a_affecter, fenetre_affichage);
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
