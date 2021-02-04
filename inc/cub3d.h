/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:40:27 by vserra            #+#    #+#             */
/*   Updated: 2021/02/04 12:19:15 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* HEADERS ----------- */

# include "mlx.h"
# include "libft.h"
# include "keycode_mac.h"
# include "error.h"

/* LIBRARIES ----------- */

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <limits.h>

/* VALUES ------------ */

#define DESTROYNOTIFY		17
#define STRUCTURENOTIFYMASK		0x20000 //1L<<17 // L = long

/* PARSING ----------- */

typedef struct	s_player
{
	char		orient_start;
	double		px;
	double		py;
	double		dirX; // vecteur de direction initiale (commence à -1 pour N, 1 pour S, 0 sinon)
	double		dirY; // vecteur de direction initiale (commence à -1 pour W, 1 pour E, 0 sinon)
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

typedef struct	s_parsing
{
	int			save;
	int			i;
	int			resx; // Résolution fenetre
	int			resy; // Résolution fenetre
	int			nb_lines;
	int			len_line;
	int			end_map;

	int			no;
	int			ea;
	int			so;
	int			we;

	char		**map;

	t_player	player;
	t_pcolor	col;
}				t_parsing;

/* RAYCSTING ----------- */

/* Toute la data de l'image (mlx_get_data_addr) */

typedef struct	s_image
{
	void		*image; 
	int			*data; //normalement char* addr
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_image;

/* Position de l'origine du carré dessiné */

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

/* Structure mère */

typedef struct	s_env
{
	void		*mlx;
	void		*window;
	int 		screen_width;
	int 		screen_height;
	char		keyboard[512];

	int			height_y; // learn_mlx
	int			width_x; // learn_mlx

	int			x; // chaque bande verticale de la fenetre, permet de parcourir les rayons
	// la version 2D raycaster du plan de la caméra
	double		planeX; // vecteur du plan (commence à 0.66 pour E, -0.66 pour W, 0 sinon)
	double		planeY; // vecteur du plan (commence à 0.66 pour N, -0.66 pour S, 0 sinon)
	double		time; // heure de la trame courante
	double		oldTime; // heure de l'image précédente
	double		cameraX; // coordonnée x dans l'espace caméra
	double		rayDirX; // la direction du rayon x
	double		rayDirY; // la direction du rayon y

	// dans quel carré de la carte nous nous trouvons
	int		mapX;
	int		mapY;

	// longueur du rayon de la position actuelle au cote x ou y suivant
	double		sideDistX; // distance que le rayon parcours jusqu'au premier point d'intersection vertical (= un coté x)
	double		sideDistY; // distance que le rayon parcours jusqu'au premier point d'intersection horizontal (= un coté y)

	// longueur du rayon d'un côté x ou y au coté x ou y
	double		deltaDistX; // = std::abs(1 / rayDirX);
	double		deltaDistY; // = std::abs(1 / rayDirY);
	double		perpWallDist; // distance du joueur au mur

	// dans quelle direction avancer dans la direction x ou y (+1 ou -1)
	int			stepX; // -1 si doit sauter un carre dans direction x negative, 1 dans la direction x positive
	int			stepY; // -1 si doit sauter un carre dans la direction y negative, 1 dans la direction y positive

	int			hit; // y a-t-il eu un mur touché?
	int			side; // 0 si c'est un cote x qui est touche (vertical), 1 si un cote y (horizontal)

	int			lineHeight; // hauteur de la ligne du mur a dessiner
	int			drawStart;
	int			drawEnd;
	double		moveSpeed;
	double		rotSpeed;

	t_coord		square_origin;

	t_image		img;
	t_parsing	parse;
}				t_env;

/* Couleurs */

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

// argb[0] == alpha
// argb[1] == r;
// argb[2] == g;
// argb[3] == b;

// toutes les variables commencent au meme endroit dans la memoire
// l'union prend la taille du plus grand type

// Une union est, à l’image d’une structure, un regroupement d’objet de type différents. 
// La nuance, et elle est de taille, est qu’une union est un agrégat qui ne peut contenir qu'un seul de ses membres à la fois.
// Autrement dit, une union peut accueillir la valeur de n’importe lequel de ses membres, mais un seul à la fois.

/* PROTOTYPES ------------ */

/*
** INIT_STRUCT
*/

void	init_parse(t_parsing *parse);
void	init_env(t_env *env);
void	init_start_mlx(t_env *env);

/*
** PARSE_START
*/

void	parsing(char *file, t_env *env);
// void	get_elements(char *str, t_parsing *parse);
// void	get_size_map(char *str, t_parsing *parse);
// int		get_map(char *file, t_parsing *parse);

/*
** PARSE_INT
*/

void	get_resolution(char *str, t_parsing *parse);
void	get_f_color(char* str, t_parsing *parse);
void	get_c_color(char* str, t_parsing *parse);

/*
** PARSE_MAP
*/

// int		player_position(t_parsing *parse, char c, int i, int j);
int		dup_map(char *str, t_parsing *parse);
int		is_a_map(char *str);
int		is_char_map(char *str, t_parsing *parse);


/*
** PARSE_CHECK
*/

int		check_after_map(char *str, t_parsing *parse);
int		check_element(t_parsing *parse);
int		check_color(t_parsing *parse, int ctrl);
int		check_strend(char *str, t_parsing *parse, int ctrl);

/*
** PARSE_WALL
*/

void	check_walls(t_parsing *parse);
void	check_borders(t_parsing *parse);

/*
** RAYCASTING_START
*/

int		start_mlx(t_env *env);

/*
** RAY_UTILS
*/

void	screen_size(t_env *env);
int		ft_key_release(int key, t_env *env);
int		ft_key_press(int key, t_env *env);
int		ft_quit(t_env *env);
int		ft_convert_color(t_color color, int endian);

/*
** RAY_MOVES
*/

void	go_straight(t_env *env);
void	go_back(t_env *env);
void	go_left(t_env *env);
void	go_right(t_env *env);

/*
** RAY_DRAW
*/

// int		ret_color(t_env *env, int alpha, int red, int green, int blue);
// void	put_px_to_img(t_image *img, int x, int y, int color);
void	draw_column(t_env *env, int coord_x);

/*
** ERROR
*/

void	free_error(t_parsing *parse, int error);
void	file_error(t_parsing *parse, int error);
void	element_error(t_parsing *parse, int error);
void	map_error(t_parsing *parse, int error);
void	mlx_error(t_parsing *parse, int error);
int		print_error(t_parsing *parse, int error);

/*
** DEBUG
*/

void	debug_parsing(t_parsing *parse);
void	debug_colors(t_parsing *parse, int ctrl);
void	debug_size_map(t_parsing *parse);
void	debug_resolution(t_parsing *parse);
void	debug_print_map(t_parsing *parse);

#endif
