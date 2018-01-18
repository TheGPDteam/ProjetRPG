#ifndef equipe_h
#define equipe_h

#include <vector>
#include <set>
#include <algorithm>
#include <assert.h>
#include "personnage.h"
#include "zombie.h"
#include "humain.h"
#include "utilitaires.h"

class Equipe
{
private:
    std::set<Personnage*> m_personnages;
public:
    Equipe();
    Equipe(std::set<Personnage*> personnages);
    Equipe(Personnage* personnage);
    std::set<Personnage*> obtenirListePersonnage();
    void supprimerPersonnage(Personnage *personnage);
    void ajouterPersonnage(Personnage* personnage);
    static Equipe *genererEquipeZombie();

    std::set<Personnage *>::iterator begin(){
        return m_personnages.begin();
    }
    std::set<Personnage *>::iterator end(){
        return m_personnages.end();
    }
    std::string serialiser() const;
    void charger(std::__cxx11::string &donnees);
};

#endif
