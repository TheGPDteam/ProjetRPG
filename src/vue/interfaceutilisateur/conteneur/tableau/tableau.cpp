#include "tableau.h"
#include "zonetexte.h"



Tableau::Tableau(SDL_Rect rect, Controleur *controleur, bool avecImage, float hauteurLigne)
    :Affichable{rect}, m_hauteurLigne {hauteurLigne}, m_controleur{controleur}, m_avecImage(avecImage)
{
    m_rectangle.h=0;
}



//!
//! \brief affiche le contenu du tableau
//! \param surface_affichage
//! \author Lacoste Dorian
//! \date 15/11/2018
//!
void Tableau::afficher(SDL_Surface *surface_affichage)
{
    for (Ligne * l : m_lignes)
    {
        l->afficher(surface_affichage);
    }
}
//!
//! \brief redimensionne la tableau
//! \param nouvelleDimension
//! \author Lacoste Dorian, Regnies Anthony
//! \date 15/11/18
//!
void Tableau::redimensionner(SDL_Rect nouvelleDimension)
{
    m_rectangle = nouvelleDimension;
    int i=0;
    for (Ligne * l : m_lignes)
    {
        l->redimensionner(creerRectLigne(i));
        i++;
    }
}
//!
//! \brief indique la ligne survolé
//! \param coord_souris
//! \return la ligne survolé par la souris ou nullptr si elle n'est pas survolé
//! \author Lacoste Dorian, Regnies Anthony
//! \date 22/11/18
//!
Ligne*
Tableau::ligneSurvole(std::pair<int, int> coord_souris){
    for(Ligne *l : m_lignes){
        if(l->contient(coord_souris)){
            return l;        }
    }
    return nullptr;
}

//!
//! \brief Test si la souris survole une ligne et si oui alors change la couleur de la ligne
//! \param coord_souris
//! \author Lacoste Dorian
//! \date 16/12/18
//!
bool
Tableau::testAffichageLigneSurvole(std::pair<int, int> coord_souris){
    Ligne * lSurvole = ligneSurvole(coord_souris);
    //on remet la ligne survoler precendente comme avant
    if(m_lignePrecedemmentSurvoler == lSurvole) return false;
    if(m_lignePrecedemmentSurvoler != nullptr)
        m_lignePrecedemmentSurvoler->definirNumCouleur((positionLigne(m_lignePrecedemmentSurvoler)+1)%2+1);

    //ligne n'appartient pas au tableau c'est l'entete ou c'est le titre
    if(lSurvole == nullptr){
        m_lignePrecedemmentSurvoler=nullptr;
        return false;}
    lSurvole->definirNumCouleur(3);
    m_lignePrecedemmentSurvoler=lSurvole;
    return true;
}
//!
//! \brief recherche la postion de la ligne dans le vector m_lignes
//! \param ligRecherchee
//! \return le postion de la ligne dans le vector
//!
int
Tableau::positionLigne(Ligne * ligRecherchee){
    int i=0;
    for(auto l : m_lignes){
        i++;
        if(l == ligRecherchee) break;
    }
    return i;
}

//!
//! \brief obtient la ligne a la position numLignee
//! \param numLigne le numero de la ligne a récuperer
//! \return la ligne qui est a cette position dans le vector
//! \author Lacoste Dorian
//! \date 16/12/18
//!
Ligne * Tableau::obtenirLigne(int numLigne){
    return m_lignes.at(numLigne);
}

//!
//! \brief permet de comparer 2 Lignes
//! \param lig1
//! \param lig2
//! \return la ligne la plus proche du debut de l'alphabet
//! \author Lacoste Dorian
//! \date 16/12/18
//!
bool compareLigne(Ligne* lig1, Ligne* lig2){
    int idCase=lig1->obtenirNumCaseSelectionnerTri();
    std::string texte1 = (dynamic_cast<ZoneTexte * >(lig1->obtenirCase(idCase)->obtenirDonnee()))->obtenirTexte();
    std::string texte2 = (dynamic_cast<ZoneTexte * >(lig2->obtenirCase(idCase)->obtenirDonnee()))->obtenirTexte();
    if(isdigit(texte1[0])){ //test si le string est un nombre
        return std::stoi(texte1) > std::stoi(texte2); //on compare des int
    }
    return (texte1 < texte2);
}



//!
//! \brief trie le tableau en fonction d'une case de reference
//! \param c la case ou s'effectue le tri
//! \author Lacoste Dorian
//! \date 16/12/18
//!
bool
Tableau::trie(Case * c){
    ZoneTexte * zone = dynamic_cast<ZoneTexte * >(c->obtenirDonnee());
    if(zone == nullptr) return false;
    if(zone->obtenirTexte() == " ") return false;

    for(auto *l : m_lignes){
        l->definirNumCaseSelectionnerTri(c->obtenirIdCase());
    }
    std::sort(m_lignes.begin(), m_lignes.end(), compareLigne);
    int i=0;
    for (auto *l : m_lignes)
    {
        l->definirNumCouleur(i%2+1);
        l->redimensionner(creerRectLigne(i)); //deplace les lignes
        i++;
    }
    return true;
}

//!
//! \brief Tableau::testTri
//! \param l la ligne ou c'est effectué le clique
//! \param coord_souris
//! \return true si le trie c'est effectué (clique sur l'entete) , false sinon
//! \author Lacoste Dorian
//! \date 16/12/18
//!
//bool
//Tableau::testTri(Ligne * l, std::pair<int, int> coord_souris){
////    if(l == m_enTete){
////        this->trie(m_enTete->caseClique(coord_souris));
////        return true;
////    }
//    return  false;
//}



//!
//! \brief ajoute une ligne contenant des affichables dans le tableau
//! \param affichables
//! \author Lacoste Dorian
//! \date 12/12/18
//!
void
Tableau::ajouterLigne(std::vector<Affichable*> affichables){
      creerLigne(affichables);
}
//!
//! \brief Ajouter un humain dans le tableau
//! \param perso
//! \author Lacoste Dorian, Anthony Regnies
//! \date 22/11/18
//!
//!
void
Tableau::ajouterLigne(Humain* perso){
      std::vector<Affichable*> tmp;
    tmp.push_back(creeZoneTexte(perso->obtenirNom()));
    tmp.push_back(creeZoneTexte(perso->obtenirPrenom()));
    tmp.push_back(creeZoneTexte(std::to_string((int)perso->obtenirChasse().obtenirValeur())));
    tmp.push_back(creeZoneTexte(std::to_string((int)perso->obtenirRecolte().obtenirValeur())));
    tmp.push_back(creeZoneTexte(std::to_string((int)perso->obtenirCampement().obtenirValeur())));
    tmp.push_back(creeZoneTexte(perso->obtenirArme()->obtenirNom()));
    tmp.push_back(creeZoneTexte(std::to_string((int)perso->obtenirNiveau().obtenirNiveauActuel())));
    creerLigne(tmp);
}

void
Tableau::ajouterLigne(std::vector<std::string> strings){
    std::vector<Affichable*> tmp;
    for(std::string s : strings){
        tmp.push_back(creeZoneTexte(s));
    }
    creerLigne(tmp);
}

//!
//! \brief Tableau::creeZoneTexte
//! \param donnee
//! \author Lacoste Dorian
//! \date 09/12/18
//! \return un affichable zoneTexte
//!
ZoneTexte *
Tableau::creeZoneTexte(std::string donnee, COMPORTEMENT_TEXTE comportment, ALIGNEMENT_TEXTE alignement){
    return new ZoneTexte(POLICE_COLLEGED, 12, m_rectangle, donnee, SDL_Color{0,0,0,255}, comportment, alignement);
}

//!
//! \brief Ajouter un objet dans le tableau
//! \param obj
//! \author Lacoste Dorian
//! \date 15/11/2018
void
Tableau::ajouterLigne(Objet* obj){
    std::vector<Affichable *> tmp;
    tmp.push_back(obj->obtenirSprite());
    tmp.push_back(creeZoneTexte(obj->obtenirNom()));
    tmp.push_back(creeZoneTexte(obj->obtenirDescription()));

    creerLigne(tmp);
}

void Tableau::ajouterLigne(Campement *c)
{
     std::vector<Affichable *> tmp;
    std::map<PartieBus*, unsigned short> cpt;
    //Pour chaque partie bus
    for (Objet *o : c->obtenirObjets())
    {
        if (o->obtenirType()==TypeObjet::Partie_bus)
        {

            PartieBus *p = dynamic_cast<PartieBus *> (o);
            bool ajoute = false;
            //Compter le nombre
            if (cpt.size()!=0)
            {
                for (std::map<PartieBus*, unsigned short>::iterator it = cpt.begin(); it != cpt.end(); ++it)
                {
                    if (p->obtenirTypePartie()==it->first->obtenirTypePartie()) //Quand je le trouve
                    {
                        ajoute=true;
                        it->second++;
                    } else if (it->first==cpt.rbegin()->first && !ajoute)
                    {
                        cpt.insert(cpt.begin(), std::make_pair(p, 1));
                    }
                }
            } else {
                cpt.insert(cpt.begin(), std::make_pair(p, 1));
            }
        }
    }
    for (std::map<PartieBus*, unsigned short>::iterator it = cpt.begin(); it != cpt.end(); ++it)
    {
        //Inserer nom
        tmp.push_back(creeZoneTexte(it->first->obtenirNom()));
        //Inserer description
        tmp.push_back(creeZoneTexte(it->first->obtenirDescription()));
        //Inserer la quantite
        tmp.push_back(creeZoneTexte(std::to_string(it->second)));
        creerLigne(tmp);
        tmp.clear();
    }
}


//!
//! \brief Créer une ligne
//! \param donneesLigne
//! \author Lacoste Dorian
//! \date 15/11/2018
void
Tableau::creerLigne(std::vector<Affichable *> donneesLigne){
    Ligne *l = new Ligne(donneesLigne, this->m_controleur, creerRectLigne(), (m_lignes.size()%2 ==0) ? 1:2, m_lignes.size()+1, m_avecImage);
    m_lignes.push_back(l);
    m_rectangle.h+=l->rectangle().h;
}

//!
//! \brief Créer le rectangle ou s'affichera la ligne
//! \return SDL_Rect : la rectangle de la ligne
//! \author Lacoste Dorian, Anthony Regnies
//! \date 22/11/18
//!
SDL_Rect
Tableau::creerRectLigne(){
    return creerRectLigne(m_lignes.size());
}
SDL_Rect
Tableau::creerRectLigne(int numLigne){
    SDL_Rect rectangleParLigne = m_rectangle;
    rectangleParLigne.y=this->m_rectangle.y + this->m_hauteurLigne * numLigne;
    rectangleParLigne.h= this->m_hauteurLigne+1;
    return rectangleParLigne;
}




ZoneDefilable * Tableau::obtenirZoneDefilableTableau(SDL_Rect rectAffichable){
    return new ZoneDefilable(this,SDL_Color{100, 100, 100,255}, this->m_controleur,true,rectAffichable);
}

void Tableau::vider(){
    for(auto & l : m_lignes)
        delete l;
    m_lignes.clear();
    m_rectangle.h=0;

}
