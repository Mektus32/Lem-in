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

	if (ac == 1)
	{
		//fd = /Users/qgilbert/Desktop/lem_in/six/School21-Lem-in/lem-in_test 2/tests/test_5.map
		fd = open("../test", O_RDONLY);
		//fd = 0;
	}
	else
	{
		str = av[1];
		fd = open(str, O_RDONLY);
	}
	map = (t_map*)malloc(sizeof(t_map));
	map->rooms = NULL;
	map->link = NULL;
	map->link_copy = NULL;
	map->link_new = NULL;
	map->sh = NULL;
	map->two_path = NULL;
	if (make_map(fd, map) && check_room(map) && map->rooms->number == 0 && ft_list_i_head(map->c_room, map->link)->next != NULL )
	{
		main_path(map);
		if (map->two_path->down->content)
			ant_in_room(map);
	}
	else
		ft_printf("ERROR\n");
	ft_free_map(&map);
	return (0);
}

