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


typedef struct		s_room
{
	int				x;//координаты комнаты
	int				y;
	char			*name;
	int				number;// у первой №0, у последней № c_room
	struct s_room	*next;
}					t_room;
//главная структура, которую везде передавать
typedef struct		s_map
{
	int				fd;
	int				c_room;//кол - во комнат
	int				**matr;//матрица смежности
	t_room			*rooms;//лист всех комнат
}					t_map;



int	check_room(t_map *map);
int		ft_len_int(int num);
t_room	*ft_create_ele(char *line, int number);
void ft_pushback(t_room **head, t_room *new);

#endif
