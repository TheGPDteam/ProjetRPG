#ifndef sauvegarde_h
#define sauvegarde_h

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "modele/modele.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <../ext/tinyxml/tinyxml.h>

class Sauvegarde
{
private:
    std::string m_donnees;
    static int creerFichier(std::string fichier);
public:
    static int sauvegarderModele(Modele *modele);
};

#endif
