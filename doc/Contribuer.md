# Comment contribuer au développement ?

Après avoir installer le nécessaire pour développé sur le projet vous avez fait des modifications au code et souhaiter les faire parvenir sur la branche de développement du dépôt.

## Récupérer le nouveau code qui a été poussé sur le dépôt

Comme vous n'êtes pas le seul à participer au projet, il arrive souvent que d'autres membres pousse du code pendant que vous codiez votre fonctionnalité/correctif. Pas de panique, avant de pousser du code vous aller systématiquement devoir tirer les différence entre le dépôt et votre version locale. Pour cela une commande à retenir :

    git pull

Cette opération est à réaliser obligatoirement avant de commencer à coder et avant de pousser une modification. Cela vous permet d'avoir le code le plus à jour possible avec le dépôt distant. Il peut arriver que cette partie génère des complications, voir *Fusion de code* plus bas.

Pour cela il faut que votre code respecte quelques conditions importantes pour la cohésion du projet.

## Les conditions à respecter avant de pousser du code

 1. Votre version du code **DOIT IMPÉRATIVEMENT** pouvoir compiler sans erreurs. *Personne* ne veut passer son temps à essayer de faire compiler le code d'un autre avant de commencer à programmer.
 2. L’exécutable obtenu à la compilation doit être un minimum fonctionnel. Évitez de pousser du code qui casse la moitié du jeu.
 3. Commentez un maximum le code que vous venez d'ajouter. Cela fera gagner du temps à tout le monde, y compris vous.

Si ces conditions sont respectées vous pouvez passer à la suite.

## Ajouter les fichiers modifiés à envoyer sur le dépôt distant

Votre version du code locale est à présent différente de la version disponible sur le dépôt distant. Cependant vous n'avez pas modifier tout les fichiers donc il n'est pas nécessaire de renvoyer la totalité de votre version locale vers le dépôt distant. Il existe une commande pour ajouter seulement les fichiers modifiés à la prochaine poussé de code que vous allez faire :
    
     git add [fichier1.ext] [fichier2.ext] [...]
Entre crochet vous devez bien entendu renseigner les fichiers que vous voulez ajouter à la poussée, l’auto-complétion est souvent disponible avec tabulation dans le terminal.
Vous avez oublié les fichiers que vous avez modifié ? Pas de soucis, il existe également une commande qui vous indique quels fichiers ont été modifiés, créés ou supprimés par rapport au dépôt distant.

    git status 
Une liste des différences est alors affichée : en vert on trouve les fichiers ajoutés à la prochaine poussée du code et en rouge ceux qui n'y seront pas. On trouve également le type de modification (modifié ou supprimé et les non-suivis/nouveaux/ajouts) du fichier à gauche de celui-ci. À vous d'utiliser `git add`pour faire passer en vert les fichiers désirés.

Si vous savez ce que vous faites, il est possible d'utiliser `git add *`pour ajouter toutes les modifications d'un seul coup, cependant il faut faire attention aux fichiers de compilations qui viennent polluer le dépôt. Personnellement j'utilise uniquement la version avec l’énumération de fichiers, cela me permet de bien me remémorer les différentes modifications effectuées. 

## Soumettre ses modifications au dépôt distant

Maintenant que vous avez renseigné tout les fichiers que vous voulez envoyer vers le dépôt distant, il va falloir expliquer ce que font vos modifications ! En effet, à chaque soumission il est d'usage de fournir une liste des des fonctionnalités ajoutées/supprimées/corrigées.  En effet avec la commande `git log` vous pouvez afficher la liste des soumissions effectuées précédemment ! C'est plus pratique de savoir ce que fait exactement chacune des soumissions pour pouvoir, par exemple, revenir en arrière si jamais le besoin ce fait. 

Voici une nouvelle commande pour faire exactement cela :

    git commit -m "Votre message explicatif ici d'une longueur indéterminée"

Vous pouvez aussi écrire un fichier au préalable et ajouter son contenu avec l'option -F, ce qui nous donne :

    git commit -F MesModifications.txt

## Pousser les modifications vers le dépôt distant

Étape finale pour envoyer son code vers le dépôt distant : la poussée ! Pour ça une seule et unique commande :

    git push

En fonction du type de votre dépôt (http ou ssh), il est possible que le terminal vous demande votre identifiant GitHub et votre mot de passe.

## Que faire en cas de conflits / fusions avec le dépôt distant ?

En cours de rédaction
