/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:40:27 by vserra            #+#    #+#             */
/*   Updated: 2021/03/21 13:48:09 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** HEADERS ------------------------------------------------------------------ **
*/

# include "mlx.h"
# include "libft.h"
# include "keycode_mac.h"
# include "error.h"

/*
** LIBRARIES ---------------------------------------------------------------- **
*/

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <limits.h>

/*
** VALUES ------------------------------------------------------------------- **
*/

#define DESTROYNOTIFY		17
#define STRUCTURENOTIFYMASK		0x20000 //1L<<17 // L = long

/*
** STRUCTURES --------------------------------------------------------------- **
*/

enum	e_bgra
{
	BGRA_BLUE,
	BGRA_GREEN,
	BGRA_RED,
	BGRA_ALPHA
};

enum	e_argb
{
	ARGB_ALPHA,
	ARGB_RED,
	ARGB_GREEN,
	ARGB_BLUE
};

typedef union		u_color
{
	int				all;
	unsigned char	argb[4];
	unsigned char	bgra[4];
}				t_color;

/*
** argb[0] == alpha; argb[1] == r; argb[2] == g; argb[3] == b;
**
** toutes les variables commencent au meme endroit dans la memoire
** l'union prend la taille du plus grand type
**
** Une union est, à l’image d’une structure, un regroupement d’objet de type
** différents. La nuance, et elle est de taille, est qu’une union est un agrégat
** qui ne peut contenir qu'un seul de ses membres à la fois.
** Autrement dit, une union peut accueillir la valeur de n’importe lequel
** de ses membres, mais un seul à la fois.
*/

enum	e_tex
{
	NO,
	WE,
	SO,
	EA,
	S,
	ALL
};

typedef struct	s_texture
{
	int			x; // coordonnée x de la texture
	int			y; // coordonée y de la texture
	int			dir; //direction NO, S, EA, WE de la texture
	double		wallx; // valeur où le mur a été touché : coordonnée y si side == 0, coordonnée x si side == 1
	double		step; // indique de combien augmenter les coordonnées de la texture pour chaque pixel
	double		pos; // coordonnée de départ
	char		*path_no;
	char		*path_we;
	char		*path_so;
	char		*path_ea;
	char		*path_s;
}				t_texture;

typedef struct	s_player
{
	char		orient_start;
	double		x;
	double		y;
	double		dirx; // vecteur de direction initiale (commence à -1 pour N, 1 pour S, 0 sinon)
	double		diry; // vecteur de direction initiale (commence à -1 pour W, 1 pour E, 0 sinon)
	double		mspeed;
	double		rspeed;
}				t_player;

typedef struct	s_pcolor
{
	int			red_c;
	int			green_c;
	int			blue_c;
	int			red_f;
	int			green_f;
	int			blue_f;
}				t_pcolor;

typedef struct	s_map
{
	int			x; // coordonnee x dans quel carré de la carte nous nous trouvons
	int			y; // coordonnee y dans quel carré de la carte nous nous trouvons
	int			nb_lines;
	int			len_line;
	int			end_map;
	char		**map;
}				t_map;

/* Toute la data de l'image (mlx_get_data_addr) */

typedef struct	s_image
{
	void		*image; 
	int			*data; //normalement char* addr
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_image;

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct	s_dbcoord
{
	double		x;
	double		y;
}				t_dbcoord;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		dist;
	double		invdet;
	int			sx;
	int			h;
	int			w;
	int			color;
	t_coord		dstart;
	t_coord		dend;
	t_coord		tex;
	t_dbcoord	tform;
}				t_sprite;

/* Structure mère */

typedef struct	s_env
{
	int			i;
	int			x; // chaque bande verticale de la fenetre, permet de parcourir les rayons
	int 		screen_width;
	int 		screen_height;
	int			save;
	int			hit; // y a-t-il eu un mur touché?
	int			side; // 0 si c'est un cote x qui est touche (vertical), 1 si un cote y (horizontal)
	int			lineh; // hauteur de la ligne du mur a dessiner
	int			dstart;
	int			dend;
	void		*mlx;
	void		*window;
	double		camerax; // coordonnée x dans l'espace caméra
	double		pwdist; // distance du joueur au mur
	char		keyboard[512];
	int			nbsprite;
	double		*zbuffer;

	t_coord		step; // -1 si doit sauter un carre dans direction x ou y negative, 1 dans la direction x ou y positive
	t_dbcoord	deltadist; // longueur du rayon d'un côté x ou y au coté x ou y
	t_dbcoord	sidedist; // distance que le rayon parcours jusqu'au premier point d'intersection (vertical = un coté x, horizontal = un coté y)
	t_dbcoord	plane; // vecteur du plan (plane.x = commence à 0.66 pour E, -0.66 pour W, 0 sinon, plane.y = commence à 0.66 pour N, -0.66 pour S, 0 sinon)
	t_dbcoord	raydir; // la direction du rayon
	t_image		tx[ALL];
	t_coord		res;
	t_player	ply;
	t_pcolor	col;
	t_map		map;
	t_sprite	*spr; // en fonction du nombre de sprite
	t_texture	tex;
	t_image		img;
}				t_env;


/*
** PROTOTYPES --------------------------------------------------------------- **
*/

/* init_struct */
void	init_parse(t_env *env);
void	init_env(t_env *env);
void	init_start_mlx(t_env *env);
void	init_texture(t_env *env);

/* parse_start */
void	parsing(char *file, t_env *env);

/* parse_int */
void	get_resolution(char *str, t_env *env);
void	get_f_color(char* str, t_env *env);
void	get_c_color(char* str, t_env *env);

/* parse_map */
int		dup_map(char *str, t_env *env);
int		is_a_map(char *str);
int		is_char_map(char *str, t_env *env);

/* parse_check */
int		check_after_map(char *str, t_env *env);
int		check_element(t_env *env);
int		check_color(t_env *env, int ctrl);
int		check_strend(char *str, t_env *env, int ctrl);

/* parse_wall */
void	check_walls(t_env *env);

/* parse_texture */
char	*get_path(char *str, int i, t_env *env);

/* ray_start */
int		start_mlx(t_env *env);

/* ray_utils */
void	screen_size(t_env *env);
int		ft_key_release(int key, t_env *env);
int		ft_key_press(int key, t_env *env);
int		ft_convert_color(t_color color, int endian);

/* ray_moves 1 & 2 */
int		ft_quit(t_env *env);
void	go_straight(t_env *env);
void	go_back(t_env *env);
void	go_left(t_env *env);
void	go_right(t_env *env);
void	keys_control(t_env *env);

/* ray_draw */
void	draw_column(t_env *env, int coord_x);
void	draw_sprite(t_env *env, int i);

/* ray_texture */
void	calc_texture(t_env *env);
void	get_texture(t_env *env);

/* ray_sprite */
void	sprite_casting(t_env *env);

/* bmp */
void	save_bmp(t_env *env);

/* error */
int		print_error(t_env *env, int error);

/* debug */
void	debug_parsing(t_env *env);
void	debug_print_map(t_env *env);

#endif
