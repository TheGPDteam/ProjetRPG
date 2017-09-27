#include "sauvegarde.h"

int Sauvegarde::sauvegarderModele(Modele *modele)
{
    #ifdef __MINGW32__
    if (!mkdir("save"))
    #elif __linux__
    if (!mkdir("save", 0777))
    #endif
    {
        std::cerr << "Dossier créé !" << std::endl;
    }

    TiXmlDocument doc("save/save.xml");
    TiXmlHandle manipulateur(&doc);

    TiXmlElement *elem = new TiXmlElement("Sauvegarde");
    doc.LinkEndChild(elem);

    elem->SetAttribute("personnage", "statistiques");

    TiXmlElement *stats = new TiXmlElement("statistiques");
    elem->LinkEndChild(stats);

    stats->SetAttribute("Niveau", std::to_string(modele->obtenirJoueur()->obtenirPersonnageJoueur()->obtenirNiveau()));
    stats->SetAttribute("Vie", std::to_string(modele->obtenirJoueur()->obtenirPersonnageJoueur()->obtenirVie()));
    stats->SetAttribute("Force", std::to_string(modele->obtenirJoueur()->obtenirPersonnageJoueur()->obtenirForce()));
    stats->SetAttribute("Intelligence", std::to_string(modele->obtenirJoueur()->obtenirPersonnageJoueur()->obtenirIntelligence()));
    stats->SetAttribute("Vitesse", std::to_string(modele->obtenirJoueur()->obtenirPersonnageJoueur()->obtenirVitesse()));

    doc.SaveFile("save/save.xml");

    return 0;
}
