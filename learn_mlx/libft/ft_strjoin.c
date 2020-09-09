/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 23:12:20 by vserra            #+#    #+#             */
/*   Updated: 2019/11/14 23:53:16 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *s1, char *s2)
{
	int		len;
	int		i;

	len = ft_strlen(s1);
	i = 0;
	while (s2[i])
	{
		s1[len + i] = s2[i];
		i++;
	}
	s1[len + i] = '\0';
	return (s1);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	int		total_size;

	if (!s1 || !s2)
		return (NULL);
	total_size = (ft_strlen((char *)s1) + ft_strlen((char *)s2));
	if (!(out = malloc(total_size + 1)))
		return (NULL);
	out[0] = '\0';
	out = ft_strcat(out, (char *)s1);
	out = ft_strcat(out, (char *)s2);
	return (out);
}
