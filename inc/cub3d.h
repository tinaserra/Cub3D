#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include "keycode_mac.h"

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
