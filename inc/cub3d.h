/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:40:27 by vserra            #+#    #+#             */
/*   Updated: 2020/11/04 17:23:45 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* HEADERS ----------- */

# include "mlx.h"
# include "libft.h"
# include "keycode_mac.h"

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

/* VALUES ----------- */

#define DESTROYNOTIFY		17
#define STRUCTURENOTIFYMASK		0x20000 //1L<<17 // L = long

/* Toute la data de l'image (mlx_get_data_addr) ----------- */

typedef struct	s_image
{
	void		*image; 
	int			*data; //normalement char* addr
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_image;

/* Position de l'origine du carré dessiné ------------------ */

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

/* Structure mère ------------------------------------------ */


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

typedef enum	e_error{
	FILE_NAME,
	CUB_DIR,
	CUB_INVALIDE,
	RESOLUTION,
	RESOLUTION_END,
	F_COLOR,
	F_COLOR_END,
	C_COLOR,
	C_COLOR_END,
	MORE_NUM,
	DOUBLE_ELEMENT,
	MAP_WRONG_CHAR,
	MAP_CHAR_AFTER,
	NO_MAP,
	MULTI_PLAYER,
	

	MALLOC_FAILED
}				t_error;

typedef struct	s_env
{
	void		*mlx;
	void		*window;
	int 		height_y;
	int 		width_x;
	char		keyboard[512];
	t_coord		square_origin;
	t_image		img;
}				t_env;

typedef struct	s_player
{
	char		orient_start;
	int			px;
	int			py;
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
	int			i;
	int			resx;
	int			resy;
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

/*
** INIT_STRUCT
*/

void	init_parse(t_parsing *parse);


/*
** PARSE_START
*/

void	parsing(char *file, t_parsing *parse);
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

int		is_char_map(char *str, t_parsing *parse, int ctrl);
// int		player_position(t_parsing *parse, char c, int i, int j);
int		dup_map(char *str, t_parsing *parse);
void	wall_in_row(t_parsing *parse);

/*
** PARSE_CHECK
*/
int		check_after_map(char *str, t_parsing *parse);
int		check_element(t_parsing *parse);
int		check_color(t_parsing *parse, int ctrl);
int		check_strend(char *str, t_parsing *parse, int ctrl);
// int		check_is_map(char *str, t_parsing *parse);

/*
** ERROR
*/

void	print_error(t_parsing *parse, int error);
void	free_error(t_parsing *parse, int error);

/*
** DEBUG
*/

void	debug_parsing(t_parsing *parse);
void	debug_colors(t_parsing *parse, int ctrl);
void	debug_size_map(t_parsing *parse);
void	debug_resolution(t_parsing *parse);
void	debug_print_map(t_parsing *parse);

// argb[0] == alpha
// argb[1] == r;
// argb[2] == g;
// argb[3] == b;

// toutes les variables commencent au meme endroit dans la memoire
// l'union prend la taille du plus grand type

// Une union est, à l’image d’une structure, un regroupement d’objet de type différents. 
// La nuance, et elle est de taille, est qu’une union est un agrégat qui ne peut contenir qu'un seul de ses membres à la fois.
// Autrement dit, une union peut accueillir la valeur de n’importe lequel de ses membres, mais un seul à la fois.
#endif
