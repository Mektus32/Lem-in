/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 21:36:54 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/15 21:36:56 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

void	ft_draw_rooms(t_ob *ob)
{
	t_room	*room;

	room = ob->rooms;
	while (room->down)
	{
		mlx_put_image_to_window(ob->mlx_ptr, ob->win_ptr, room->image,
				room->x, room->y);
		//Линиии рисовать надо через mlx_put_pixel
		printf("room[%s]-x[%d]-y[%d]\n", room->name, room->x, room->y);
		room = room->down;
	}
}

void	ft_draw(t_ob *ob)
{
	int 	weidth;
	int 	height;

	weidth = WIDTH;
	height = HEIGHT;
	ob->image->img_background = mlx_xpm_file_to_image(ob->mlx_ptr, BACKGROUND,
	&weidth, &height);
	mlx_put_image_to_window(ob->mlx_ptr, ob->win_ptr, ob->image->img_background,
			0, 0);
	ft_draw_rooms(ob);
	key_hook(ob);
	mlx_loop(ob->mlx_ptr);
}
