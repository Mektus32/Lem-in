/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liba_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 17:33:04 by qgilbert          #+#    #+#             */
/*   Updated: 2019/08/17 17:33:06 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	*make_mass_cant_go(t_map *map, t_list_i *cant_go)
{
	int	*dist;
	int	i;

	dist = make_mass(map->m * map->c_r);
	i = 0;
	while (i < map->m * map->c_r)
	{
		if (find_room(cant_go, i) && i != 0 && i != map->c_r)
			dist[i] = -1;
		i++;
	}
	return (dist);
}
