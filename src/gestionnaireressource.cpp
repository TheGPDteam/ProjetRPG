#include "gestionnaireressource.h"

	GestionnaireRessource::GestionnaireRessource()
	{
		m_tabSurface = new std::map<std::string, SDL_Surface*>();
	}
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
	//! \author anguilbaud
	//! \date 20/10/2019
	void GestionnaireRessource::~GestionnaireRessource()
	{
		for (std::map<std::string, SDL_Surface*>::iterator it = m_tabSurface->begin(); it != m_tabSurface->end(); it++)
		{
			SDL_FreeSurface(it->second);
		}
		delete(m_tabSurface);
	}
	//! \author anguilbaud
//! \date 20/10/2019
	void GestionnaireRessource::chargementSurface(std::string nom, std::string extension)
	{
		SDL_Surface* surface = IMG_Load((nom + extension).c_str());

		if (surface == NULL)
		{
			std::cerr << "Impossible de charger la surface." << std::endl;
			exit(2);
		}
		m_tabSurface->insert(std::pair<std::string, SDL_Surface*>(nom.c_str(), surface));
	}
	//! \author anguilbaud
	//! \date 20/10/2019
	SDL_Surface* GestionnaireRessource::obtenirSurface(const char* nom)
	{
		std::map<std::string, SDL_Surface*>::iterator it = m_tabSurface->find(nom);
		SDL_Surface* surface = nullptr;

		if (it != m_tabSurface->end())
		{
			surface = it->second;
		}
		else
		{
			std::cerr << "Impossible la surface n'a pas etait chargee." << std::endl;
			exit(2);
		}
		return surface;
	}
};
