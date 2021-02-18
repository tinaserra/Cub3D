/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:03:31 by vserra            #+#    #+#             */
/*   Updated: 2021/02/18 14:26:07 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, int ctrl)
{
	int		i;
	int		j;
	char	*out;

	if ((out = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)) == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		out[i + j] = s2[j];
		j++;
	}
	out[i + j] = '\0';
	if (ctrl == 'L' || ctrl == 'B')
		free(s1);
	if (ctrl == 'R' || ctrl == 'B')
		free(s2);
	return (out);
}
