#include "gestionnaireressource.h"

//! \brief constructeur
//! \author anguilbaud
//! \date 20/10/2019
GestionnaireRessource::GestionnaireRessource()
{
    m_tabSurface = new std::map<std::string, SDL_Surface*>();
}


//! \brief decharge une surface
//! \param nom de la surface a decharger
//! \author anguilbaud
//! \date 20/10/2019
void GestionnaireRessource::dechargerSurface(char* nom)
{
    std::map<std::string, SDL_Surface*>::iterator it = m_tabSurface->find(nom);

    if (it != m_tabSurface->end())
    {
        SDL_FreeSurface(it->second);
        m_tabSurface->erase(nom);
    }
}


//! \brief destructeur
//! \author anguilbaud
//! \date 20/10/2019
GestionnaireRessource::~GestionnaireRessource()
{
    for (std::map<std::string, SDL_Surface*>::iterator it = m_tabSurface->begin(); it != m_tabSurface->end(); it++)
    {
        SDL_FreeSurface(it->second);
    }

    delete(m_tabSurface);
}


//! \brief permet de charger une surface
//! \author anguilbaud
//! \date 20/10/2019
void GestionnaireRessource::chargementSurface(std::string nom)
{
    std::map<std::string, SDL_Surface*>::iterator it = m_tabSurface->find(REPERTOIRE + nom + EXTENSION);

    if(it == m_tabSurface->end())
    {

        SDL_Surface* surface = IMG_Load((REPERTOIRE + nom + EXTENSION).c_str());
        if (surface == NULL)
        {

            std::cerr << "Impossible de charger la surface." << std::endl;
            exit(2);
        }

        m_tabSurface->insert(std::pair<std::string, SDL_Surface*>(nom.c_str(), surface));
    }
}


//! \brief permet de recuperer une surface
//! \author anguilbaud
//! \date 20/10/2019
SDL_Surface* GestionnaireRessource::obtenirSurface(const char* nom)
{
    std::map<std::string, SDL_Surface*>::iterator it = m_tabSurface->find(nom);

    if (it == m_tabSurface->end()){
        chargementSurface(nom);
        it = m_tabSurface->find(nom);
    }

    return it->second;
}

