# Comment contribuer au projet ?

## Sommaire

 1. Prérequis
 2. Sous Linux
	2.1 Installation de qtCreator et qmake
	2.2 Installation de Git
	2.3 Installation de la SDL1.2 et de ses extensions
	2.4 Récupération du code depuis le dépôt GitHub
 3. Sous Windows
	 3.1 Installation de qtCreator et qmake
	 3.2 Installation de Git (Ligne de commande ou Interface Graphique)
	 3.3 Installation de la SDL1.2 et de ses extensions
	 3.4 Récupération du code depuis les dépôts

## Prérequis

Pour contribuer au projet vous aurez besoin de deux logiciels et d'une bibliothèque.

Il vous faut donc :

- qtCreator & qmake
- git

Ainsi que la blibliothèque SDL dans sa version 1.2 avec les extensions SDL\_images et SDL\_TTF.

----------

## Sous Linux

Si vous êtes sur des machines de l'IUT, passez les étapes d'installations car les logiciels sont déjà présents. 

### Installer qtCreator et qmake

Ouvrez un terminal.
Puis entrez et exécuter la ligne de commande suivante

    apt-get install qtcreator qt5-qmake

Après un certain temps, la main du terminal vous reviendra : vous avez installé qtCreator et qmake

### Installer git

Le logiciel git est nécessaire pour récupérer le code depuis le dépôt avec lequel on effectue le versionnage du Projet

Ouvrez donc un terminal et entrez la ligne suivante 

    apt-get install git

Voilà !

### Installer la SDL et les extensions

Ouvrez un terminal.
Puis entrez et exécutez la ligne de commande suivante

    apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-ttf2.0-dev

Bravo vous avez installez la SDL1.2 et ses extensions pour pourvoir compiler le jeu !

### Récupération du code depuis le dépot de dev

Pour récupérer le code après avoir installer le nécessaire de compilation il vous faudra exécuter les commandes suivantes sous Linux :

    git clone -b dev https://github.com/TheGPDteam/ProjetRPG.git 

Cela va vous créer un nouveau dossier ProjetRPG/ dans le dossier courant. Il suffit de lancer les deux commandes suivante pour ouvrir le projet dans l'environnement de développement intégré

    cd ProjetRPG/
    qtcreator src/src.pro

----------

## Sous Windows
