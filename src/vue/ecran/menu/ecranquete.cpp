#include "ecranquete.h"
#include "interfaceutilisateur/conteneur/bouton/constantesbouton.h"
#include "interfaceutilisateur/conteneur/bouton/bouton.h"
#include <utility>
#include <vector>
#include "tableau.h"

EcranQuete::EcranQuete(Controleur *controleur, GestionnaireRessource* gestionnaireRessource) :
    EcranGeneral{controleur, gestionnaireRessource},
    m_nomFenetre("Repartition des membres de votre equipe", SDL_Color{0,0,0,255}, POLICE_COLLEGED, 30,
                 std::make_pair(0,0), std::make_pair(WIDTH_FENETRE_PRINCIPALE, 60))
{
    std::pair<int, int> coordB((WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL/2), (HEIGHT_FENETRE_PRINCIPALE)-(HEIGHT_BOUTON_NORMAL)-10);
    std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    //A SUPPRIMER
    SDL_Rect rect= {coordB.first, coordB.second, tailleB.first, tailleB.second};
    ajoutBoutonDansMapDeBoutons(new Bouton("Exploration", rect, m_controleur, nullptr,
                                           true, POLICE_COLLEGED), &ActionsBoutons::lancerExploration);

    m_fondPerso = {20,50,WIDTH_FENETRE_PRINCIPALE-20*2,HEIGHT_FENETRE_PRINCIPALE/2-20*2-10};
    m_fondExploration = {20, HEIGHT_FENETRE_PRINCIPALE/2+20 , WIDTH_FENETRE_PRINCIPALE-20*2,HEIGHT_FENETRE_PRINCIPALE/2-20*2-10-HEIGHT_BOUTON_NORMAL};;
    m_fondDescriptionPerso = {30, 60, WIDTH_FENETRE_PRINCIPALE - 20* 3, 40};

    m_tableauNonAffectes=TableauDefilable::tableauHumain(m_fondPerso,m_controleur,"Non Affectes", false);
    m_tableauExploration=TableauDefilable::tableauHumain(m_fondExploration,m_controleur, "Explorer", false);
    Campement * c =m_controleur->obtenirModele()->obtenirCampement();
    m_tableaux.insert(std::pair<TableauDefilable *, Equipe * >(m_tableauNonAffectes, nullptr));
    m_tableaux.insert(std::pair<TableauDefilable *, Equipe * >(m_tableauExploration, c->obtenirEquipeRecolte()));

    obtenirChangement(*m_controleur->obtenirModele()->obtenirJoueur());

    m_ecranRepartitionJoueur = new EcranRepartitionJoueur(m_controleur, m_gestionnaireRessource);

}

EcranQuete::~EcranQuete(){
    delete m_ecranRepartitionJoueur;
    for (auto itr = m_tableaux.begin(); itr != m_tableaux.end(); ++itr){
        delete itr->first;
    }
    m_tableaux.clear();
}


void EcranQuete::afficherEcran(std::pair<int, int> coord_souris, SDL_Surface* fenetre_affichage){
    std::pair<int, int> coordB((WIDTH_FENETRE_PRINCIPALE/2)-(WIDTH_BOUTON_NORMAL/2), (HEIGHT_FENETRE_PRINCIPALE)-(HEIGHT_BOUTON_NORMAL)-10);
    std::pair<int, int> tailleB(WIDTH_BOUTON_NORMAL, HEIGHT_BOUTON_NORMAL);

    afficherFondEcran(fenetre_affichage);

    SDL_FillRect(fenetre_affichage, &m_fondPerso, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondExploration, SDL_MapRGB(fenetre_affichage->format, 100,100,100));
    SDL_FillRect(fenetre_affichage, &m_fondDescriptionPerso, SDL_MapRGB(fenetre_affichage->format, 200, 200, 200));
    m_nomFenetre.afficher(fenetre_affichage);


    for (auto itr = m_tableaux.begin(); itr != m_tableaux.end(); ++itr)
        itr->first->afficher(fenetre_affichage);


    if (m_ecranRepartitionJoueur->obtenirEtatAfficher()){
        m_ecranRepartitionJoueur->afficherEcran(coord_souris,fenetre_affichage);
    } else {
        afficherBoutons(coord_souris, fenetre_affichage);
    }
}

void EcranQuete::gestionDesEvenements(Controleur *controleur, bool &quitter_jeu, bool &clique_souris, std::pair<int, int> &coord_souris)
{
    if (m_ecranRepartitionJoueur->obtenirEtatAfficher()){
        m_ecranRepartitionJoueur->gestionDesEvenements(controleur, quitter_jeu, clique_souris, coord_souris);
        return;
    }
    SDL_Event evenements;

    while (SDL_PollEvent(&evenements)){
        //std::pair<int, int> coord_souris2 = std::make_pair(evenements.button.x, evenements.button.y);
        switch(evenements.type){
        case SDL_QUIT:
            quitter_jeu = true;
            SDL_Quit();
            break;

        case SDL_MOUSEBUTTONUP:
            if (evenements.button.button == SDL_BUTTON_LEFT){
                for (auto itr = m_tableaux.begin(); itr != m_tableaux.end(); ++itr) {
                    Ligne * lig = itr->first->gestionEvenementClique(coord_souris);
                    if(lig != nullptr){
                        int idHumain = lig->m_idLigne;
                        if (itr->second == nullptr){
                            auto humainsModel=  m_controleur->obtenirModele()->obtenirCampement()->obtenirNonAttribuees();
                            std::vector<Humain *> humains(humainsModel.begin(), humainsModel.end());
                            m_ecranRepartitionJoueur->definirHumain(humains.at(idHumain-1));
                        } else {
                            auto humainsModel=  itr->second->obtenirListePersonnage();
                            std::vector<Personnage *> perso(humainsModel.begin(), humainsModel.end());
                            m_ecranRepartitionJoueur->definirHumain(dynamic_cast<Humain *>(perso.at(idHumain-1)));
                        }
                    }
                }
                clique_souris = true;
                coord_souris.first = evenements.button.x;
                coord_souris.second = evenements.button.y;
            }
            break;
        case SDL_MOUSEMOTION:
            coord_souris.first = evenements.button.x;
            coord_souris.second = evenements.button.y;
            for (auto itr = m_tableaux.begin(); itr != m_tableaux.end(); ++itr) {
                if(itr->first->gestionAffichageLigneSurvole(coord_souris))
                    break;
            }
            break;
        default:
            if (DictionnaireDeBoutons::boutonValiderEntree("Exploration",evenements,clique_souris,coord_souris)) break;

            coord_souris.first = evenements.button.x;
            coord_souris.second = evenements.button.y;
            break;
        }
    }
}

void EcranQuete::obtenirChangement(Observable &obj){

    for (auto itr = m_tableaux.begin(); itr != m_tableaux.end(); ++itr) {
        TableauDefilable * tab = itr->first;
        tab->vider();
        if (itr->second == nullptr){ //cas ou c'est le tableau non attribue et donc pas d'equipe
            for (Humain *h : m_controleur->obtenirModele()->obtenirCampement()->obtenirNonAttribuees())
            {
                tab->ajouterLigne(h);
            }
        } else {
            for (Personnage *p : itr->second->obtenirListePersonnage())
                tab->ajouterLigne(dynamic_cast <Humain *> (p));
        }
        tab->trieDefault();
    }
}
