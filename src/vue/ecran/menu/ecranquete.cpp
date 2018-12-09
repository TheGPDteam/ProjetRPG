#include "ecranquete.h"
#include "interfaceutilisateur/conteneur/bouton/constantesbouton.h"
#include "interfaceutilisateur/conteneur/bouton/bouton.h"
#include "ecranrepartitionjoueur.h"
#include <utility>
#include "tableau.h"

EcranQuete::EcranQuete(Controleur *controleur) :
    EcranGeneral{controleur},
    //m_methodeVerificationCliqueSourisSurBouton(&DictionnaireDeBoutons::verificationCliqueSourisSurBouton),
//    m_nomFenetre("Repartition des membres de votre equipe", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 30,
//                 std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 60)),
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

    m_tableauNonAffectes=Tableau::tableauHumain(m_fondPerso,32,m_controleur,"Non Affectes");
    m_tableauChasse=Tableau::tableauHumain(m_fondChasse,32,m_controleur, "Chasse");
    m_tableauRecolte=Tableau::tableauHumain(m_fondRecolte,32,m_controleur, "Recolte");
    m_tableauCampement=Tableau::tableauHumain(m_fondCampement,32,m_controleur, "Campement");
    Campement * c = m_controleur->obtenirModele()->obtenirCampement();
    for (Humain *h : c->obtenirNonAttribuees())
    {
        m_tableauNonAffectes->ajouterLigne(h);
    }

    for (Personnage *p : c->obtenirRecolte()->obtenirListePersonnage())
    {
        m_tableauRecolte->ajouterLigne(dynamic_cast <Humain *> (p));
    }

    for (Personnage *p : c->obtenirChasse()->obtenirListePersonnage())
    {
        m_tableauChasse->ajouterLigne(dynamic_cast <Humain *> (p));
    }

    for (Personnage *p : c->obtenirCampement()->obtenirListePersonnage())
    {
        m_tableauCampement->ajouterLigne(dynamic_cast <Humain *> (p));
    }

}

EcranQuete::~EcranQuete(){
    delete m_tableauChasse;
    delete m_tableauRecolte;
    delete m_tableauCampement;
    delete m_tableauNonAffectes;
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
//    m_nomFenetre.afficher(fenetre_affichage);


    m_tableauCampement->afficher(fenetre_affichage);
    m_tableauChasse->afficher(fenetre_affichage);
    m_tableauRecolte->afficher(fenetre_affichage);
    m_tableauNonAffectes->afficher(fenetre_affichage);


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
//                if(evenements.button.y >= m_CoordPrenom.second+30 && evenements.button.y <= m_CoordPrenom.second+30+(8*30)
//                        && evenements.button.x >= m_CoordNom.first ){
//                      int idHumain = (evenements.button.y - m_CoordPrenom.second)/30;

//                    int i=0;
//                   for(Humain* h : m_controleur->obtenirModele()->obtenirCampement()->obtenirNonAttribuees())
//                   {

//                       i++;
//                       if(i==idHumain)
//                       {
//                           m_humain_a_affecter = h;
//                           break;
//                       }
//                   }


//                }

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
