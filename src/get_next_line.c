/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:42:00 by vserra            #+#    #+#             */
/*   Updated: 2021/02/18 15:42:02 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_line(char *s)
{
	char	*res;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (!(res = malloc(i + 1)))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_str(char *s)
{
	int		i;
	int		j;
	char	*out;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	if (!(out = malloc(ft_strlen(s) - i + 1)))
		return (NULL);
	i++;
	j = 0;
	while (s && s[i])
		out[j++] = s[i++];
	out[j] = '\0';
	free(s);
	return (out);
}

int		get_next_line(t_env *env, int fd, char **line)
{
	int			ret;
	char		*buffer;
	// static char	*str;

	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buffer = malloc(BUFFER_SIZE + 1)))
		return (-1);
	ret = 1;
	while (ft_strchr(env->str, '\n') == NULL && ret != 0)
	{
		if ((ret = read(fd, buffer, BUFFER_SIZE)) == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[ret] = '\0';
		env->str = ft_strjoin_free(env->str, buffer, 'L');
	}
	free(buffer);
	*line = get_line(env->str);
	env->str = get_str(env->str);
	return (ret == 0 ? 0 : 1);
}
