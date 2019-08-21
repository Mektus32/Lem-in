/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acheck_n_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:31:03 by qgilbert          #+#    #+#             */
/*   Updated: 2019/08/14 20:31:04 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_ant_in_path(int n_ant, int c_path, int len_max, t_map *map)
{
	int	f;
	int	k;

	f = 1;
	while (n_ant > 0 && f)
	{
		k = 0;
		f = 0;
		while (k < c_path && n_ant)
		{
			if (map->dist[k] < len_max)
			{
				map->dist[k] += 1;
				n_ant--;
				f++;
			}
			k++;
		}
	}
	free(map->dist);
	return (n_ant);
}

/*
** path_new кончается комнатой -10
** ft_ant_in_path - до равновесия заполним все пути муравьями
** t_now - время, которое потребуется для прохода этого состояния
** если муравьев не 0, +1
*/

int		ft_check_path_n(t_list_down *two_path, t_map *map, int n)
{
	t_list_down	*path_new;
	int			n_ant;
	int			c_path;
	int			t_now;
	int			len_max;

	if (n == 1)
		path_new = two_path->right;
	else
		path_new = two_path->right->right;
	c_path = ft_list_len_down(path_new) - 1;
	map->dist = (int *)malloc(sizeof(int) * c_path);
	path_new = path_new->down;
	n_ant = 0;
	while (path_new->next)
	{
		map->dist[n_ant++] = path_new->content;
		path_new = path_new->down;
	}
	n_ant = map->c_ant;
	len_max = ft_max_mass(map->dist, c_path);
	n_ant = ft_ant_in_path(n_ant, c_path, len_max, map);
	t_now = len_max + n_ant / c_path + ((n_ant == 0 || (n_ant % c_path == 0)) ?
			0 : 1) - c_path;
	if (t_now < two_path->content && map->c_ant >= c_path)
		return (t_now);
	return (0);
}
