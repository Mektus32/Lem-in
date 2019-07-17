/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_funct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 20:51:00 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/15 20:51:06 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

char	*ft_super_strrev(char *line)
{
	int		i;
	char	*part1;
	char	*part2;

	i = 0;
	while (line[i] != '-')
		i++;
	part1 = ft_strsub(line, 0, i);
	i++;
	part2 = ft_strjoin(line + i, "-");
	free(line);
	return (ft_free_strjoin_duo(part2, part1));
}

void	ft_room_color(t_room **list, int cont, t_ob *ob)
{
	int		weight;
	int		height;

	weight = 1;
	height = 1;
	if (cont == 0)
		(*list)->image = mlx_xpm_file_to_image(ob->mlx_ptr, ROOMA, &weight,
				&height);
	else if (cont == 1)
		(*list)->image = mlx_xpm_file_to_image(ob->mlx_ptr, ROOMS, &weight,
				&height);
	else
		(*list)->image = mlx_xpm_file_to_image(ob->mlx_ptr, ROOME, &weight,
				&height);
}
