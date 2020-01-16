#include <iostream>
#include <stdlib.h>

//! \file fichier main
//! \date 15/11/16
//! \version 0.1

#include "vue/vue.h"
#include "modele/modele.h"
#include "controleur/controleur.h"
#include "modele/survie/equipe.h"
#include "modele/survie/inventaire.h"

const int TEMPS_RAFRAICHISSEMENT = 1000/60;
void mainloop_func(void* c, void* ctrl){  
    Vue* vue= (Vue*) c;
    Controleur* controleur = (Controleur*) ctrl;

    Uint32 tempsActuel = SDL_GetTicks();
    Uint32 tempsAvant = 0;


    while (!vue->obtenirFermerJeu()) {
        
        tempsActuel = SDL_GetTicks();

        if(tempsActuel - tempsAvant > TEMPS_RAFRAICHISSEMENT){
            tempsAvant = tempsActuel;
            vue->affichageVue();
            controleur->deroulementJournee();
        }
        else{
            //SDL_Delay(TEMPS_RAFRAICHISSEMENT + tempsAvant - tempsActuel);
        }
    }
    ChargementFeuilleDeSprites::supprimerInstance();
}

//!
//! \brief Fonction principale du programme
//! \return etat de sortie du programme (0 si il n'y a pas eu de probleme)
//! \author mleothaud, fvain
//! \date 15/11/16
//! @param argc nombre d'arguments passés en paramètre
//! @param argv arguments passés en paramètre
//! \version 0.1
//!
//! Contient la boucle de jeu et l'initialisation des classes principales
//!
int main (){

    srand(time(NULL));
    std::cout << "Initialisation de la Vue" << std::endl;
    Vue* vue = new Vue(); //On instancie la vue
    std::cout << "Initialisation du Modele" << std::endl;
    Modele* modele= new Modele(); // On instancie le modele
    std::cout << "Initialisation du Controleur" << std::endl;
    Controleur controleur{vue,modele}; // On instancie le controleur
    std::cout << "Initialisation du MVC effectué" << std::endl;
    vue->definirControleur(&controleur);

#ifdef EMSCRIPTEN
    emscripten_set_main_loop_arg(mainloop_func,vue, 60, 0);
    emscripten_exit_with_live_runtime();
#else
    mainloop_func(vue, &controleur);
#endif

    delete vue;
    delete modele;

    return EXIT_SUCCESS;
}
