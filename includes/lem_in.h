/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:44:03 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/30 16:44:04 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include <stdio.h>
#include <fcntl.h>

# include "libft.h"
# include "ft_printf.h"




typedef struct	s_room
{
	int			x;
	int			y;
	char		*name;
	int			number;
}				t_room;

typedef struct		s_rlist
{
	t_room			*content;
	size_t			content_size;
	struct s_rlist	*next;
}					t_rlist;

int	check_room(int fd, t_rlist **rooms);

#endif
