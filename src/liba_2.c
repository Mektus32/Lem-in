#include "lem_in.h"

int *make_mass_cant_go(t_map *map, t_list_i *cant_go)
{
	int	*dist;
	int	i;


	dist = make_mass(2 * map->c_room);
	i = 0;
	while (i < 2 * map->c_room)
	{
		if (find_room(cant_go, i) && i != 0 && i != map->c_room)
			dist[i] = -1;
		i++;
	}
	return (dist);
}

