/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:11:57 by ojessi            #+#    #+#             */
/*   Updated: 2019/08/14 19:35:48 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

void	ft_next_read(t_ob *ob, char *line)
{
	if (!ft_strcmp(line, "##start"))
	{
		free(line);
		get_next_line(ob->fd, &line);
		ft_push_back_room(&ob->rooms, ft_create_room(line, 1, ob));
		ob->c_rooms++;
	}
	else if (!ft_strcmp(line, "##end"))
	{
		free(line);
		get_next_line(ob->fd, &line);
		ft_push_back_room(&ob->rooms, ft_create_room(line, -1, ob));
		ob->c_rooms++;
	}
	else if (line[0] == 'L')
		ft_push_back_turn(&ob->turn, line);
	else if (ft_isdigonly(line))
	{
		ob->ants = ft_atoi(line);
		free(line);
	}
	else
		free(line);
}

int		ft_read(t_ob *ob)
{
	char	*line;

	while (get_next_line(ob->fd, &line) > 0)
		if (ft_strstr(line, "ERROR"))
		{
			free(line);
			return (1);
		}
		else if (line[0] != '#' && ft_count_words(line) == 3 && line[0] != 'L')
		{
			ft_push_back_room(&ob->rooms, ft_create_room(line, 0, ob));
			ob->c_rooms++;
		}
		else if (line[0] != '#' && ft_count_words(line) == 1 &&
			!ft_isdigonly(line) && line[0] != 'L')
		{
			ft_add_neib(&ob->rooms, line);
			ft_super_strrev(line);
			ft_add_neib(&ob->rooms, line);
			free(line);
		}
		else
			ft_next_read(ob, line);
	return (0);
}
