#include "utilitaires.h"

std::string obtenirSousChaineEntre2Predicats(const std::string &chaine,const std::string &predicat_debut,const std::string &predicat_fin)
{
    if (chaine.empty())
        return "";

    std::string chaineRetournee = "";

    std::size_t positionFinPredicatDebut = chaine.find(predicat_debut) + predicat_debut.length();
    std::size_t positionPredicatFin = chaine.find(predicat_fin);
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

void decouper(const std::string& str, std::vector<std::string>& jetons, const std::string& delimiteurs) {
    jetons.resize(0);
    if (str.length() == 0) return;
    std::string::size_type prevPos = 0;//str.find_first_not_of(delimiteurs, 0);
    std::string::size_type pos     = str.find_first_of(delimiteurs, prevPos);
    while (std::string::npos != pos || std::string::npos != prevPos) {
        jetons.push_back(str.substr(prevPos, pos - prevPos));
        std::string::size_type pos_tmp = str.find_first_of(delimiteurs, pos+1);
        if (pos_tmp - pos == 1){
            prevPos = pos_tmp;
            pos = pos_tmp;
        } else {
            prevPos = str.find_first_not_of(delimiteurs, pos);
            pos = str.find_first_of(delimiteurs, prevPos);
        }
    }

    if (str[str.size()-1]=='\t')
        jetons.push_back("");
}
