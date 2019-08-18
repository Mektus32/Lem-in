/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aliba.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgilbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 17:36:03 by qgilbert          #+#    #+#             */
/*   Updated: 2019/08/17 17:36:04 by qgilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		ft_len_int(int num)
{
	int	len;

	if (num == 0)
		return (1);
	len = 0;
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

int		ft_max_mass(int *mass, int k)
{
	int	max;
	int	i;

	i = 0;
	max = mass[i++];
	while (i < k)
	{
		if (mass[i] > max)
			max = mass[i];
		i++;
	}
	return (max);
}

int		*make_mass(int k)
{
	int	i;
	int	*dist;

	dist = (int*)malloc(sizeof(int) * (k + 1));
	i = 1;
	while (i <= k)
		dist[i++] = k + 1;
	dist[0] = 0;
	return (dist);
}

char	*ft_check_cmd(int *fd)
{
	char	*line;

	while (get_next_line(*fd, &line) == 1)
	{
		if ((ft_strequ(line, "##start") || ft_strequ(line, "##end")))
			return (line);
		else if (line[0] == '#')
			ft_str_print_del(&line);
		else
			return (line);
	}
	return (NULL);
}

void	ft_str_print_del(char **as)
{
	if (!as)
		return ;
	ft_printf("%s\n", *as);
	free(*as);
	*as = NULL;
}
