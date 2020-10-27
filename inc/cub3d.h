/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:40:27 by vserra            #+#    #+#             */
/*   Updated: 2020/10/24 11:06:36 by vserra           ###   ########.fr       */
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
	CUB_DIR,
	CUB_INVALIDE,
	RESOLUTION,
	RESOLUTION_END,
	F_COLOR,
	F_COLOR_END,
	C_COLOR,
	C_COLOR_END,
	DOUBLE_ELEMENT,
	MAP_CHAR_AFTER
}				t_error;

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
int		get_elements(char *str, t_parsing *parse);
int		get_size_map(char *str, t_parsing *parse);

/*
** PARSE_INT
*/

int		get_resolution(char *str, t_parsing *parse);
int		get_f_color(char* str, t_parsing *parse);
int		get_c_color(char* str, t_parsing *parse);

/*
** PARSE_MAP
*/

int		is_char_map(char *str, t_parsing *parse);
int		check_element(t_parsing *parse);
int		check_after_map(char *str, t_parsing *parse);

/*
** ERROR
*/

void	print_error(t_parsing *parse, int error);

/*
** DEBUG
*/

void	debug_colors(t_parsing *parse, int ctrl);
void	debug_size_map(t_parsing *parse);
void	debug_resolution(t_parsing *parse);

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
