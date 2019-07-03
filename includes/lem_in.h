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

# include "libft.h"
# include "ft_printf.h"

typedef struct 		s_room
{
	int 			x;
	int 			y;
	char 			*name;
	int 			number;
	struct s_room	*next;
}					t_room;

typedef struct 		s_map
{
	int 	fd;
	int 	roomcount;
	int 	**matrix;
	t_room	**rooms;
}					t_map;

#endif
