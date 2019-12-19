#ifndef combat_h
#define combat_h

#include <array>
#include <vector>
#include <map>
#include <utility>
#include <random>
#include "partiebus.h"
#include "../equipe.h"
#include "../../personnages/personnage.h"
#include "actioncombat.h"

class Combat
{
private:
    Equipe* m_equipeBasse;
    Equipe* m_equipeHaute;
    std::vector<Personnage*> m_ordrePassage;
    unsigned short m_numeroDePassage;
    ActionCombat* m_actionDuTour;
    static const float PROBABILITE_OBTENIR_OBJET;
    static const float PROBABILITE_OBTENIR_ARME;
    void suprimmerPersonnageOrdrePassage(Personnage *p);
public:
    Combat() = default;
    Combat(Equipe* equipeHaute, Equipe* equipeBasse);
    Combat(Equipe *equipeHaute);
    Equipe * obtenirEquipeHaute() const;
    Equipe * obtenirEquipeBasse() const;
    Equipe * obtenirEquipe(Personnage* personnage) const;
    Personnage * prochainPersonnage();
    void tourSuivant();
    void ajouterAction(Personnage* cible, Personnage* source, TypeActionCombat action);
    void simulerCombat();
    Objet* obtenirRecompense() const;

};

#endif
