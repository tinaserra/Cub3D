#include "cub3d.h"

int     parsing_elements(char *str, t_parsing *parse)
{
	parse->i = 0;
	/* /!\ aux lignes vides */
		// if (*str[parse->i] == '\0')
		// 	return (0);

	/* /!\ aux espaces */
	while (str[parse->i] == ' ')
		parse->i++;

	//si c'est R resolution
	if (str[parse->i] == 'R')
		ft_putstr_fd("c'est R resolution\n", 1);

	//si c'est F sol ou C plafond
	if (str[parse->i] == 'F' || str[parse->i] == 'C')
		ft_putstr_fd("c'est F sol ou C plafond\n", 1);

	//si c'est texture (NO)
	if (str[parse->i] == 'N' && str[parse->i + 1] == 'O')
		ft_putstr_fd("c'est texture (NO)\n", 1);

	//si c'est texture (WE)
	if (str[parse->i] == 'W' && str[parse->i + 1] == 'E')
		ft_putstr_fd("c'est texture (WE)\n", 1);

	//si c'est texture (SO)
	if (str[parse->i] == 'S' && str[parse->i + 1] == 'O')
		ft_putstr_fd("c'est texture (SO)\n", 1);

	//si c'est texture (EA)
	if (str[parse->i] == 'E' && str[parse->i + 1] == 'A')
		ft_putstr_fd("c'est texture (EA)\n", 1);

	//si c'est S sprite
	if (str[parse->i] == 'S' && str[parse->i + 1] != 'O')
		ft_putstr_fd("c'est S sprite\n", 1);

	ft_putstr_fd("OKKKK\n", 1);
	return (0);
}

void	parsing(char *file, t_parsing *parse)
{
	int			fd;
	int			ret;
	char		*str;

	ret = 1;
	str = NULL;
	if ((fd = open(file, O_DIRECTORY)) != -1)
		ft_putstr_fd("ERROR : Invalide : is a directory\n", 1); // ft_error(parse, "Invalide : is a directory\n");
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_putstr_fd("ERROR : Invalide : file .cub invalide\n", 1); // ft_error(parse, "file .cub invalide\n");
	while (ret != 0)
	{
		ft_putstr_fd("\n- ON VA LIRE\n", 1);
		ret = get_next_line(fd, &str);
		printf("ligne = %s\n", str);
		parsing_elements(str, parse);
		// parse_color_resolution(&str, parse);
		// parse_texture(str, parse);
		// parse_map(str, parse);
		free(str);
	}
	close(fd);
	// if (parse->sizeline == 0 || parse->nblines == 0)
	// 	ft_error(parse, "Map absente\n");
	// ft_parsing_map(file, parse);
}

int		check_file_name(char *file, t_parsing *parse)
{
	// int			i;

	// i = 0;
	// while (str[parse->i] != '\0')
	// 	i++;
	// while (str[parse->i] != '.')
	// {
	// 	i--;
	// 	if (i == 0)
	// 	{
	// 		ft_error(parse, "Nom de la map invalide\n");
	// 		return (0);
	// 	}
	// }
	// if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
	parsing(file, parse);
	// else
	// 	ft_error(parse, "Nom de la map invalide\n");
	return (0);
}

// int			ft_printf(const char *str, ...)
// {
// 	int		i;
// 	t_data	data;

// 	i = 0;
// 	data.format = (unsigned char *)str;

// 	va_start(data.ap, str);

// 	parsing(&data);
// 	va_end(data.ap);
// 	return (data.nb_char);
// }

int main(int argc, char **argv)
{
	t_parsing parse;

	(void)argc;

	check_file_name(argv[1], &parse);
}