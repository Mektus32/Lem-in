/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liba.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 15:05:04 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/14 15:05:06 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
// ищем длину инта, для прохождение по строке
int		ft_len_int(int num)
{
	int	len;

	len = 0;
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	if (num == 0)
		return (1);
	return (len);
}

int ft_max_mass(int *mass, int k)
{
	int max;
	int i;

	i = 0;
	max = mass[i++];
	while (i < k)
	{
		if(mass[i] > max)
			max = mass[i];
		i++;
	}
	return (max);
}

int *make_mass(int k)
{
	int i;
	int *dist;

	dist = (int*)malloc(sizeof(int) * (k + 1));
	i = 0;
	while (i <= k)
		dist[i++] = k + 1;
	dist[0] = 0;
	return (dist);
}