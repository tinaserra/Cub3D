# Cub3D

A 3D game using raycasting.

Start
```
make && ./Cub3D description.cub
```

Supprimer tout
```
make fclean
```

## INTRODUCTION 🤓

Sujet -> [EN](https://github.com/tinaserra/Cub3D/blob/master/links/cub3d_en.pdf) | [FR](https://github.com/tinaserra/Cub3D/blob/master/links/cube3d_fr.pdf)

## PARSING 😳

Votre programme doit prendre en premier argument un fichier de description de scène avec pour extension **.cub**

La carte doit être parsée en accord avec ce qui est présenté dans le fichier.</br>
Vous devez pouvoir parser n’importe quelle sorte de carte, tant qu’elle respecte les règles de carte.

[règles de la map](https://github.com/tinaserra/Cub3D/blob/master/links/cube3d_fr.pdf) Page 7

### Les cas d'erreur

=> [Ma liste de cas d'erreur](https://github.com/tinaserra/Cub3D/blob/master/links/map_error.md)

### Retourner un message d'erreur

Si un problème de configuration de n’importe quel type est rencontré dans le fichier, le programme doit **quitter et renvoyer "Error\n"** suivi d’un **message d’erreur explicite de votre choix.**

### Fonctions autorisées

On dispose de deux fonctions por nous aider dans la gestion d'erreur :</br>
```perror``` et ```strerror```

En gros, ```strerror``` prend en parametre un int correspondant a un numero d'erreur et retourne une string contenant le message correspondent au numero.</br>
On peut ensuite imprimer la string sur la sortie standard avec ```perror```.


[man strerror](http://manpagesfr.free.fr/man/man3/strerror.3.html)
[man perror](http://manpagesfr.free.fr/man/man3/perror.3.html)

## RAYCASTING 😎

**Raycasting** est une technique de rendu permettant de créer une perspective 3D dans une carte 2D. Le jeu le plus connu qui utilise cette technique est bien sûr **Wolfenstein 3D**.

### Raycasting & Raytracing

***Raycasting n'est pas la même chose que raytracing!***</br></br>
Le raycasting est **une technique semi-3D rapide** qui fonctionne en temps réel même sur des calculatrices graphiques à 4 MHz.</br>
Le raytracing est **une technique de rendu réaliste** qui prend en charge les reflets et les ombres dans de vraies scènes 3D, et ce n'est que récemment que les ordinateurs sont devenus assez rapides pour le faire en temps réel pour un niveau raisonnablement élevé. résolutions et scènes complexes.

### Le principe du raycasting

Tuto :</br>
[How to become a Raycasting Master <3](https://lodev.org/cgtutor/raycasting.html)

Envoyer des rayons de gauche à droite depuis la position du joueur.
Plus le rayon met du temps à atteindre le mur, plus il est loin.
Plus il est loin plus la colonne de pixels est petite.
La couleur dépend aussi de la distance : plus c’est loin plus c’est foncé plus c’est près plus c’est clair.

### Les Sprites

Tuto :</br>
[Fraire des sprites de bg soyeux](https://lodev.org/cgtutor/raycasting3.html)


## USEFUL LINKS 🤙🏼
* [Raycasting tutorial video](https://courses.pikuma.com/courses/take/raycasting/lessons/7485598-introduction-and-learning-outcomes)
* [Lodev raycasting tutorial in english](https://lodev.org/cgtutor/raycasting.html)
* [Le raycasting en francais](http://projet-moteur-3d.e-monsite.com/pages/raycasting/raycasting.html)
* [Images in MLX](https://github.com/keuhdall/images_example)
