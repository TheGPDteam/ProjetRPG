#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <map>

class GestionnaireRessource
{
private:
	std::map<std::string, SDL_Surface*>* m_tabSurface;
public:
	GestionnaireRessource();
  	~GestionnaireRessource();
	
	void dechargerSurface(char* nom);
	void chargementSurface(std::string nom, std::string extension);
	SDL_Surface* obtenirSurface(const char* nom);
};
