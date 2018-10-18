#ifndef inventaire_h
#define inventaire_h

#include <vector>
#include "../objets/objet.h"
#include "../objets/armes/arme.h"
#include "vivre.h"

//!
//! \brief Classe de gestion de l'inventaire
//! \date 03/11/2016
//!

class Inventaire
{
private:
    std::vector<Objet*> m_objets; /// Liste des objets dans l'inventaire
    unsigned short m_tailleMaximum = 10; /// Taille maximum de l'inventaire
public:
    Inventaire();
    ~Inventaire();
    std::vector<Objet *> obtenirObjets() const;
    unsigned short obtenirTailleMax() const;
    unsigned short obtenirNombreObjet() const;
    void ajouterObjet(Objet *objet);
    void supprimerObjet(Objet *objet);
    bool estPlein() const;
    std::string serialiser() const;
    void charger(const std::string &donnees);
    void chargerDansConteneur(const std::string &donnees);
};

#endif
