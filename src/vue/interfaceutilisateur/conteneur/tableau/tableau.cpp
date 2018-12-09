#include "tableau.h"

Tableau::Tableau(SDL_Rect rect, float hauteurLigne, Controleur *controleur)
    :Affichable{rect},m_hauteurLigne {hauteurLigne}, m_controleur{controleur}, m_nbLignes{0}
{
}


//!
//! \brief affiche le contenu du tableau
//! \param surface_affichage
//! \author Lacoste Dorian
//! \date 15/11/2018
//!
void Tableau::afficher(SDL_Surface *surface_affichage)
{
    m_enTete->afficher(surface_affichage);
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
    SDL_Rect rectangleLigne = nouvelleDimension;
    rectangleLigne.h = rectangleLigne.h / m_lignes.size();
    for (Ligne * l : m_lignes)
    {
        l->redimensionner(rectangleLigne);
        rectangleLigne.y += m_hauteurLigne;
    }
}
//!
//! \brief indique la ligne survolé
//! \param coord_souris
//! \return la ligne survolé par la souris
//! \author Lacoste Dorian, Regnies Anthony
//! \date 22/11/18
//!
Ligne*
Tableau::ligneSurvole(std::pair<int, int> coord_souris){
    for(Ligne *l : m_lignes){
        if(l->contient(coord_souris))
            return l;
    }
    return nullptr;
}

void
Tableau::ajouterEnTeteHumain(){
    std::vector<Affichable *> tmp;
    tmp.push_back(creeZoneTexte("Nom"));
    tmp.push_back(creeZoneTexte("Prenom"));
    tmp.push_back(creeZoneTexte("Chasse"));
    tmp.push_back(creeZoneTexte("Recolte"));
    tmp.push_back(creeZoneTexte("Campement"));
    tmp.push_back(creeZoneTexte("Arme"));
    tmp.push_back(creeZoneTexte("Niveau"));
    m_enTete = new Ligne(tmp, m_controleur,creerRectLigne(), 0);
    m_nbLignes++;
}

void
Tableau::ajouterEnTeteObjet(TypeObjet typeObjet){
    std::vector<Affichable *> tmp;
    tmp.push_back(creeZoneTexte("Nom"));
    tmp.push_back(creeZoneTexte("Description"));
    if(typeObjet == TypeObjet::Partie_bus ) {
        tmp.push_back(creeZoneTexte("Quantite"));
    }
    //    }else if(typeObjet == TypeObjet::Vivre){
    //        tmp.push_back("ValeurNutritive");
    //    }
    m_enTete = new Ligne(tmp, m_controleur, creerRectLigne(), 0);
    m_nbLignes++;
}

void Tableau::ajouterEnTetePartiesBus(){
    std::vector<Affichable *> tmp;
    //    tmp.push_back("Icone");
    tmp.push_back(creeZoneTexte("Nom"));
    tmp.push_back(creeZoneTexte("Description"));
    tmp.push_back(creeZoneTexte("Quantite"));
    //    if(typeObjet == TypeObjet::Arme ) {
    //        tmp.push_back("Degats");
    //        tmp.push_back("Vitesse");
    //        tmp.push_back("Chance");
    //    }else if(typeObjet == TypeObjet::Vivre){
    //        tmp.push_back("ValeurNutritive");
    //    }
    m_enTete = new Ligne(tmp, m_controleur, creerRectLigne(), 0);
    m_nbLignes++;
}


void
Tableau::ajouterLigne(std::vector<Affichable*> affichables){
    assert (m_enTete != nullptr); //l'entete doit etre defini avant d'ajouter des objets
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
    assert (m_enTete != nullptr); //l'entete doit etre defini avant d'ajouter des objets
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

//!
//! \brief Tableau::creeZoneTexte
//! \param donnee
//! \author Lacoste Dorian
//! \date 09/12/18
//! \return un affichable zoneTexte
//!
ZoneTexte *
Tableau::creeZoneTexte(std::string donnee){
    return new ZoneTexte(POLICE_COLLEGED, 12, std::make_pair(0,0), SDL_Rect(), donnee, SDL_Color{0,0,0,255}, COMPORTEMENT_TEXTE::REDIMENTIONNE, ALIGNEMENT_TEXTE::CENTRE);
}

//!
//! \brief Ajouter un objet dans le tableau
//! \param obj
//! \author Lacoste Dorian
//! \date 15/11/2018
void
Tableau::ajouterLigne(Objet* obj){
    assert (m_enTete != nullptr); //l'entete doit etre defini avant d'ajouter des objets
    std::vector<Affichable *> tmp;
    tmp.push_back(creeZoneTexte(obj->obtenirNom()));
    tmp.push_back(creeZoneTexte(obj->obtenirDescription()));
    //    if(obj->obtenirType() == TypeObjet::Arme ) {
    //        Arme * arme = dynamic_cast<Arme *>(obj);
    //        tmp.push_back(,std::to_string((int)arme->obtenirDegats()));
    //        tmp.push_back(std::to_string((int)arme->obtenirVitesse()));
    //        tmp.push_back(std::to_string((int)arme->obtenirChance()));
    //    }else if(obj->obtenirType() == TypeObjet::Vivre){
    //        Vivre * vivre = dynamic_cast<Vivre*>(obj);
    //        tmp.push_back(std::to_string(vivre->obtenirValeurNutritive()));
    //    }
    creerLigne(tmp);
}

void Tableau::ajouterLigne(Campement *c)
{
    assert (m_enTete != nullptr); //l'entete doit etre defini avant d'ajouter des objets
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
            /*
            if (cpt.find(p) != cpt.end()) //Quand je le trouve
            {
                cpt.find(p)++;
            } else
            {
            }*/
        }
    }
    for (std::map<PartieBus*, unsigned short>::iterator it = cpt.begin(); it != cpt.end(); ++it)
    {
        /*            //Inserer l'icone
            if (it->first->obtenirTypePartie() == TypePartieBus::ROUE)
            {

            } else if (it->first->obtenirTypePartie() == TypePartieBus::ESSENCE)
            {

            } else if (it->first->obtenirTypePartie() == TypePartieBus::MOTEUR)
            {

            } else //HUILE
            {

            }
*/
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
    Ligne *l = new Ligne(donneesLigne, this->m_controleur, creerRectLigne(), (m_nbLignes%2 ==0) ? 1:2);
    m_lignes.push_back(l);
    m_nbLignes++;
}

//!
//! \brief Créer le rectangle ou s'affichera la ligne
//! \return SDL_Rect : la rectangle de la ligne
//! \author Lacoste Dorian, Anthony Regnies
//! \date 22/11/18
//!
SDL_Rect
Tableau::creerRectLigne(){
    SDL_Rect rectangleParLigne = m_rectangle;
    rectangleParLigne.y=this->m_rectangle.y + this->m_hauteurLigne * m_nbLignes;
    rectangleParLigne.h= this->m_hauteurLigne;
    return rectangleParLigne;
}


Tableau * Tableau::tableauHumain(SDL_Rect rect, float hauteurLigne, Controleur *controleur){
    Tableau * t = new Tableau(rect, hauteurLigne, controleur);
    t->ajouterEnTeteHumain();
    return t;
}

Tableau * Tableau::tableauObjet(SDL_Rect rect, float hauteurLigne, Controleur *controleur, TypeObjet typeObjet){
    Tableau * t = new Tableau(rect, hauteurLigne, controleur);
    t->ajouterEnTeteObjet(typeObjet);
    return t;
}

void Tableau::vider(){
    for(auto & l : m_lignes)
        delete l;
    m_lignes.clear();
    m_nbLignes = 1;
}
