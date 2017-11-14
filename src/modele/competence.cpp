#include "competence.h"

//! \file fichier Competence
//! \date 17/11/16
//! \version 1.0

//!
//! \brief Constructeur par defaut d'une competence
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//!
//! Affecte la valeur 1 a la competence
//!

Competence::Competence()
    :m_valeur{1}
{}

//!
//! \brief Constructeur parametre d'une competence
//! \author mleothaud
//! \date 17/11/16
//! @param valeur : valeur a donner a la competence
//! \version 1.0
//!
//! Affecte la valeur du parametre a la competence
//!

Competence::Competence(unsigned short valeur)
    :m_valeur{valeur}
{
}

//!
//! \brief Permet d'augmenter la valeur de la competence
//! \author mleothaud
//! \date 17/11/16
//! @param valeur : valeur à incrementer pour la competence
//! \version 1.0
//!
//! Verifie si la valeur courante plus la valeur ajoutee est inferieur a la valeur max
//! si c'est le cas, on ajoute normalement
//! sinon la valeur courante devient la valeur max
//!

void Competence::augmenter(unsigned short valeur)
{
    if (valeur + m_valeur < M_VALEUR_MAX)
        m_valeur+=valeur;
    else
        m_valeur=M_VALEUR_MAX;
}

//!
//! \brief Accesseur en ecriture de l'attribut valeur
//! \author mleothaud
//! \date 17/11/16
//! @param valeur : Nouvelle valeur de la competence
//! \version 1.0
//!
//! Verifie si la valeur a affecter est inferieure ou egale a la valeur max
//! sinon la valeur courante devient la valeur max
//!

void Competence::definirValeur(const unsigned short &valeur)
{
    if (valeur <= M_VALEUR_MAX)
        m_valeur=valeur;
    else
        m_valeur=M_VALEUR_MAX;
}

//!
//! \brief Accesseur en lecture de l'attribut valeur
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return la valeur de la competence
//!

unsigned short Competence::obtenirValeur() const
{
    return m_valeur;
}

//!
//! \brief Accesseur en lecture de l'attribut valeur max
//! \author mleothaud
//! \date 17/11/16
//! \version 1.0
//! \return la valeur maximum que peut avoir une competence
//!

unsigned short Competence::obtenirValeurMax() const
{
    return M_VALEUR_MAX;
}

std::string Competence::serialiser() const
{
    return "<Competence>\n"
            "   <Valeur>\n" + std::to_string(m_valeur) + "\n</Valeur>\n"
            "   <ValeurMaximum>\n" + std::to_string(M_VALEUR_MAX) + "\n</ValeurMaximum>\n"
            "\n</Competence>\n";
}
