#ifndef objet_h
#define objet_h

#include <string>
//!
//! \brief Classe de gestion de l'Objet
//! \date 03/11/2016
//!

class Objet
{
protected:
    std::string m_nom; /// Nom de l'Objet
    std::string m_description; /// Description de l'Objet
public:
    Objet(std::string nom, std::string description);
    ~Objet();
    std::string obtenirNom() const;
    void definirNom(const std::string &nom);
    std::string obtenirDescription() const;
    void definirDescription(const std::string &description);
};

#endif
