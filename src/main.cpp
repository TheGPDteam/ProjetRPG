#include <iostream>
#include <stdlib.h>

//! \file fichier main
//! \date 15/11/16
//! \version 0.1

#include "vue/vue.h"
#include "modele/modele.h"
#include "controleur/controleur.h"
#include "modele/equipe.h"
#include "modele/inventaire.h"

void mainloop_func(void* c){
    Vue* vue= (Vue*) c;
    while (!vue->getFermerJeu())
        vue->affichageVue();
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
    Vue* vue = new Vue(); //On instancie la vue
    Modele* modele= new Modele(); // On instancie le modele
    Controleur controleur{vue,modele}; // On instancie le controleur

    vue->definirControleur(&controleur);
//    controleur.definirVue(vue);
//    controleur.definirModele(modele);

#ifdef EMSCRIPTEN
    emscripten_set_main_loop_arg(mainloop_func,vue, 60, 0);
    emscripten_exit_with_live_runtime();
#else
    mainloop_func(vue);
#endif

    delete vue;
    delete modele;

    return EXIT_SUCCESS;
}
