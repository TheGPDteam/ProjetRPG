#include "tableaudefilable.h"
#include "outilsvue.h"

TableauDefilable::TableauDefilable(SDL_Rect rect, Controleur *controleur,float hauteurLigne):
    Affichable (rect), m_hauteurLigne(hauteurLigne), m_controleur(controleur), m_tableauEntete(nullptr),  m_tableauDonnee(nullptr),m_zoneDefilableDonnees(nullptr)
{}


void
TableauDefilable::afficher(SDL_Surface *surface){
    m_tableauEntete->afficher(surface);
    m_zoneDefilableDonnees->afficher(surface);
}

TableauDefilable * TableauDefilable::tableauHumain(SDL_Rect rect, Controleur *controleur, const std::string titre, bool aUneImage, float hauteurLigne){
    TableauDefilable * tabDef = creationTableauDefilableDefaut(rect,controleur,titre,aUneImage,hauteurLigne);
    tabDef->ajouterEnTeteHumain();
    return tabDef;
}

TableauDefilable * TableauDefilable::tableauObjet(SDL_Rect rect, Controleur *controleur, const std::string titre, bool aUneImage, TypeObjet typeObjet, float hauteurLigne){
    TableauDefilable * tabDef = creationTableauDefilableDefaut(rect,controleur,titre,aUneImage,hauteurLigne);
    tabDef->ajouterEnTeteObjet(typeObjet);
    return tabDef;
}

TableauDefilable * TableauDefilable::creationTableauDefilableDefaut(SDL_Rect rect, Controleur *controleur, const std::string titre, bool aUneImage, float hauteurLigne){
    TableauDefilable * tabDef = new TableauDefilable(rect,controleur,hauteurLigne);

    tabDef->m_tableauEntete = new Tableau(SDL_Rect(),controleur,aUneImage, hauteurLigne);
    tabDef->m_tableauDonnee = new Tableau(SDL_Rect(),controleur,aUneImage, hauteurLigne);
    tabDef->redimensionner(rect); //donne les bonnes valeurs de rect aux tableauxrect

    tabDef->ajoutertitre(titre);
    SDL_Rect rect2 = tabDef->m_tableauDonnee->rectangle();
    tabDef->m_zoneDefilableDonnees = tabDef->m_tableauDonnee->obtenirZoneDefilableTableau(rect2);
    return tabDef;
}

void
TableauDefilable::ajoutertitre(std::string titre){
    std::vector<std::string> tmp;
    tmp.push_back(titre);
    m_tableauEntete->ajouterLigne(tmp);
}
void
TableauDefilable::ajouterEnTeteHumain(){
    std::vector<std::string> tmp;
    tmp.push_back("Nom");
    tmp.push_back("Prenom");
    tmp.push_back("Chasse");
    tmp.push_back("Recolte");
    tmp.push_back("Campement");
    tmp.push_back("Arme");
    tmp.push_back("Niveau");
    m_tableauEntete->ajouterLigne(tmp);
}

void
TableauDefilable::ajouterEnTeteObjet(TypeObjet typeObjet){
    std::vector<std::string> tmp;
    tmp.push_back(" ");
    tmp.push_back("Nom");
    tmp.push_back("Description");
    if(typeObjet == TypeObjet::Partie_bus ) {
        tmp.push_back("Quantite");
    }
    m_tableauEntete->ajouterLigne(tmp);
}

void
TableauDefilable::redimensionner(SDL_Rect m_rectangle){
    this->m_rectangle = m_rectangle;
    float hauteurEnTete = this->m_hauteurLigne*2;

    SDL_Rect rectEntete = m_rectangle;
    rectEntete.h = hauteurEnTete;
    m_tableauEntete->redimensionner(rectEntete);
    m_rectDonnees = m_rectangle;
    m_rectDonnees.y = m_rectangle.y + hauteurEnTete;
    m_rectDonnees.h = m_rectangle.h - hauteurEnTete;
    m_tableauDonnee->redimensionner(m_rectDonnees);

}

bool TableauDefilable::gestionAffichageLigneSurvole(std::pair<int, int> coord_souris){
    if(m_zoneDefilableDonnees->contient(coord_souris))
        return m_tableauDonnee->testAffichageLigneSurvole(coordSourisElement(coord_souris));
    return m_tableauDonnee->testAffichageLigneSurvole(std::pair<int,int>());

}

Tableau *
TableauDefilable::obtenirTableauDonnees(){
    return m_tableauDonnee;
}
//!
//! \brief gestionEvenement lors qu'il y un clique de souris
//! \param coord_souris
//! \return une ligne survolé ou nullprt si pas de ligne survolé
//!
Ligne * TableauDefilable::gestionEvenementClique(std::pair<int, int> &coord_souris){
    if(m_zoneDefilableDonnees->gestionEvenementDefilableClique(coord_souris)) return nullptr;
    //test tri
    Ligne * lig = m_tableauEntete->ligneSurvole(coord_souris);
    if(lig != nullptr){
        if(lig->m_idLigne == 2){ // test si c'est bien l'entete
            m_tableauDonnee->trie(lig->caseClique(coord_souris));
            return nullptr;
        }
    }
    return m_tableauDonnee->ligneSurvole(m_zoneDefilableDonnees->coordSourisElement(coord_souris));
}
//!
//! \brief permet de lancer le tri par default sur le tableau
//! \author Lacoste Dorian
//! \date 16/12/18
//!
void
TableauDefilable::trieDefault(){
    Ligne * lig= m_tableauEntete->obtenirLigne(1);
    if(!m_tableauDonnee->trie(lig->obtenirCase(0)))
        m_tableauDonnee->trie(lig->obtenirCase(1));
}

std::pair<int, int> TableauDefilable::coordSourisElement(std::pair<int, int> &coord_sourisEcran){
    return m_zoneDefilableDonnees->coordSourisElement(coord_sourisEcran);
}

TableauDefilable::~TableauDefilable(){
    delete m_tableauDonnee;
    delete m_tableauEntete;
    delete m_zoneDefilableDonnees;
//    delete m_controleur;
}
