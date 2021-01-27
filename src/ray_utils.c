

#include "cub3d.h"

void	put_px_to_img(t_image *img, int x, int y, int color)
{
	img->data[img->size_line / 4 * y + x] = color;
}

/*
** *(int *)&img->data[img->size_line * y + x * img->bits_per_pixel / 8] = color;

** size_line == taille de ligne de l image.
** bits_per_pixel == un nombre de bit pour un pixel en memoire.

** pour avancer de ligne en ligne avec un buffer de une dimmension : avancer de size_ligne en size_ligne.
** Pour avancer d un pixel dans une ligne il faut avancer de bite par pixel / 8. (un byte = 8 bites)
** Mettre un int dans un char* = on recupere l adresse de data(&). on le cast en int*. + *devant pour y acceder.

** on cast directement la fontion mlx_get_data_adr du coup on le stock dans un int *data.
** on peux supprimer le cast du debut, puisque c est deja un int qu on veux mettre dans un int.
** vu que c est int int* on avance de 4. donc on supprime le '* img->bits_per_pixel / 8' car c etait = 4.
*/

int	ft_convert_color(t_color color, int endian)
{
	t_color	temp;

	if (endian == 1)
	{
		temp.all = color.all;
		color.bgra[BGRA_ALPHA] = color.argb[ARGB_ALPHA];
		color.bgra[BGRA_RED] = color.argb[ARGB_RED];
		color.bgra[BGRA_GREEN] = temp.argb[ARGB_GREEN];
		color.bgra[BGRA_BLUE] = temp.argb[ARGB_BLUE];
	}
	return (color.all);
}

int ft_quit(t_env *env)
{
	mlx_destroy_image(env->mlx, env->img.image);
	mlx_destroy_window(env->mlx, env->window);
	exit(0);
}

int	ft_key_press(int key, t_env *env)
{
	env->keyboard[key] = 1;
	return (0);
}

int	ft_key_release(int key, t_env *env)
{
	env->keyboard[key] = 0;
	return (0);
}

// Fonction a changer de fichier ! 😎

void	screen_size(t_env *env)
{
	// avec mlx_get_screen_size -> connaitre la resolutiion de l'ecran utilisé,
	// si la res demandé dans le file.cub est supperieur a l'ecran alors choisr une resolution plus petite (celle de l'ecran)

	mlx_get_screen_size(env->mlx, &env->screen_width, &env->screen_height);
	if (env->parse.resx > env->screen_width)
		env->parse.resx = env->screen_width;
	if (env->parse.resy > env->screen_height)
		env->parse.resy = env->screen_height;

}
