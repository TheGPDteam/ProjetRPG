# Le Grand Projet de Développement (ou GPD)

Statut de la compilation : [![Build Status](https://travis-ci.org/TheGPDteam/ProjetRPG.svg?branch=dev)](https://travis-ci.org/TheGPDteam/ProjetRPG)

Ce dépôt git traite du **Grand Projet de Développement** initié par des anciens membres de l'Association Bordelaise des étudiants en IUT Informatique (ABEII).
Il va servir à ordonner les étapes d'avancement du projet décrit ci-dessous.

## Un Survival-RPG

Ce projet sera donc un jeu, plus précisément un **Survival-RPG** codé en C++ et transpillé en JavaScript.
Il va permettre aux étudiants de travailler sur un plus gros projet et de pouvoir accéder à des fonctions et des fonctionnalités plus étoffées dans un programme plus important. Il leur permettra également de développer des compétences techniques ainsi que l'esprit d'équipe.

Ce projet est également l'occasion pour certains de produire de la musique, des effets sonores et des sprites (ou images). Ce projet
offre également la possibilité de créer un site web pour intégrer le jeu.

## Scénario

Nous sommes en Septembre 1944, après le débarquement de Normandie.
Adolf Hitler a conscience que la guerre est sur le point d'être perdue et qu'il ne peut pas continuer à se battre sur deux fronts. Il décide donc de se servir d'une arme secrète : un virus qui nécrose le claustrum, région du cerveau en charge de la conscience. Une personne sur 10 est naturellement résistante à ce virus, et par chance vous en faites partie. Vous êtes le commandant d'une division de la gendarmerie allemande (la Feldgendarmerie) basée sur l'île d'Oléron. Vous sortez des jeunesses hitleriennes comme bon nombre de vos compagnons et par chance, 7 des 9 soldats sont également résistants. Les deux autres devenant des zombies, vous vous devez de les exécuter.
Vous organisez donc un petit groupe de survivants,bien décidés à rester en vie et à retourner en Allemagne révéler aux habitants les agissements du dictateur afin de le renverser.

## Architecture du Programme

Le programme sera codé avec une architecture MCV :

- Un modèle : Cette partie est le coeur du programme, elle va traiter et gérer les données du jeu.
- Un controleur : Cette partie va gérer les échanges entre le modèle (voir ci-dessus) et la vue (voir ci-dessous).
- Une vue : Cette partie est responsable de l'affichage du jeu et du traitement des évènements produits par le joueur (un clic par exemple).

## Convention de Notation

Cette partie n'est pas à négliger, elle va décrire comment vous devez coder pour pouvoir vous repérer dans le code et faire en sorte que les autres puissent également le faire. Vous comprendrez lorsque vous lirez le code de quelqu'un d'autre qu'il est très important de bien commenter et de suivre les conventions données ici afin de régler les soucis de relecture.

- Les commentaires : Il y a deux types de commentaires :
- Les commentaires généraux d'une fonction qui seront effectués dans la syntaxe Doxygen.
- Les commentaires détaillés qui serviront dans une fonction à comprendre le code et qui utiliseront "//" pour les commentaires courts (sur une ligne) et "/* */" sur les commentaires plus longs.

- Les classes : Un nom de classe doit commencer impérativement par une majuscule (PascalCase).
- Les attributs : Le nom d'un attribut doit impérativement commencer par m_, être écrit en camelCase et son nom doit être descriptif. Ainsi, pour la vitesse d'un personnage, on aura : m_vitesse.
- L'utilisation de git : Les modifications doivent être ajoutées à la branche dev. Dans le titre d'un commit, il faudra que l'on puisse savoir de quoi il s'agit précisemment.

## Environnement de développement

La liste de choses à faire est disponible à l'adresse : https://trello.com/b/CGDtE35u/gpd

## Liste des participants :

### Première génération :

#### Le Concepteur/Scénariste : 

- Mathieu Leothaud

#### Le chef de projet / Tuteur :

- Jeremy Garcia

#### Les développeurs : 

- Florent Vain (intégrateur / controlleur)
- Mathieu Leothaud (modèle)
- Pablo Gutierrez (vue)
- Julien Sorin (modèle)
- Anthony Nguyen (vue)
- Anthony Martin (modèle)
- Aymeric Devriesere (modèle)
- Nathan Lesne (modèle)

### Deuxième génération : 

#### To be continued...

## Remerciements

- A Monsieur Olivier Gauwin, pour son implication, son soutien et son engouement pour ce projet.

- A Monsieur Romain Bourqui, professeur de l'IUT en charge du bon déroulement de ce projet.

- A Monsieur Jeremy Garcia, ancien élève de l'IUT, en sa qualité de tuteur, ayant rendu possible que ce projet file droit.
