#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include <map>

class GestionnaireRessource
{
private:
    const std::string REPERTOIRE = "../rsc/sprites/";
    const std::string EXTENSION = ".bmp";
	std::map<std::string, SDL_Surface*>* m_tabSurface;
public:
	GestionnaireRessource();
  	~GestionnaireRessource();
	
	void dechargerSurface(char* nom);
    void chargementSurface(std::string nom);
	SDL_Surface* obtenirSurface(const char* nom);
};
