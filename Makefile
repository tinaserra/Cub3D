# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vserra <vserra@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/22 11:40:18 by vserra            #+#    #+#              #
#    Updated: 2021/03/11 12:28:42 by vserra           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c \
		debug.c \
		error.c \
		init_struct.c \
		parse_start.c \
		parse_int.c \
		parse_texture.c \
		parse_map.c \
		parse_check.c \
		parse_wall.c \
		ray_start.c \
		ray_utils.c \
		ray_moves1.c \
		ray_moves2.c \
		ray_draw.c \
		ray_texture.c \
		ray_sprite.c

NAME = Cub3D

LIBFT_DIR = libft
LIBFT = libft.a
MLX_DIR = mlx
MLX = libmlx.dylib

# diff entre .a et .dylib :
# .a = lib static, les fonctions utilisees sont directement ecrite dans le binaire
# .dylib = lib dynamique, les fonctions doivent etre chargees au momnent ou on lance le binaire

# override -> permet de reecrire la suite de la variable
override CFLAGS += -Wall -Wextra -Werror -MMD -O3 #-fsanitize=address

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DPD = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

# -C faire make comme si on etait dans le dossier
# -j multisreder / ameliore la vitesse de compliation
# Pas de regle opti car makefile mlx pas compatible
all:
	#@$(MAKE) -C $(MLX_DIR)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -j $(NAME)

# permet de pouvoir comparer la derniere modification de la dep par rapport a la regle
# -L donner le nom du dossier / -l donner le nom le la lib
# loader path = ecrit le chemin de la mlx dans le binaire pour pouvoir la retrouver au moment ou on lance le binaire
$(NAME): $(OBJ)
		@gcc $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_DIR) -l mlx -L $(LIBFT_DIR) -l ft
		@install_name_tool -change $(MLX) @loader_path/$(MLX_DIR)/$(MLX) $(NAME)
		@echo $(NAME) : Created !

# si le .c est plus recent que le .o on rentre dans la regle
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(MLX_DIR)/$(MLX) $(LIBFT_DIR)/$(LIBFT) | .gitignore
		@mkdir -p $(OBJ_DIR)
		@gcc $(CFLAGS) -I $(INC_DIR) -I $(MLX_DIR) -I $(LIBFT_DIR) -c $< -o $@

.gitignore:
		@echo $(NAME) > .gitignore

debug : fclean
	make all CFLAGS:="-DDEBUG -g"

clean:
	#@$(MAKE) clean -C $(MLX_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "obj deleted"

fclean:	clean
	@rm -rf $(LIBFT_DIR)/$(LIBFT)
	@echo "[$(LIBFT)]: deleted"
	@rm -rf $(NAME)
	@echo "[$(NAME)]: deleted"

re: fclean all

.PHONY: all, clean, fclean, re

# Utilise les .d (et ignore s'ils n'existe pas)
-include $(DPD)
