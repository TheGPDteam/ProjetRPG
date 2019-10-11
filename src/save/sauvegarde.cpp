#include "sauvegarde.h"
#ifdef _WIN32
   #include <io.h>
   #define access    _access_s
#else
   #include <unistd.h>
#endif

void Sauvegarde::sauvegarderModele(Modele *modele)
{
    #ifdef __MINGW32__
    if (!mkdir("save"))
    #elif __linux__
    if (mkdir("save", 0777) == 0)
    #endif
    {
        std::cout << "Dossier créé !" << std::endl;
    }
    //if (!modele->obtenirNomPartie().empty())
        //cheminFichier += modele->obtenirNomPartie()+".xml";
    //else
    std::ofstream fichierSauvegarde(FICHIER_SAUVEGARDE,std::ios::out | std::ios::trunc);

    if (fichierSauvegarde.is_open())
    {
        fichierSauvegarde << EN_TETE_XML;
        fichierSauvegarde << modele->serialiser();
        fichierSauvegarde.close();
    }
    else
        std::cerr << "Erreur lors de l'ouverture du fichier" << std::endl;
}

void Sauvegarde::chargerModele(Modele* modele)
{
    std::ifstream fichierSauvegarde(FICHIER_SAUVEGARDE,std::ifstream::in);
    std::string emplacementXMLAttendu;

    if (fichierSauvegarde.is_open())
    {
        std::copy_n(std::istreambuf_iterator<char>(fichierSauvegarde.rdbuf()), EN_TETE_XML.length(), std::back_inserter(emplacementXMLAttendu));

        if (emplacementXMLAttendu == EN_TETE_XML) // Teste si le fichier est un fichier contenant une sauvegarde
        {
            std::string donnees_fichier { std::istreambuf_iterator<char>(fichierSauvegarde), std::istreambuf_iterator<char>() };
            modele->charger(donnees_fichier);
        }

        fichierSauvegarde.close();
    }

}

bool Sauvegarde::fichierSauvegardeExiste()
{
    return access(FICHIER_SAUVEGARDE.c_str(),R_OK) == 0;
}
