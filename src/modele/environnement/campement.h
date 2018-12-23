#ifndef campement_h
#define campement_h

#include "personnage.h"
#include "equipe.h"
#include "vivre.h"
#include "humain.h"
#include "utilitaires.h"
#include <vector>
#include <string>

class Campement : public Observable
{
private:
    unsigned short m_quantiteVivre;
    std::set <Vivre*> m_stockVivre;
    std::set <Humain*> m_personnesNonAttribuees;
    Equipe m_equipeRecolte;
    Equipe m_equipeChasse;
    Equipe m_equipeCampement;
    std::vector <Objet *> m_objets;
    bool rechercherPersonnage(std::set <Personnage*> set, Personnage * p);
    bool rechercherHumain(std::set <Humain*> set, Personnage * p);
public:
    Campement();

    void ajouterPersonne(Humain *perso, Equipe *equipe);
    void ajouterPersonne(Humain *humain);
    void ajouterVivre(Vivre vivre);
    unsigned short obtenirNbVivres() const;
    int consommerVivre();
    int obtenirConsommation() ;
    void supprimerPersonnage(Personnage * p);
    Equipe * obtenirEquipePersonnage(Personnage * p);
    std::set<Humain *>& obtenirNonAttribuees();

    Equipe* obtenirEquipeChasse();
    Equipe* obtenirEquipeRecolte();
    Equipe* obtenirEquipeCampement();

    std::string serialiser() const;
    void charger(std::__cxx11::string &donnees);
    void ajouterObjet(Objet* obj);
    std::set<Vivre *> obtenirVivres();

    std::vector <Objet *> obtenirObjets();
    int obtenirValeurNutritiveDisponible() const;
};

#endif
