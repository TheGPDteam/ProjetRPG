TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += address_sanitizer

LIBS+=`sdl-config --libs` -lSDL_image -lSDL_ttf

INCLUDEPATH+=/usr/include/SDL/ ./controleur ./modele ./modele/environnement ./modele/environnement/carte ./modele/objets/ ./modele/objets/armes ./modele/personnages \
        ./modele/personnages/ennemis ./modele/survie ./modele/survie/combat ./modele/survie/experience ./modele/survie/quetes ./save ./vue ./vue/ecran ./vue/ecran/jeu \
        ./vue/ecran/menu ./vue/interfaceutilisateur ./vue/interfaceutilisateur/conteneur ./vue/interfaceutilisateur/conteneur/bouton ./vue/interfaceutilisateur/conteneur/tableau ./vue/interfaceutilisateur/ressources
QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra -Wno-narrowing

SOURCES += \
    controleur/controleur.cpp \
    modele/environnement/carte/carte.cpp \
    modele/environnement/carte/tuile.cpp \
    modele/environnement/carte/zone.cpp \
    modele/environnement/campement.cpp \
    modele/objets/armes/arme.cpp \
    modele/objets/objet.cpp \
    modele/personnages/ennemis/zombie.cpp \
    modele/personnages/humain.cpp \
    modele/personnages/personnage.cpp \
    modele/survie/combat/actioncombat.cpp \
    modele/survie/combat/combat.cpp \
    modele/survie/experience/competence.cpp \
    modele/survie/experience/niveau.cpp \
    modele/survie/quetes/quete.cpp \
    modele/survie/equipe.cpp \
    modele/survie/inventaire.cpp \
    modele/survie/vie.cpp \
    modele/survie/vivre.cpp \
    modele/joueur.cpp \
    modele/modele.cpp \
    modele/statistique.cpp \
    modele/temps.cpp \
    modele/utilitaires.cpp \
    save/sauvegarde.cpp \
    vue/ecran/jeu/ecranchoixpersonnage.cpp \
    vue/ecran/jeu/ecrancombat.cpp \
    vue/ecran/jeu/ecranequipe.cpp \
    vue/ecran/jeu/ecraninventaire.cpp \
    vue/ecran/jeu/ecranjeuprincipal.cpp \
    vue/ecran/jeu/ecranlisteobjets.cpp \
    vue/ecran/menu/ecranaccueilcampement.cpp \
    vue/ecran/menu/ecranmenuprincipal.cpp \
    vue/ecran/menu/ecrannom.cpp \
    vue/ecran/menu/ecranpremierejournee.cpp \
    vue/ecran/menu/ecranquete.cpp \
    vue/ecran/menu/ecranquetejoueur.cpp \
    vue/ecran/menu/ecranrecapitulatifnuit.cpp \
    vue/ecran/menu/ecranrepartitionjoueur.cpp \
    vue/ecran/ecrangeneral.cpp \
    vue/interfaceutilisateur/conteneur/bouton/actionsboutons.cpp \
    vue/interfaceutilisateur/conteneur/bouton/bouton.cpp \
    vue/interfaceutilisateur/conteneur/bouton/dictionnairedeboutons.cpp \
    vue/interfaceutilisateur/ressources/chargementfeuilledesprite.cpp \
    vue/interfaceutilisateur/saisir.cpp \
    vue/interfaceutilisateur/sprite.cpp \
    vue/interfaceutilisateur/textesdl.cpp \
    vue/vue.cpp \
    main.cpp \
    observable.cpp \
    observateur.cpp \
    vue/interfaceutilisateur/cliquable.cpp \
    vue/interfaceutilisateur/zonetexte.cpp \
    vue/affichable.cpp \
    vue/outilsvue.cpp \
    vue/interfaceutilisateur/conteneur/tableau/case.cpp \
    vue/interfaceutilisateur/conteneur/tableau/ligne.cpp \
    vue/interfaceutilisateur/conteneur/tableau/tableau.cpp \
    modele/queteprincipale.cpp \
    modele/objets/partiebus.cpp \
    vue/ecran/menu/ecranquetecampement.cpp \
    vue/interfaceutilisateur/zonedefilable.cpp \
    vue/interfaceutilisateur/conteneur/tableau/tableaudefilable.cpp \
    vue/spriteanime.cpp \
    vue/spritepersonnage.cpp \
    gestionnaireressource.cpp \
    vue/interfaceutilisateur/conteneur/afficheurzone.cpp \
    modele/chrono.cpp \
    modele/environnement/carte/zonechangementzone.cpp \
    timer.cpp



include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    controleur/controleur.h \
    modele/environnement/carte/carte.h \
    modele/environnement/carte/tuile.h \
    modele/environnement/carte/zone.h \
    modele/environnement/campement.h \
    modele/objets/armes/arme.h \
    modele/objets/objet.h \
    modele/objets/typeobjet.h \
    modele/personnages/ennemis/zombie.h \
    modele/personnages/humain.h \
    modele/personnages/personnage.h \
    modele/survie/combat/actioncombat.h \
    modele/survie/combat/combat.h \
    modele/survie/combat/typeactioncombat.h \
    modele/survie/experience/competence.h \
    modele/survie/experience/niveau.h \
    modele/survie/quetes/quete.h \
    modele/survie/quetes/typequete.h \
    modele/survie/equipe.h \
    modele/survie/inventaire.h \
    modele/survie/typedefaite.h \
    modele/survie/vie.h \
    modele/survie/vivre.h \
    modele/joueur.h \
    modele/modele.h \
    modele/statistique.h \
    modele/temps.h \
    modele/utilitaires.h \
    save/sauvegarde.h \
    vue/ecran/jeu/ecranchoixpersonnage.h \
    vue/ecran/jeu/ecrancombat.h \
    vue/ecran/jeu/ecranequipe.h \
    vue/ecran/jeu/ecraninventaire.h \
    vue/ecran/jeu/ecranjeuprincipal.h \
    vue/ecran/jeu/ecranlisteobjets.h \
    vue/ecran/menu/ecranaccueilcampement.h \
    vue/ecran/menu/ecranmenuprincipal.h \
    vue/ecran/menu/ecrannom.h \
    vue/ecran/menu/ecranpremierejournee.h \
    vue/ecran/menu/ecranquete.h \
    vue/ecran/menu/ecranquetejoueur.h \
    vue/ecran/menu/ecranrecapitulatifnuit.h \
    vue/ecran/menu/ecranrepartitionjoueur.h \
    vue/ecran/ecrangeneral.h \
    vue/ecran/typeecran.h \
    vue/interfaceutilisateur/conteneur/bouton/actionsboutons.h \
    vue/interfaceutilisateur/conteneur/bouton/bouton.h \
    vue/interfaceutilisateur/conteneur/bouton/constantesbouton.h \
    vue/interfaceutilisateur/conteneur/bouton/dictionnairedeboutons.h \
    vue/interfaceutilisateur/ressources/chargementfeuilledesprite.h \
    vue/interfaceutilisateur/ressources/policetexte.h \
    vue/interfaceutilisateur/saisir.h \
    vue/interfaceutilisateur/sprite.h \
    vue/interfaceutilisateur/textesdl.h \
    vue/vue.h \
    direction.h \
    observable.h \
    observateur.h \
    vue/interfaceutilisateur/cliquable.h \
    vue/interfaceutilisateur/zonetexte.h \
    vue/affichable.h \
    vue/outilsvue.h \
    vue/interfaceutilisateur/conteneur/tableau/case.h \
    vue/interfaceutilisateur/conteneur/tableau/ligne.h \
    vue/interfaceutilisateur/conteneur/tableau/tableau.h \
    modele/queteprincipale.h \
    modele/objets/partiebus.h \
    vue/ecran/menu/ecranquetecampement.h \
    vue/interfaceutilisateur/zonedefilable.h \
    vue/interfaceutilisateur/conteneur/tableau/tableaudefilable.h \
    vue/spriteanime.h \
    vue/spritepersonnage.h \
    gestionnaireressource.h \
    vue/interfaceutilisateur/conteneur/afficheurzone.h \
    modele/chrono.h \
    modele/environnement/carte/zonechangementzone.h \
    timer.h

