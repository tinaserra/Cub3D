/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_linux.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vserra <vserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 07:37:47 by vserra            #+#    #+#             */
/*   Updated: 2021/03/21 20:28:01 by vserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODE_LINUX_H
# define KEYCODE_LINUX_H

# define KEYPRESS 2
# define KEYRELEASE 3
# define KEYPRESSMASK 1L<<0
# define KEYRELEASEMASK 1L<<1
# define DESTROYNOTIFY 33
# define STRUCTURENOTIFYMASK 1L<<0

/*
** Linux qwerty
*/

# define KEY_ESCAPE 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_S 115
# define KEY_D 100
# define KEY_A 97

#endif
