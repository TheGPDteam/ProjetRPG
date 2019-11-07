#ifndef UTILITAIRES_H
#define UTILITAIRES_H

#include <string>
#include <vector>

std::string obtenirSousChaineEntre2Predicats(const std::string &chaine,const std::string &predicatDebut,const std::string &predicatFin);
void supprimmerSousChaineEntre2Predicats(std::__cxx11::string &chaine, const std::string &predicatDebut, const std::string &predicatFin);
void decouper(const std::string& str, std::vector<std::string>& jetons, const std::string& delimiteurs = " ") ;

#endif // UTILITAIRES_H
