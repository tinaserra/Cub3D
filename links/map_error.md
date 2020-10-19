# Parsing & Map error

## Ce qui est demandé

Votre programme doit prendre en premier argument un fichier de description de scène avec pour extension **.cub**

La carte doit être parsée en accord avec ce qui est présenté dans le fichier.</br>
Vous devez pouvoir parser n’importe quelle sorte de carte, tant qu’elle respecte les règles de carte.

=> [règles de la map](https://github.com/tinaserra/Cub3D/blob/master/links/cube3d_fr.pdf) Page 7

## Liste *non exhaustive* de cas d'erreur de map.cub

### Le fichier

- [ ] Le fichier n'a pas la bonne extention .cub (pas valide) ```map00```
- [ ] Le fichier .cub est vide ou contient juste un /n ```map01```

### La map elle-meme

- [ ] La map n'est pas entourée par des 1 ```map01e*```
- [ ] La map est avant les éléments dans le fichier ```map02e*```
- [ ] Un ou plusieurs élément(s) est après la map dans le fichier ```map03e*```
- [ ] La map est séparee par une ligne vide ```map04e*```
- [ ] Il y a plusieurs maps ```map05e*```
- [ ] La map contient un ou plusieurs espaces à l'interieur ```map06e*```
- [ ] Il n'y a pas de N,S,E ou W  dans la map (pas de joueur) ```map07e*``` ```map01e4``` ```map01e6```
- [ ] Il y a plus d'un joueur dans la map ```map08e*```
- [ ] Il y a d'autres caracteres que 0, 1, 2, N,S, E, W ```map09e*```
- [ ] Il n'y a pas de map apres la description ```map01e6```

### Les éléments

- [ ] Le premier caractere d'un élément n'est pas un identifiant ```map10e*```
- [ ] L'identifint a plus de deux caracteres ```map11e*```
- [ ] Apres R on a plus de deux nombres ```map12e*```
- [ ] Apres R on a qu'un seul nombre ```map13e*```
- [ ] Apres F ou C on a qu'un seul nombre, que deux nombres, plus de trois nombres, un nb plus grand que 255 ```map14e*```
- [ ] Le path d'une texture est mauvais ```map15e*```
- [ ] Il n'y a aucun caractere (couleur, resolution ou path) apres un identifiant ```map16e*```
- [ ] Apres R on a 0 0 ```map17e01```
- [ ] Il y a deux fois le même identifiant

## Retourner un message d'erreur

Si un problème de configuration de n’importe quel type est rencontré dans le fichier, le programme doit **quitter et renvoyer "Error\n"** suivi d’un **message d’erreur explicite de votre choix.**

### Fonctions autorisées

On dispose de deux fonctions por nous aider dans la gestion d'erreur :</br>
```perror``` et ```strerror```

En gros, ```strerror``` prend en parametre un int correspondant a un numero d'erreur et retourne une string contenant le message correspondent au numero.</br>
On peut ensuite imprimer la string sur la sortie standard avec ```perror```.


[man strerror](http://manpagesfr.free.fr/man/man3/strerror.3.html)
[man perror](http://manpagesfr.free.fr/man/man3/perror.3.html)