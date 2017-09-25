#include "sauvegarde.h"

int Sauvegarde::sauvegarderModele(Modele *modele)
{
    if (!mkdir("save", 0777));
    {
        std::cout << "Dossier créé !" << std::endl;
    }

    TiXmlDocument doc("save/save.xml");
    TiXmlHandle manipulateur(&doc);

    TiXmlElement *elem = new TiXmlElement("Sauvegarde");
    doc.LinkEndChild(elem);

    elem->SetAttribute("personnage", "statistiques");

    TiXmlElement *stats = new TiXmlElement("statistiques");
    elem->LinkEndChild(stats);

    stats->SetAttribute("Vie", "10");
    stats->SetAttribute("Force", "10");
    stats->SetAttribute("Vitesse", "10");
    stats->SetAttribute("Intelligence", "10");

    doc.SaveFile("save/save.xml");

    return 0;
}
