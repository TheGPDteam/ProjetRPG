#include "campement.h"

//! \file fichier campement
//! \date 17/11/16
//! \version 1.0

//!
//! \brief Constructeur par defaut de l'objet campement
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
//! Construit un objet de la classe campement en initialisant la quantite de vivres à 0
//!

Campement::Campement()
    :m_quantiteVivre{0}
{
}

//!
//! \brief Ajout d'un vivre au campement
//! \author mleothaud
//! \date 17/11/16
//! @param vivre : un vivre qui sera ajoute au stock des vivres
//! \version 1.0
//!
//! Ajout d'un vivre au stock du campement
//!

void Campement::ajouterVivre(Vivre vivre)
{
    Vivre *vivreBis = new Vivre(vivre);
    m_stockVivre.insert(m_stockVivre.begin(), vivreBis);
    m_quantiteVivre++;
}

//!
//! \brief Permet d'obtenir le nombre de vivres dans le campement
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return le nombre de vivres du campement
//!

unsigned short Campement::obtenirNbVivres() const
{
    return m_quantiteVivre;
}

//!
//! \brief Permet de consommer un Vivre
//! \author mleothaud
//! \date 17/11/16
//! @param nbVivresConsommes : Nombre de vivres que l'on doit consommer
//! \version 1.0
//!
//! Enleve les vivres du stock et decremente la quantite enregistree
//!

int Campement::consommerVivre()
{
    int valeurNutritive = 0;
    std::set<Vivre*>::iterator it = m_stockVivre.begin();
    Vivre *v = *it;
    valeurNutritive = v->obtenirValeurNutritive();
    m_stockVivre.erase(v);
    mettreAChange();
    notifierTous();
    return valeurNutritive;
}

//!
//! \brief supprime un personnage qui se trouve dans le camp
//! \param p le personnage a supprimer
//!
void Campement::supprimerPersonnage(Personnage * p){

    Equipe * equipePerso = obtenirEquipePersonnage(p);

    if(equipePerso== nullptr && rechercherHumain(m_personnesNonAttribuees, p)){
        m_personnesNonAttribuees.erase(dynamic_cast<Humain *>(p));
    }else{
        equipePerso->supprimerPersonnage(p);
    }
}

//!
//! \brief Campement::obtenirEquipePersonnage
//! \param h
//! \return l'equipe dans lequel est le personnage ou nullptr s'il n'est dans aucune equipe
//!
Equipe * Campement::obtenirEquipePersonnage(Personnage *p){
    std::vector<Equipe *> listesEquipe;
    listesEquipe.push_back(this->obtenirEquipeChasse());
    listesEquipe.push_back(this->obtenirEquipeRecolte());
    listesEquipe.push_back(this->obtenirEquipeCampement());
    for (Equipe * e : listesEquipe) {
        if(rechercherPersonnage(e->obtenirListePersonnage(), p)){
            return e;
        }
    }
    return nullptr;
}

//!
//! \brief Campement::rechercherPersonnage
//! \param set le set de recherche
//! \param p le personnage rechercher
//! \return true si le personnage se trouve dans le set, false sinon
//!
bool Campement::rechercherPersonnage(std::set <Personnage*> set, Personnage * p){
    std::vector<Personnage *> vectorDeRecherche(set.begin(), set.end());
    vectorDeRecherche.push_back(nullptr);
    return std::find(vectorDeRecherche.begin(), vectorDeRecherche.end(), p) != vectorDeRecherche.end();
}

bool Campement::rechercherHumain(std::set <Humain*> set, Personnage * p){
    std::vector<Humain *> vectorDeRecherche(set.begin(), set.end());
    vectorDeRecherche.push_back(nullptr);
    return std::find(vectorDeRecherche.begin(), vectorDeRecherche.end(), p) != vectorDeRecherche.end();
}

//!
//! \brief Retourne la consommation totale de tous les humains du campement
//! \return Consommation totale du campement
//! \author adeguilhem
//! \date 20/11/16
//! \version 0.1
//!
int Campement::obtenirConsommation()
{
    int somme = 0;
    for (Personnage *p : m_equipeChasse.obtenirListePersonnage()) {
        Humain * h = (Humain *) p;
        somme += h->obtenirConsommation();
    }
    for (Personnage *p : m_equipeRecolte.obtenirListePersonnage()) {
        Humain * h = (Humain *) p;
        somme += h->obtenirConsommation();
    }
    for (Personnage *p : m_personnesNonAttribuees)
    {
        Humain * h = (Humain *) p;
        somme += h->obtenirConsommation();
    }
    return somme;
}

//!
//! \brief Permet d'ajouter une personne au campement et de l'integrer a une equipe
//! \author mleothaud
//! \date 17/11/16
//! @param perso : Personnage à integrer
//! @param equipe : Equipe dans laquelle integrer le personnage
//! \version 1.0
//!
//! Ajoute le personnage à l'equipe desiree
//!

void Campement::ajouterPersonne(Humain *perso, Equipe *equipe)
{
    equipe->ajouterPersonnage(perso);
}

//!
//! \brief Permet d'ajouter une personne au campement et de l'integrer a une equipe
//! \author mleothaud
//! \date 11/12/17
//! @param perso : Personnage à integrer
//! \version 1.0
//!
//! Ajoute le personnage dans le campement
//!

void Campement::ajouterPersonne(Humain *humain)
{
    m_personnesNonAttribuees.insert(humain);
    mettreAChange();
    notifierTous();
}

//!
//! \brief Accesseur en lecture de l'equipe de chasse
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return l'equipe de chasse
//!

Equipe* Campement::obtenirEquipeChasse(){
    return &m_equipeChasse;
}

//!
//! \brief Accesseur en lecture de l'equipe de recolte
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return l'equipe de recolte
//!

Equipe* Campement::obtenirEquipeRecolte(){
    return &m_equipeRecolte;
}


//!
//! \brief Accesseur en lecture de l'equipe de campement
//! \author mleothaud
//! \date 13/11/18
//! \version 1.0
//! \return l'equipe de campement
//!

Equipe* Campement::obtenirEquipeCampement(){
    return &m_equipeCampement;
}

//!
//! \brief Serialisation du campement
//! \author nlesne
//! \date 16/10/17
//! \version 0.1
//! \return les donnees du campement
//!

std::string Campement::serialiser() const {
    std::string donnees_campement = "<Campement>"
                                    "   <QuantiteVivre>" + std::to_string(m_quantiteVivre) + "</QuantiteVivre>"
                                                                                             "   <StockVivre>";
    for (Vivre* v : m_stockVivre)
        donnees_campement += v->serialiser();
    donnees_campement += "</StockVivre>"
                         "   <EquipeRecolte>"
            + m_equipeRecolte.serialiser()
            + "</EquipeRecolte>"
              "   <EquipeChasse>"
            + m_equipeChasse.serialiser()
            + " </EquipeChasse>"
              " <PersonnesNonAttribuees>";
    for (Personnage* p : m_personnesNonAttribuees)
        donnees_campement += p->serialiser();
    donnees_campement += "</PersonnesNonAttribuees>"
                         "   </Campement>";

    return donnees_campement;
}

//!
//! \brief Accesseur en lecture / ecriture des personnages non attribués
//! \author mleothaud, adeguilhem
//! \date 06/11/17
//! \version 1.0
//!

std::set<Humain *> &Campement::obtenirNonAttribuees()
{
    return m_personnesNonAttribuees;
}

//!
//! \brief Chargement des attrubuts du campement
//! \author mpardo,nlesne
//! \date 17/01/18
//! \version 1.0
//!

void Campement::charger(std::string &donnees)
{
    m_quantiteVivre = std::stoi(obtenirSousChaineEntre2Predicats(donnees,"<QuantiteVivre>","</QuantiteVivre>"));

    if (donnees.find("<StockVivre>") != std::string::npos)
    {
        std::string donneesStockVivre = obtenirSousChaineEntre2Predicats(donnees,"<StockVivre>","</StockVivre>");
        while (!obtenirSousChaineEntre2Predicats(donneesStockVivre,"<Vivre>","</Vivre>").empty())
        {
            Vivre* v = new Vivre();
            v->charger(obtenirSousChaineEntre2Predicats(donneesStockVivre,"<Vivre>","</Vivre>"));
            ajouterObjet(v);
            supprimmerSousChaineEntre2Predicats(donneesStockVivre,"<Vivre>","</Vivre>");
        }
    }

    std::string donneesEquipeRecolte = obtenirSousChaineEntre2Predicats(donnees,"<EquipeRecolte>","</EquipeRecolte>");
    m_equipeRecolte = Equipe();
    m_equipeRecolte.charger(donneesEquipeRecolte);

    std::string donneesEquipeChasse = obtenirSousChaineEntre2Predicats(donnees,"<EquipeChasse>","</EquipeChasse>");
    m_equipeChasse = Equipe();
    m_equipeChasse.charger(donneesEquipeChasse);

    if (donnees.find("<PersonnesNonAttribuees>") != std::string::npos)
    {
        std::string donneesPersonnesNonAttribuees = obtenirSousChaineEntre2Predicats(donnees,"<PersonnesNonAttribuees>","</PersonnesNonAttribuees>");
        while (!obtenirSousChaineEntre2Predicats(donneesPersonnesNonAttribuees,"<Humain>","</Humain>").empty())
        {
            Humain* h = new Humain();
            h->charger(obtenirSousChaineEntre2Predicats(donneesPersonnesNonAttribuees,"<Humain>","</Humain>"));
            ajouterPersonne(h);
            supprimmerSousChaineEntre2Predicats(donneesPersonnesNonAttribuees,"<Humain>","</Humain>");
        }
    }
}

void Campement::ajouterObjet(Objet *obj) {
    if (obj->obtenirType()==TypeObjet::Vivre)
    {
        Vivre* v = dynamic_cast<Vivre *> (obj);
        m_stockVivre.insert(v);
    }
    else {
        m_objets.push_back(obj);
    }
    mettreAChange();
    notifierTous();
}

std::set<Vivre*> Campement::obtenirVivres()
{
    return m_stockVivre;
}


int Campement::obtenirValeurNutritiveDisponible() const
{
    int valeurTotale = 0;
    for (Vivre *v : m_stockVivre)
    {
        valeurTotale+=v->obtenirValeurNutritive();
    }
    return valeurTotale;
}

std::vector<Objet *> Campement::obtenirObjets() {
    return m_objets;
}
