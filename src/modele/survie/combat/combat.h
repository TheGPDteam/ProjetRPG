#ifndef combat_h
#define combat_h

#include <array>
#include <vector>
#include <map>
#include <utility>
#include <random>
#include "../equipe.h"
#include "../../personnages/personnage.h"
#include "actioncombat.h"

class Combat
{
private:
    Equipe* m_equipeBasse;
    Equipe* m_equipeHaute;
    std::array<Personnage*,8> m_ordrePassage;
    unsigned short m_numeroDePassage;
    ActionCombat* m_actionDuTour;
public:
    Combat() = default;
    Combat(Equipe* equipeHaute, Equipe* equipeBasse);
    Combat(Equipe *equipeHaute);
    Equipe * obtenirEquipeHaute() const;
    Equipe * obtenirEquipeBasse() const;
    Personnage * prochainPersonnage();
    void tourSuivant();
    void ajouterAction(Personnage* cible, Personnage* source, TypeActionCombat action);
};

#endif
