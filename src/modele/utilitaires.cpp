#include "utilitaires.h"

std::string obtenirSousChaineEntre2Predicats(const std::string &chaine,const std::string &predicatDebut,const std::string &predicatFin)
{
    if (chaine.empty())
        return "";

    std::string chaineRetournee = "";

    std::size_t positionFinPredicatDebut = chaine.find(predicatDebut) + predicatDebut.length();
    std::size_t positionPredicatFin = chaine.find(predicatFin);
    std::size_t longueurChaineRetournee = positionPredicatFin - positionFinPredicatDebut;

    if (positionFinPredicatDebut != std::string::npos
            && positionPredicatFin != std::string::npos
            && longueurChaineRetournee > 0)
        chaineRetournee = chaine.substr(positionFinPredicatDebut, longueurChaineRetournee);

    return chaineRetournee;
}

void supprimmerSousChaineEntre2Predicats(std::string &chaine, const std::string &predicatDebut, const std::string &predicatFin)
{
    std::size_t positionPredicatDebut = chaine.find(predicatDebut);
    std::size_t positionFinPredicatFin = chaine.find(predicatFin) + predicatFin.length();
    std::size_t longueurASuprimmer = positionFinPredicatFin - positionPredicatDebut;

    chaine.erase(positionPredicatDebut,longueurASuprimmer);
}
