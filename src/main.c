#include "cub3d.h"

int error(char *str)
{
	ft_putstr_fd(str, 2);
	return(1);
}

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

** ont cast directement la fontion mlx_get_data_adr du coup on le stock dans un int *data.
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

void draw_square(t_env *env)
{
	int x;
	int y;
	int all;

	y = 0;
	while (y < 100)
	{
		x = 0;
		while (x < 100)
		{
			// mlx_pixel_put(mlx, window, x++, y, 0xffffff);
			// put_px_to_img(&img, x++, y, 0xFF4233);
			t_color color;
			color.argb[BGRA_ALPHA] = 0;
			color.argb[BGRA_RED] = 255;
			color.argb[BGRA_GREEN] = 95;
			color.argb[BGRA_BLUE] = 95;
			all = ft_convert_color(color, env->img.endian);
			put_px_to_img(&env->img, env->square_origin.x + x, env->square_origin.y + y, all);
			x++;
		}
		y++;
	}
}


int	game_update(t_env *env)
{
	if (env->keyboard[KEY_ESCAPE])
		ft_quit(env);
	if(env->keyboard[KEY_D] && env->square_origin.x < env->width_x)
		env->square_origin.x++;
	if(env->keyboard[KEY_A] && env->square_origin.x > 0)
		env->square_origin.x--;
	if(env->keyboard[KEY_W] && env->square_origin.y > 0)
		env->square_origin.y--;
	if(env->keyboard[KEY_S] && env->square_origin.y < env->height_y)
		env->square_origin.y++;
	ft_bzero(env->img.data, env->img.size_line * env->height_y);
	draw_square(env);
	mlx_put_image_to_window(env->mlx, env->window, env->img.image, 0, 0);

	return (0);
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

int	main(void)
{
	t_env env;

	ft_bzero(&env, sizeof(t_env));

	env.height_y = 600;
	env.width_x = 1200;
	if ((env.mlx = mlx_init()) == NULL)
		return (error("FAILED : Init mlx\n"));
	if (!(env.window = mlx_new_window(env.mlx, env.width_x, env.height_y, "Mon super titre")))
		return (error("FAILED : Create new window\n"));
	if (!(env.img.image = mlx_new_image(env.mlx, env.width_x, env.height_y)))
		return (error("FAILED : Create new image"));
	env.img.data = (int*)mlx_get_data_addr(env.img.image, &env.img.bits_per_pixel, &env.img.size_line, &env.img.endian);
	ft_putstr_fd("Hello World !\n", 1);
	mlx_hook(env.window, DESTROYNOTIFY, STRUCTURENOTIFYMASK, ft_quit, &env);
	mlx_hook(env.window, KEYPRESS, KEYPRESSMASK, ft_key_press, &env);
	mlx_hook(env.window, KEYRELEASE, KEYRELEASEMASK, ft_key_release, &env);
	mlx_loop_hook(env.mlx, game_update, &env);
	mlx_loop(env.mlx);
	return (0);
}