#ifndef combat_h
#define combat_h

#include <array>
#include <vector>
#include <map>
#include <utility>
#include <random>
#include "equipe.h"
#include "personnage.h"
#include "actioncombat.h"

class Combat
{
private:
    Equipe* m_equipeBasse;
    Equipe* m_equipeHaute;
    std::array<Personnage*,8> m_ordrePassage;
    unsigned short m_numeroDePassage;
    std::pair<std::pair<Personnage*,Personnage*>,ActionCombat>m_actionDuTour;
public:
    Combat() = default;
    Combat(Equipe* equipeHaute, Equipe* equipeBasse);
    Combat(Equipe *equipeHaute);
    Equipe * obtenirEquipeHaute() const;
    Equipe * obtenirEquipeBasse() const;
    Personnage * prochainPersonnage();
    void effectuerAttaque(Personnage* agresseur, Personnage* cible);
    void tourSuivant();
    void ajouterAction(Personnage* cible, Personnage* source, ActionCombat action);
};

#endif
