/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 17:16:18 by ojessi            #+#    #+#             */
/*   Updated: 2019/06/30 17:16:19 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


int main(int ac, char	**av)
{
	int		fd;
	t_map	*map;
	char	*str;

	ac = 0;
	av = NULL;
	str = "../test";
	//str = av[1];
	map = (t_map*)malloc(sizeof(t_map));
	map->rooms = NULL;
	map->link = NULL;
	map->link_copy = NULL;
	map->link_new = NULL;
	map->sh = NULL;
	map->two_path = NULL;
	fd = open(str, O_RDONLY);
	if (make_map(fd, map) && check_room(map))
	{
		main_path(map);
		ant_in_room(map);
		ft_free_map(&map);
	}
	else// и все почистить бы
	{
		ft_printf("ERROR");
	}
	return (0);
}

