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

    stats->SetAttribute("Niveau", std::to_string(modele->obtenirJoueur()->obtenirPersonnageJoueur()->obtenirNiveau().obtenirNiveauActuel()).c_str());
    stats->SetAttribute("Vie", std::to_string(modele->obtenirJoueur()->obtenirPersonnageJoueur()->obtenirVie()->obtenirValeur()).c_str());
    stats->SetAttribute("Force", std::to_string(modele->obtenirJoueur()->obtenirPersonnageJoueur()->obtenirForce()->obtenirValeur()).c_str());
    stats->SetAttribute("Intelligence", std::to_string(modele->obtenirJoueur()->obtenirPersonnageJoueur()->obtenirIntelligence()->obtenirValeur()).c_str());
    stats->SetAttribute("Vitesse", std::to_string(modele->obtenirJoueur()->obtenirPersonnageJoueur()->obtenirVitesse()).c_str());

    doc.SaveFile("save/save.xml");

    return 0;
}
