#ifndef campement_h
#define campement_h

#include "../personnages/personnage.h"
#include "../survie/equipe.h"
#include "../survie/vivre.h"
#include "../personnages/humain.h"
#include "../utilitaires.h"
#include <vector>
#include <string>

class Campement
{
private:
    unsigned short m_quantiteVivre;
    std::set <Vivre*> m_stockVivre;
    std::set <Humain*> m_personnesNonAttribuees;
    Equipe m_equipeRecolte;
    Equipe m_equipeChasse;
    std::vector <Objet *> m_objets;
public:
    Campement();

    void ajouterPersonne(Humain *perso, Equipe *equipe);
    void ajouterPersonne(Humain *humain);
    void ajouterVivre(Vivre vivre);
    unsigned short obtenirNbVivres() const;
    int consommerVivre();
    int obtenirConsommation() ;

    std::set<Humain *>& obtenirNonAttribuees();

    Equipe* obtenirChasse();
    Equipe* obtenirRecolte();
    Equipe* obtenirCampement();

    std::string serialiser() const;
    void charger(std::__cxx11::string &donnees);
    void ajouterObjet(Objet* obj);
    std::set<Vivre *> obtenirVivres();

    std::vector <Objet *> obtenirObjets();
    int obtenirValeurNutritiveDisponible() const;
};

#endif
