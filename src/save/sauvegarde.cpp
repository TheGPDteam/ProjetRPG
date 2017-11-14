#include "sauvegarde.h"

void Sauvegarde::sauvegarderModele(Modele *modele)
{
    auto t_debut = std::chrono::system_clock::now();
    #ifdef __MINGW32__
    if (!mkdir("save"))
    #elif __linux__
    if (mkdir("save", 0777) == 0)
    #endif
    {
        std::cerr << "Dossier créé !" << std::endl;
    }

    std::ofstream fichierSauvegarde("save/Modele.xml",std::ios::out | std::ios::trunc);

    if (fichierSauvegarde.is_open())
    {
        fichierSauvegarde << EN_TETE_XML+"\n";
        fichierSauvegarde << modele->serialiser();
        fichierSauvegarde.close();
    }
    else
        std::cout << "Erreur lors de l'ouverture du fichier" << std::endl;
    auto t_fin = std::chrono::system_clock::now();
    std::chrono::duration<double> t = t_fin-t_debut;

    std::cout << "Durée exec: " << t.count() << std::endl;
}

void Sauvegarde::chargerModele(Modele* modele,std::string chemin)
{
    std::ifstream fichierSauvegarde(chemin,std::ifstream::in);

    if (fichierSauvegarde.is_open())
    {

    }

}
