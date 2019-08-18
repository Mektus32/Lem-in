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

	dist = make_mass(map->m * map->c_r);
	while (cant_go)
	{
		if (cant_go->cnt != 0 && cant_go->cnt != map->c_r )//&& i < map->m * map->c_r)
			dist[cant_go->cnt] = -1;
		cant_go = cant_go->next;
	}
	dist[0] = 0;
	return (dist);
}
