#ifndef quete_h
#define quete_h

#include <string>
#include "objet.h"
#include <ctime>
#include "typequete.h"

class Quete
{
private:
    bool m_fini;
    std::string m_nom;
    std::string m_description;
    int m_valeurObjectif;
    int m_valeurActuelle;
    int m_recompenseExperience;
    Objet* m_recompense;

    std::clock_t m_tempsDebutQuete;
    std::clock_t m_tempsDebutPause;
    int m_secondesJeuPause;
    TypeQuete m_type;

public:
    Quete() = default;
    Quete(TypeQuete tq, std::string nom, std::string description, int valeurObjectif, int recompenseExperience, Objet* recompense);
    Quete(const Quete& copie) = default;

    Objet* obtenirRecompense() const;
    int obtenirValeurAvancement() const;
    int obtenirValeurObjectif() const;
    int obtenirRecompenseExp() const;
    void definirValeurActuelle(int valeur);
    void definirValeurObjectif(int valeur);
    void definirRecompense(Objet obj);
    void definirRecompenseExp(int valeur);
    void demarrerTimer();
    std::string obtenirStringTemps();
    bool queteTerminee();
    void miseEnPause();
    void reprise();
    void augmenterValeur(int valeur);
    void finir();
    bool estfini();
    TypeQuete obtenirType() const;
};

#endif
