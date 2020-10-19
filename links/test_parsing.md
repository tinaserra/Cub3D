# Test parsing

## Good maps

1. ***seg fautl*** avec une map correct ```description.cub``` en quittant le programme avec ```echap```
=> meme chose sur d'autres maps, en cliquant sur la croix la fenetre se ferme mais le programme ne s'arrete pas, il faut faire ```ctrl C```. Si on spam la touche, on a un segfault.
2. ***bus error*** avec ```maps/good_map00.cub``` en foncant dans un mur
3. tres lent avec une grande (1920x1080) resolution ```maps/good_map02.cub``` la fenetre ne prend pas toute la taille de l'ecran mais ok.
4. ***seg fault*** avec ```maps/good_map03.cub``` : il y a des espaces devant les identifiants des textures.
5. ***bus error*** avec ```maps/wrong_map01e1.cub``` en foncant dans un mur, idem que n.2

## Tableau de check

- [x] une case cochée : le programme reconnait une erreur (on n'a pas forcément le bon message d'ereur)
- [ ] une case non cochée : le programme ```segmentation fault``` ou ```bus error``` ou *ne reconnait pas d'erreur* ou *ne quitte pas*

### Good maps

- [ ] good_map00.cub
- [ ] good_map01.cub
- [ ] good_map02.cub
- [ ] good_map03.cub

### Error : Mauvaise extenion de fichier

- [x] wrong_map00           -> ```y a une erreur```
- [x] wrong_map00.c         -> ```y a une erreur```
- [x] wrong_map00.cu        -> ```y a une erreur```
- [x] wrong_map00.txt       -> ```y a une erreur```

### Error : fichier vide (ou ne contenant qu'un /n)

- [ ] wrong_map01.cub       -> ```segmentation fault```

### Error : la map n'est pas entouree de 1

- [ ] wrong_map01e1.cub     -> Pas d'erreur.
- [ ] wrong_map01e2.cub     -> ```bus error```
- [ ] wrong_map01e3.cub     -> ```bus error```
- [ ] wrong_map01e4.cub     -> ```segmentation fault```
- [ ] wrong_map01e5.cub     -> ```y a une erreur``` mais ne quitte pas
- [ ] wrong_map01e6.cub     -> ```segmentation fault```
*Ce dernier cas correspond a plusieurs erreurs, c'est une map vide*

### Error : Il y a des éléments après la map

- [ ] wrong_map02e1.cub     -> Pas d'erreur.
- [ ] wrong_map02e2.cub     -> Pas d'erreur.
- [ ] wrong_map02e3.cub     -> Pas d'erreur.

- [ ] wrong_map03e1.cub     -> Pas d'erreur.
- [ ] wrong_map03e2.cub     -> Pas d'erreur.
- [ ] wrong_map03e3.cub     -> Pas d'erreur. ou ```bus error``` quand Résolution trop grande
- [ ] wrong_map03e4.cub     -> Pas d'erreur.
- [ ] wrong_map03e5.cub     -> Pas d'erreur.

### Error : Il y a des lignes vides dans la map

- [ ] wrong_map04e1.cub     -> Pas d'erreur.
- [ ] wrong_map04e2.cub     -> Pas d'erreur.
- [ ] wrong_map04e3.cub     -> Pas d'erreur.
- [ ] wrong_map04e4.cub     -> Pas d'erreur.
- [ ] wrong_map04e5.cub     -> Pas d'erreur.

</br>*Dans ces prochains cas il y a deux maps*</br>
- [ ] wrong_map05e1.cub     -> Pas d'erreur.
- [ ] wrong_map05e2.cub     -> Pas d'erreur.

### Error : Il y a un ou plusieurs espaces dans la map

- [ ] wrong_map06e01.cub    -> Pas d'erreur.
- [ ] wrong_map06e02.cub    -> ```bus error```        
- [ ] wrong_map06e03.cub    -> Pas d'erreur.
- [ ] wrong_map06e04.cub    -> ```bus error```
- [ ] wrong_map06e05.cub    -> Pas d'erreur.
- [ ] wrong_map06e06.cub    -> Pas d'erreur.
- [ ] wrong_map06e07.cub    -> ```bus error```
- [ ] wrong_map06e08.cub    -> ```bus error```
- [ ] wrong_map06e09.cub    -> ```bus error```
- [ ] wrong_map06e10.cub    -> ```bus error```
- [ ] wrong_map06e11.cub    -> Pas d'erreur.
- [ ] wrong_map06e12.cub    -> Pas d'erreur.
- [ ] wrong_map06e13.cub    -> Pas d'erreur.

### Error : Il n'y a pas de personnage

- [ ] wrong_map07e01.cub    -> Pas d'erreur.
- [ ] wrong_map07e02.cub    -> Pas d'erreur.
- [ ] wrong_map07e03.cub    -> Pas d'erreur.
- [ ] wrong_map07e04.cub    -> Pas d'erreur.

### Error : Il y a plusieurs personnages

- [ ] wrong_map08e01.cub    -> ```bus error```
- [ ] wrong_map08e02.cub    -> Pas d'erreur.
- [ ] wrong_map08e03.cub    -> Pas d'erreur.

- [ ] wrong_map09e01.cub
- [ ] wrong_map09e02.cub
- [ ] wrong_map09e03.cub
- [ ] wrong_map09e04.cub
- [ ] wrong_map09e05.cub
- [ ] wrong_map09e06.cub
- [ ] wrong_map09e07.cub
- [ ] wrong_map09e08.cub
- [ ] wrong_map09e09.cub

- [ ] wrong_map10e01.cub
- [ ] wrong_map10e02.cub
- [ ] wrong_map10e03.cub
- [ ] wrong_map10e04.cub
- [ ] wrong_map10e05.cub
- [ ] wrong_map11e01.cub
- [ ] wrong_map11e02.cub
- [ ] wrong_map11e03.cub
- [ ] wrong_map11e04.cub
- [ ] wrong_map11e05.cub
- [ ] wrong_map12e01.cub
- [ ] wrong_map12e02.cub
- [ ] wrong_map12e03.cub
- [ ] wrong_map13e01.cub
- [ ] wrong_map13e02.cub
- [ ] wrong_map13e03.cub
- [ ] wrong_map13e04.cub
- [ ] wrong_map13e05.cub
- [ ] wrong_map14e01.cub
- [ ] wrong_map14e02.cub
- [ ] wrong_map14e03.cub
- [ ] wrong_map14e04.cub
- [ ] wrong_map14e05.cub
- [ ] wrong_map14e06.cub
- [ ] wrong_map14e07.cub
- [ ] wrong_map14e08.cub
- [ ] wrong_map14e09.cub
- [ ] wrong_map14e10.cub
- [ ] wrong_map14e11.cub
- [ ] wrong_map14e12.cub
- [ ] wrong_map14e13.cub
- [ ] wrong_map15e01.cub
- [ ] wrong_map15e02.cub
- [ ] wrong_map15e03.cub
- [ ] wrong_map16e01.cub
- [ ] wrong_map16e02.cub
- [ ] wrong_map16e03.cub
- [ ] wrong_map16e04.cub
- [ ] wrong_map16e05.cub
- [ ] wrong_map16e06.cub
- [ ] wrong_map16e07.cub
- [ ] wrong_map16e08.cub
- [ ] wrong_map19e01.cub