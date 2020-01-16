#include "modele.h"
#include <utility>

using namespace std;

//! \file fichier modele
//! \date 17/11/16
//! \version 0.1

//!
//! \brief Constructeur par defaut de la classe modele
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
//! Construit un objet de la classe modele
//!
Modele::Modele()
    : m_joueur{Quete(TypeQuete::QUETERECOLTE, "Survivre aujourd'hui","Récolter assez de nourriture pour pouvoir passer la nuit",
                     50, 50, new Vivre())},
      m_deplacementDepuisDernierCombat{0}, m_nouvelArrivant{nullptr}, m_perdu{false},
      m_nbPersosMorts{0}, m_nbZombiesAttaquant{0}, m_nbZombiesTues{0}, m_td{TypeDefaite::PASDEDEFAITE}
{
    premiereJournee();
}


//!
//! \brief Accesseur en lecture du nom de la partie
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
//! Renvoit le nom de la partie
//!
std::string Modele::obtenirNomPartie() const{
    return m_nomPartie;
}


//!
//! \brief Accesseur en ecriture du nom de la partie
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! @param nom : Nouveau nom de la partie
//!
void Modele::definirNomPartie(std::string nom){
    m_nomPartie=nom;
}


//!
//! \brief Modele::testerDeplacement
//! \param dir
//! \return
//!
bool Modele::testerDeplacement(Direction& dir){
    int largeurCarte = m_carte.obtenirZoneActive()->obtenirLargeur();
    int hauteurCarte = m_carte.obtenirZoneActive()->obtenirHauteur();
    int posX = m_joueur.obtenirPosition().first;
    int posY = m_joueur.obtenirPosition().second;

    switch(dir){
    case Nord:
        return posY - 1 >= 0 && m_carte.obtenirZoneActive()->obtenirTuile(make_pair(posX, posY-1))->obtenirEstMarchable();
    case Sud:
        return posY + 1 < hauteurCarte && m_carte.obtenirZoneActive()->obtenirTuile(make_pair(posX, posY+1))->obtenirEstMarchable();
    case Ouest:
        return posX - 1 >= 0 && m_carte.obtenirZoneActive()->obtenirTuile(make_pair(posX-1, posY))->obtenirEstMarchable();
    case Est:
        return posX + 1 < largeurCarte && m_carte.obtenirZoneActive()->obtenirTuile(make_pair(posX+1, posY))->obtenirEstMarchable();
    default :
        return false;
    }
}


//!
//! \brief Permet de gérer le déplacement du personnage
//! \author mleothaud
//! \date 17/11/16
//! \version 2.0
//! @param dir : la direction du déplacement
//!
void Modele::deplacement(Direction dir){
    //On teste si le déplacement est possible
    if(testerDeplacement(dir)){
        m_deplacementDepuisDernierCombat++;
        m_joueur.deplacerJoueur(dir);
        Zone * zoneActive = m_carte.obtenirZoneActive();

        pair<int, int> position = m_joueur.obtenirPosition();
        ZoneChangementZone * zoneChangement = zoneActive->obtenirChangement(&m_joueur);
        if (zoneChangement != nullptr){

            m_carte.changerZoneActive(zoneChangement->obtenirNumeroZone());
            std::pair<int,int> arrive = zoneChangement->obtenirPositionArrive();
            //m_joueur.definirPosition(arrive);

        } else if(zoneActive->objetPresent(position)){

            if(!m_joueur.obtenirInventaire()->estPlein()){
                Objet * objet = zoneActive->obtenirObjet(position);
                m_joueur.obtenirInventaire()->ajouterObjet(objet);


                if(objet->obtenirType() == TypeObjet::Vivre){
                    Quete * q = m_joueur.obtenirQuete();
                    Vivre* v = dynamic_cast<Vivre*>(objet);
                    q->augmenterValeur(v->obtenirValeurNutritive());
                    if (q->obtenirValeurObjectif()<= q->obtenirValeurAvancement() && !q->estfini()){
                        m_campement.ajouterObjet(q->obtenirRecompense());
                        q->finir();
                    }
                }

                zoneActive->supprimerObjet(objet);
            } else {
                std::cout << "Inventaire plein !" << std::endl;
            }
        }
        // Si l'on rencontre une équipe de zombie, on lance un combat
        else if (zoneActive->equipeZombiePresente(position))
        {
            Equipe* equipeZombie = zoneActive->obtenirEquipeZombie(position);
            Combat combat = Combat(m_joueur.obtenirEquipe(), equipeZombie);
            combat.simulerCombat();

            if (false)//m_joueur.obtenirPersonnageJoueur()->obtenirVie()->obtenirValeur() > 0)
            {
                if (!m_joueur.obtenirInventaire()->estPlein())
                {
                    Objet* recompense = combat.obtenirRecompense();
                    if (recompense != nullptr)
                        m_joueur.obtenirInventaire()->ajouterObjet(recompense);
                    else
                    {
                        std::cout<< "Vous n'avez rien gagne !" << std::endl;
                    }
                }
                else
                {
                    std::cout << "Inventaire plein" << std::endl;
                }
                zoneActive->supprimerEquipeZombie(equipeZombie);
            }
            else
            {
                std::cout << "mklklmklmmkllmklmkklmklmmklmklklmmklklmmkl" << std::endl;
                m_perdu = true;
                m_td = TypeDefaite::ATTAQUEZOMBIES;
            }
            mettreAChange();
            notifierTous();

        }
    }
}


//!
//! \brief Permet de gérer le cas d'un changement de carte lorsque l'on est sur une tuile de changement
//! \author dolacoste
//! \date 21/12/17
//! \version 2.0
//!
bool Modele::testChangementDeCarte(Direction directionDep){
    std::pair<int,int> nouvellePosition = m_joueur.obtenirPosition();

    bool changementCarte=false;
    // On teste si on est sur une case qui a une direction pour changer de carte, alors on change donc la zone active en fonction de cette direction
    Direction directionTuile = m_carte.obtenirZoneActive()->obtenirTuile(nouvellePosition)->obtenirDirectionChangementZone();
    if (directionTuile == Nord && directionDep==Nord) {
        nouvellePosition.first = m_joueur.obtenirPosition().first;
        nouvellePosition.second = 63;
        m_carte.changerZoneActive(Nord);
        changementCarte=true;

    } else if (directionTuile ==Sud && directionDep==Sud) {
        nouvellePosition.first = m_joueur.obtenirPosition().first;
        nouvellePosition.second = 0;
        m_carte.changerZoneActive(Sud);
        changementCarte=true;
    } else if (directionTuile ==Ouest && directionDep==Ouest) {
        nouvellePosition.first = 63;
        nouvellePosition.second = m_joueur.obtenirPosition().second;
        m_carte.changerZoneActive(Ouest);
        changementCarte=true;
    } else if (directionTuile==Est && directionDep==Est) {
        nouvellePosition.first = 0;
        nouvellePosition.second = m_joueur.obtenirPosition().second;
        m_carte.changerZoneActive(Est);
        changementCarte=true;
    }

    if(changementCarte)  m_joueur.definirPosition(nouvellePosition);

    return changementCarte;
}


//!
//! \brief Permet d'avancer sur une journee, controle les etapes d'une journee
//! \author mleothaud
//! \date 17/11/16
//! \version 0.0.1
//!
//! Un survivant arrive, on choisit de le garder ou pas, on l'affecte a une quete si oui,
//! on part ensuite en quete pendant 10 minutes
//!
Humain* Modele::journeeSuivante(){
    m_nouvelArrivant = new Humain();
    ++m_nbJoursPasses;
    m_temps->reinitialiserTemps();
    m_joueur.nouvelleQuete(TypeQuete::QUETERECOLTE,"Survivre","Recolter de la nouriture",
                           m_campement.obtenirConsommation(),
                           50,new Vivre());
    return m_nouvelArrivant;
}


//!
//! \brief Permet de lancer un combat
//! \author mleothaud
//! \date 17/11/16
//! \version 0.0.2
//!
void Modele::lancerCombat(){
    int probabilite = 95;
    if (rand() % 100 < probabilite)   Combat combat(m_joueur.obtenirEquipe());
    else {
        std::set<Personnage *> personnagesAdverses;
        for (int i = 0; i < 4; ++i){
            Humain *h = new Humain();
            personnagesAdverses.insert(h);
        }

        Equipe *e = new Equipe(personnagesAdverses);
        Combat combat(m_joueur.obtenirEquipe(), e);
    }
}


//!
//! \brief Permet la gestion de la premiere journee, differente des autres
//! \author mleothaud
//! \date 17/11/16
//! \version 0.1
//!
//! Création d'une équipe de sept personnages
//!
void Modele::premiereJournee(){
    for(int i = 0; i < 7; ++i) {
        Humain * h = new Humain();
        m_campement.obtenirNonAttribuees().insert(h);
    }

    m_nbJoursPasses = 0;
    m_joueur.definirEquipe(m_campement.obtenirEquipeRecolte());
    // Calcul de la quantité de vivres à obtenir pour survivre au jour suivant. Si les vivres possédés sont supérieurs à la consommation,
    // le calcul se fait pour plusieurs jours à l'avance.
    m_joueur.obtenirQuete()->definirValeurObjectif(m_campement.obtenirConsommation());
    m_temps = new Temps();
    m_temps->reinitialiserTemps();
    mettreAChange();
    notifierTous();
}


//!
//! \brief Accesseur en lecture du temps
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
Temps* Modele::obtenirTemps(){
    return m_temps;
}


//!
//! \brief Accesseur en lecture de la carte
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
Carte * Modele::obtenirCarte(){
    return &m_carte;
}


//!
//! \brief Accesseur en ecriture de la carte
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
void Modele::definirCarte(Carte carte){
    m_carte = carte;
}


//!
//! \brief Accesseur en lecture du campement
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
Campement * Modele::obtenirCampement(){
    return &m_campement;
}


//!
//! \brief Accesseur en ecriture du campement
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
void Modele::definirCampement(Campement campement){
    m_campement=campement;
}


//!
//! \brief Accesseur en lecture du combat
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
Combat * Modele::obtenirCombat(){
    return &m_combat;
}


//!
//! \brief Accesseur en ecriture du combat
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
void Modele::definirCombat(Combat combat){
    m_combat=combat;
}


//!
//! \brief Accesseur en lecture du joueur
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
Joueur* Modele::obtenirJoueur(){
    return &m_joueur;
}


//!
//! \brief Serialise les attributs du modèle
//! \return Chaine contenant les attributs du modèle au format XML
//! \author nlesne
//! \date 12/11/17
//! \version 0.1
//!
std::string Modele::serialiser() const {
    return "<Modele><NomPartie>" + m_nomPartie + "</NomPartie>"
            + m_campement.serialiser()
            + m_joueur.serialiser()
            + "</Modele>";
}


void Modele::charger(const std::string &donnees){
    m_nomPartie = obtenirSousChaineEntre2Predicats(donnees,"<NomPartie>","</NomPartie>");
    std::string donneesCampement = obtenirSousChaineEntre2Predicats(donnees,"<Campement>","</Campement");
    m_campement = Campement();
    m_campement.charger(donneesCampement);
    m_joueur.charger(obtenirSousChaineEntre2Predicats(donnees,"<Joueur>","</Joueur>"));
}


void Modele::reinitialiserTemps() {
    m_temps->reinitialiserTemps();
}

//!
//! \brief Met a jour les attributs de la fin de journee
//! \author mleothaud
//! \date 17/01/18
//! \version 0.1
//!
void Modele::finJournee() {
    //Trouver la formule pour savoir combien de morts
    if(QuetePrincipale::obtenirInstance()->estLance())
    {
        QuetePrincipale::obtenirInstance()->incrementerTempQuetePrincipale();
    }

    if (m_joueur.obtenirQuete()->obtenirType() == TypeQuete::QUETERECOLTE){
        int totalChasseEquipeChasse=0;
        for (Personnage *p : m_campement.obtenirEquipeChasse()->obtenirListePersonnage()){
            Humain *h = (Humain*) (p);
            totalChasseEquipeChasse+=h->obtenirChasse().obtenirValeur();
        }

        //On affecte une valeur au nombre de zombies qui ont été tués dans la journée par l'équipe chasse
        if (totalChasseEquipeChasse != 0){
            m_nbZombiesTues = rand()%totalChasseEquipeChasse;
        } else {
            m_nbZombiesTues = 0;
        }
    }
    //On affecte un nombre de zombies attaquant qui dépend du nombre de zombies tues dans la journée et du nombre de jours passés
    m_nbZombiesAttaquant = (50 * m_nbJoursPasses) - m_nbZombiesTues;

    //On calcule si et combien de personnages du campement sont morts dans la nuit
    unsigned int totalChasseCampement=0;
    for (Personnage *p : m_campement.obtenirEquipeChasse()->obtenirListePersonnage()){
        Humain *h = (Humain*) (p);
        totalChasseCampement+=h->obtenirChasse().obtenirValeur();
    }

    for (Personnage *p : m_campement.obtenirEquipeRecolte()->obtenirListePersonnage()){
        Humain *h = (Humain*) (p);
        totalChasseCampement+=h->obtenirChasse().obtenirValeur();
    }

    for (Personnage *p : m_campement.obtenirNonAttribuees()){
        Humain *h = (Humain*) (p);
        totalChasseCampement+=h->obtenirChasse().obtenirValeur();
    }

    if (m_nbZombiesAttaquant > totalChasseCampement)  m_nbPersosMorts = (m_nbZombiesAttaquant - totalChasseCampement) / 25;
    else                                              m_nbPersosMorts = 0;


    if (m_nbPersosMorts > 0) {
        //Verifier si on a assez de personnes à tuer
        unsigned int nbPersosCamp = 0;
        nbPersosCamp+=m_campement.obtenirEquipeRecolte()->obtenirListePersonnage().size();
        nbPersosCamp+=m_campement.obtenirEquipeChasse()->obtenirListePersonnage().size();
        nbPersosCamp+=m_campement.obtenirEquipeCampement()->obtenirListePersonnage().size();
        nbPersosCamp+=m_campement.obtenirNonAttribuees().size();
        if (nbPersosCamp>m_nbPersosMorts){
            tuerPersos();
        } else {
            m_perdu = true;
            //TODO : Mettre à 0 les valeurs de jeu (équipes, inventaires, ...)
            m_td = TypeDefaite::ATTAQUEZOMBIES;
        }
    }

    //Consommation de vivres

    //Transfert de l'inventaire du joueur vers le campement
    for (Objet* o : m_joueur.obtenirInventaire()->obtenirObjets()){
        m_campement.ajouterObjet(o);
        m_joueur.obtenirInventaire()->supprimerObjet(o);
    }

    //On vérifie que l'on a bien plus de vivres dans le camp que de besoins
    int valeurNutritiveTotaleCamp = 0;
    for (Vivre * v : m_campement.obtenirVivres()){
        valeurNutritiveTotaleCamp+=v->obtenirValeurNutritive();
    }

    if (valeurNutritiveTotaleCamp > m_campement.obtenirConsommation()){
        //On consomme jusqu'à ce que la valeur nutritive consommee couvre les besoins du campement
        int valeurNutritiveConsommee = 0;
        m_vivresConsommesNuit = 0;
        while (valeurNutritiveConsommee < m_campement.obtenirConsommation()){
            valeurNutritiveConsommee += m_campement.consommerVivre();
            ++m_vivresConsommesNuit;
        }
    } else {
        //TODO : Tuer les gens mais ne perdre que si tout le monde meurt
        m_nbPersosMorts = (valeurNutritiveTotaleCamp - m_campement.obtenirConsommation()) / 30;
        unsigned int nbPersosCamp = 0;
        nbPersosCamp+=m_campement.obtenirEquipeRecolte()->obtenirListePersonnage().size();
        nbPersosCamp+=m_campement.obtenirEquipeChasse()->obtenirListePersonnage().size();
        nbPersosCamp+=m_campement.obtenirEquipeCampement()->obtenirListePersonnage().size();
        nbPersosCamp+=m_campement.obtenirNonAttribuees().size();
        if (m_nbPersosMorts > nbPersosCamp){
            m_perdu=true;
            //TODO : Mettre à 0 les valeurs de jeu (équipes, inventaires, ...)
            m_td = TypeDefaite::FAMINE;
        } else {
            tuerPersos();
        }
    }

    //Reapprovisionnement de la carte en objets*
    m_carte.recharger();
    mettreAChange();
    notifierTous();
}


unsigned int Modele::obtenirNbPersosMorts() const {
    return m_nbPersosMorts;
}


unsigned int Modele::obtenirNbZombiesAttaquants() const{
    return m_nbZombiesAttaquant;
}


unsigned int Modele::obtenirNbZombiesTues() const{
    return m_nbZombiesTues;
}


unsigned int Modele::obtenirVivresConsommesNuit() const{
    return m_vivresConsommesNuit;
}


bool Modele::perdu() {
    return m_perdu;
}


TypeDefaite Modele::obtenirTypeDefaite() const {
    return m_td;
}


Humain * Modele::obtenirNouvelArrivant(){
    return m_nouvelArrivant;
}


void Modele::changerNouvelArrivant(Humain * h){
    m_nouvelArrivant = h;
    mettreAChange();
    notifierTous();
}


void Modele::tuerPersos() {
    //TODO
    for (unsigned int i = 0; i < m_nbPersosMorts; ++i){
        bool persoMort = false;
        while (!persoMort) {
            switch (rand()%3) {
            case 0:
                //On tue un mec de recolte
                if (m_campement.obtenirEquipeRecolte()->obtenirListePersonnage().size()>0)
                {
                    m_campement.obtenirEquipeRecolte()->obtenirListePersonnage().erase(m_campement.obtenirEquipeRecolte()->obtenirListePersonnage().begin());
                    persoMort = true;
                }
                break;
            case 1:
                //On tue un mec de chasse
                if (m_campement.obtenirEquipeChasse()->obtenirListePersonnage().size()>0)
                {
                    m_campement.obtenirEquipeChasse()->obtenirListePersonnage().erase(m_campement.obtenirEquipeRecolte()->obtenirListePersonnage().begin());
                    persoMort = true;
                }
                break;
            case 2:
                //On tue un mec non attribué
                if (m_campement.obtenirNonAttribuees().size()>0)
                {
                    m_campement.obtenirNonAttribuees().erase(m_campement.obtenirNonAttribuees().begin());
                    persoMort = true;
                }
                break;
            default:
                break;
            }
        }
    }
}
