#ifndef tuile_h
#define tuile_h

enum TypeTuile {
    Eau,
    Sable,
    Herbe,
    Beton,
    Terre,
    Arbre,
    AucunType
};

enum TypeJonction{
    AucuneJonction,
    HautGaucheEntrant,
    HautDroiteSortant,
    HautDroiteEntrant,
    BasDroiteSortant,
    BasDroiteEntrant,
    BasGaucheSortant,
    BasGaucheEntrant,
    Haut,
    Gauche,
    Droite,
    Bas,
    HautGaucheSortant
};

class Tuile
{
protected:
    TypeTuile m_type;
    int m_jonction;
private:
    bool m_extremiteCarte;

public:
    void definirExtremiteCarte(bool extremite);
    bool obtenirExtremiteCarte() const;
    Tuile(int val);
    TypeTuile obtenirType() const;
    bool obtenirEstMarchable() const;
    bool obtenirPeutApparaitre() const;

    void definirHachageJonction(TypeTuile typeVoisin, TypeJonction positionVoisin);
    int obtenirHachageJonction() const;

    static int hacher(TypeTuile typeVoisin, TypeJonction positionVoisin);
};

#endif
