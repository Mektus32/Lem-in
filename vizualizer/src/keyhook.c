/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:36:57 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/15 14:36:58 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

int		expose(void *param)
{
	t_ob	*ob;

	ob = param;
	(void)ob;
	exit(0);
	return (0);
}

int 	keyboard(int key, void *param)
{
	t_ob	*ob;

	ob = param;
	if (key == 53)
		exit(0);
	if (key == 124)
	{
		ob->cur = ft_move_turn_next(ob->cur, 1);
		ft_draw_turn(ob);
	}
	return (0);
}

void	key_hook(t_ob *ob)
{
	mlx_hook(ob->win_ptr, 3, 0, keyboard, ob);
	mlx_hook(ob->win_ptr, 17, 0, expose, ob);
}
