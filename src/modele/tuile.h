#ifndef tuile_h
#define tuile_h

enum TypeTuile {
    Eau,
    Sable,
    Herbe,
    Beton,
    Terre,
    Arbre
};


class Tuile
{
protected:
    TypeTuile m_type;
private:
    bool m_extremiteCarte;
public:
    void definirExtremiteCarte(bool extremite);
    bool obtenirExtremiteCarte() const;
    Tuile(int val);
    TypeTuile obtenirType() const;
    bool obtenirEstMarchable() const;
    bool obtenirPeutApparaitre() const;
};

#endif
