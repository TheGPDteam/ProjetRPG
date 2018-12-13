#ifndef objet_h
#define objet_h

#include <string>
#include <vector>
#include "typeobjet.h"
#include "sprite.h"

//!
//! \brief Classe de gestion de l'Objet
//! \date 03/11/2016
//!

class Objet
{
protected:
    std::string m_nom; /// Nom de l'Objet
    std::string m_description; /// Description de l'Objet
    Sprite* m_sprite;

public:
    Objet();
    Objet(std::string nom, std::string description);
    virtual ~Objet();
    Sprite* obtenirSprite() const;
    void definirSprite(Sprite *sprite);
    std::string obtenirNom() const;
    void definirNom(const std::string &nom);
    std::string obtenirDescription() const;
    void definirDescription(const std::string &description);
    virtual std::string serialiser() const;
    virtual TypeObjet obtenirType() const;
    virtual void charger(const std::string &donnees);
    virtual bool operator==(const Objet* obj);
    virtual bool operator>(const Objet* obj);
};

#endif
