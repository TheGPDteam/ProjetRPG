#ifndef equipe_h
#define equipe_h

#include <vector>
#include <set>
#include <algorithm>
#include <assert.h>
#include "personnage.h"
#include "zombie.h"

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
    Equipe *genererEquipeZombie();

    std::set<Personnage *>::iterator begin(){
        return m_personnages.begin();
    }
    std::set<Personnage *>::iterator end(){
        return m_personnages.end();
    }
    std::vector<std::string> serialiser() const;
};

#endif
