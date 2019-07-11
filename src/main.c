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
	int fd;
	t_map *map;

	map = (t_map*)malloc(sizeof(t_map));
	fd = open(av[1], O_RDONLY);
	if (make_map(fd, map) && check_room(map))
	{
		// теперь нужен поиск в ширину
		ft_bfs(map);
	}
	else// и все почистить бы
	{

		ft_printf("ERROR");
	}
	return (0);
}
