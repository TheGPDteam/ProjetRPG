#include "sauvegarde.h"

void Sauvegarde::sauvegarderModele(Modele *modele)
{
    #ifdef __MINGW32__
    if (!mkdir("save"))
    #elif __linux__
    if (mkdir("save", 0777) == 0)
    #endif
    {
        std::cerr << "Dossier créé !" << std::endl;
    }

    std::string cheminFichier = "save/";
    if (!modele->obtenirNomPartie().empty())
        cheminFichier += modele->obtenirNomPartie()+".xml";
    else
        cheminFichier += "Defaut.xml";
    std::ofstream fichierSauvegarde(cheminFichier,std::ios::out | std::ios::trunc);

    if (fichierSauvegarde.is_open())
    {
        fichierSauvegarde << EN_TETE_XML+"";
        fichierSauvegarde << modele->serialiser();
        fichierSauvegarde.close();
    }
    else
        std::cout << "Erreur lors de l'ouverture du fichier" << std::endl;
}

void Sauvegarde::chargerModele(Modele* modele)
{
    std::string chemin = "save/Defaut.xml";
    std::ifstream fichierSauvegarde(chemin,std::ifstream::in);
    std::string ligneCourante = "";

    if (fichierSauvegarde.is_open())
    {
        std::getline(fichierSauvegarde,ligneCourante);
        if (ligneCourante == EN_TETE_XML) // Teste si le fichier est un fichier contenant une sauvegarde
        {
            std::string donnees_fichier { std::istreambuf_iterator<char>(fichierSauvegarde), std::istreambuf_iterator<char>() };
            modele->charger(donnees_fichier);
        }

        fichierSauvegarde.close();
    }

}
