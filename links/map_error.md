# Parsing & Map error

## Liste *non exhaustive* de cas d'erreur de map.cub

### Le ou les arguments

- [ ] Il n'y a pas d'arguments
- [ ] Le deuxieme argument n'est pas le fichier.cub
- [ ] Le troisieme argument n'estpas le --save
- [ ] Le fichier n'a pas la bonne extention .cub (pas valide) ```map00```
- [ ] Le fichier .cub est vide ou contient juste un /n ```map01```
- [ ] Le fichier.cub n'existe pas

### La map elle-meme

- [ ] La map n'est pas entourée par des 1 ```map01e1*```
- [ ] La map contient un ou plusieurs espaces à l'interieur ```map01e8*```
- [ ] La map est avant les éléments dans le fichier ```map02e*```
- [ ] Un ou plusieurs élément(s) est après la map dans le fichier ```map03e*```
- [ ] La map est séparee par une ligne vide ```map04e*```
- [ ] Il y a plusieurs maps ```map05e*```
- [ ] Il n'y a pas de N,S,E ou W  dans la map (pas de joueur) ```map07e*```
- [ ] Il y a plus d'un joueur dans la map, ou pas de joueur ```map08e*```
- [ ] Il y a d'autres caracteres que 0, 1, 2, N,S, E, W ```map09e*```
- [ ] Il n'y a pas de map apres la description ```map13e1```

### Les éléments

- [ ] L'identifiant d'un élément est manquant, n'existe pas ou est incorrect```map10e*```
- [ ] Apres R on a plus de deux nb, un seul nb, une resolution égale a 0 ou négative, supérieure a INT_MAX ```map12e*```
- [ ] Apres F ou C on a plus de deux nb, un seul nb, un nb négatif, supérieur a INT_MAX, supérieur que 255, pas de virgule entre les nb ```map14e*```
- [ ] Le path d'une texture est mauvais ```map15e*```
- [ ] Il n'y a aucun caractere (couleur, resolution ou path) apres un identifiant ```map16e*```
- [ ] Il y a deux fois le même identifiant
