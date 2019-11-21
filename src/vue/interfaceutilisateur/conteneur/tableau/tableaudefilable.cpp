#include "tableaudefilable.h"
#include "outilsvue.h"

TableauDefilable::TableauDefilable(SDL_Rect rect, Controleur *controleur, float hauteur_ligne):
    Affichable (rect), m_hauteurLigne(hauteur_ligne), m_controleur(controleur), m_tableauEntete(nullptr),  m_tableauDonnee(nullptr),m_zoneDefilableDonnees(nullptr)
{}


void TableauDefilable::afficher(SDL_Surface *surface){
    m_tableauEntete->afficher(surface);
    m_zoneDefilableDonnees->afficher(surface);
}


TableauDefilable * TableauDefilable::tableauHumain(SDL_Rect rect, Controleur *controleur, const std::string titre, bool contient_image, float hauteur_ligne){
    TableauDefilable * tabDef = creationTableauDefilableDefaut(rect, controleur, titre, contient_image, hauteur_ligne);
    tabDef->ajouterEnTeteHumain();
    return tabDef;
}


TableauDefilable * TableauDefilable::tableauObjet(SDL_Rect rect, Controleur *controleur, const std::string titre, bool contient_image, TypeObjet type_objet, float hauteur_ligne){
    TableauDefilable * tabDef = creationTableauDefilableDefaut(rect, controleur, titre, contient_image, hauteur_ligne);
    tabDef->ajouterEnTeteObjet(type_objet);
    return tabDef;
}


TableauDefilable * TableauDefilable::creationTableauDefilableDefaut(SDL_Rect rect, Controleur *controleur, const std::string titre, bool contient_image, float hauteur_ligne){
    TableauDefilable * tabDef = new TableauDefilable(rect, controleur, hauteur_ligne);

    tabDef->m_tableauEntete = new Tableau(SDL_Rect(), controleur, contient_image, hauteur_ligne);
    tabDef->m_tableauDonnee = new Tableau(SDL_Rect(), controleur, contient_image, hauteur_ligne);
    tabDef->redimensionner(rect); //donne les bonnes valeurs de rect aux tableauxrect

    tabDef->ajoutertitre(titre);
    SDL_Rect rect2 = tabDef->m_tableauDonnee->obtenirRectangle();
    tabDef->m_zoneDefilableDonnees = tabDef->m_tableauDonnee->obtenirZoneDefilableTableau(rect2);
    return tabDef;
}


TableauDefilable * TableauDefilable::tableau(SDL_Rect rect, Controleur *controleur, const std::string titre, bool contient_image, std::vector<std::string> colonne_en_tete, float hauteurLigne){
    TableauDefilable * tabDef = creationTableauDefilableDefaut(rect, controleur, titre, contient_image, hauteurLigne);
    if(colonne_en_tete.size() != 0)  tabDef->m_tableauEntete->ajouterLigne(colonne_en_tete);
    return tabDef;
}


void TableauDefilable::ajoutertitre(std::string titre){
    std::vector<std::string> tmp;
    tmp.push_back(titre);
    m_tableauEntete->ajouterLigne(tmp);
}


void TableauDefilable::ajouterEnTeteHumain(){
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


void TableauDefilable::ajouterEnTeteObjet(TypeObjet type_objet){
    std::vector<std::string> tmp;
    tmp.push_back(" ");
    tmp.push_back("Nom");
    tmp.push_back("Description");
    if(type_objet == TypeObjet::QuetePrincipale ) {
        tmp.push_back("Quantite");
    }
    m_tableauEntete->ajouterLigne(tmp);
}


void TableauDefilable::redimensionner(SDL_Rect rectangle){
    this->m_rectangle = rectangle;
    float hauteurEnTete = this->m_hauteurLigne* 2;//m_tableauEntete->obtenirNbLignes();

    SDL_Rect rectEntete = rectangle;
    rectEntete.h = hauteurEnTete;
    m_tableauEntete->redimensionner(rectEntete);
    m_rectDonnees = rectangle;
    m_rectDonnees.y = rectangle.y + hauteurEnTete;
    m_rectDonnees.h = rectangle.h - hauteurEnTete;
    m_tableauDonnee->redimensionner(m_rectDonnees);

}


bool TableauDefilable::gestionAffichageLigneSurvole(std::pair<int, int> coord_souris){
    if(m_zoneDefilableDonnees->contient(coord_souris))
        return m_tableauDonnee->testAffichageLigneSurvole(coordSourisElement(coord_souris));

    return m_tableauDonnee->testAffichageLigneSurvole(std::pair<int,int>());
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
    if (lig != nullptr){
        if (lig->m_idLigne == 2){ // test si c'est bien l'entete
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
void TableauDefilable::trieDefault(){
    Ligne * lig= m_tableauEntete->obtenirLigne(1);
    if(!m_tableauDonnee->trie(lig->obtenirCase(0)))  m_tableauDonnee->trie(lig->obtenirCase(1));
}


std::pair<int, int> TableauDefilable::coordSourisElement(std::pair<int, int> &coord_sourisEcran){
    return m_zoneDefilableDonnees->coordSourisElement(coord_sourisEcran);
}


void TableauDefilable::vider(){
    m_tableauDonnee->vider();
}


void TableauDefilable::ajouterLigne(std::vector<Affichable*> affichables){
    m_tableauDonnee->ajouterLigne(affichables);
}


void TableauDefilable::ajouterLigne(std::vector<std::string> strings){
    m_tableauDonnee->ajouterLigne(strings);
}


void TableauDefilable::ajouterLigne(Humain* perso){
    m_tableauDonnee->ajouterLigne(perso);
}


void TableauDefilable::ajouterLigne(Objet* obj){
    m_tableauDonnee->ajouterLigne(obj);
}


void TableauDefilable::ajouterLigne(Campement *c){
    m_tableauDonnee->ajouterLigne(c);
}


TableauDefilable::~TableauDefilable(){
    delete m_tableauDonnee;
    delete m_tableauEntete;
    delete m_zoneDefilableDonnees;
    //    delete m_controleur;
}
