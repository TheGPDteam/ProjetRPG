#ifndef sauvegarde_h
#define sauvegarde_h

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "modele/modele.h"
#include <sys/stat.h>
#include <sys/types.h>

const std::string EN_TETE_XML = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";

class Sauvegarde
{
public:
    static void sauvegarderModele(Modele *modele);
    static void chargerModele(Modele* modele);
};

#endif
