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

void	ft_draw_menu(t_ob *ob)
{
	const char 	*ants = ft_free_strjoin_rev("Ants = ", ft_itoa(ob->ants));
	const char 	*room = ft_free_strjoin_rev("Rooms = ", ft_itoa(ob->c_rooms));
	const char 	*sp = ft_free_strjoin_rev("Speed = ", ft_itoa(ob->speed));

	mlx_string_put(ob->mlx_ptr, ob->win_ptr, 10, 25, 0xD75728, "Menu");
	mlx_string_put(ob->mlx_ptr, ob->win_ptr, 10, 50, 0xD75728, (char*)ants);
	mlx_string_put(ob->mlx_ptr, ob->win_ptr, 10, 75, 0xD75728, (char*)room);
	mlx_string_put(ob->mlx_ptr, ob->win_ptr, 10, 100, 0x2ECC30, (char*)sp);
	mlx_string_put(ob->mlx_ptr, ob->win_ptr, 10, 125, 0xD75728,
	"Space = Pause");
	mlx_string_put(ob->mlx_ptr, ob->win_ptr, 10, 150, 0xD75728,
	"Restart = R");
	free((void*)ants);
	free((void*)room);
	free((void*)sp);
}

void	ft_draw_lines(t_ob *ob)
{
	t_room	*room;
	t_neib	*neib;
	int 	arr[4];

	room = ob->rooms;
	while (room)
	{
		neib = room->next;
		while (neib)
		{
			arr[0] = room->x;
			arr[1] = room->y;
			arr[2] = ft_get_x_room(ob->rooms, neib->name);
			arr[3] = ft_get_y_room(ob->rooms, neib->name);
			ft_draw_links(arr, ob);
			neib = neib->next;
		}
		room = room->down;
	}
}

void	ft_draw_all(t_ob *ob)
{
	t_room	*room;
	int 	i;

	mlx_clear_window(ob->mlx_ptr, ob->win_ptr);
	mlx_put_image_to_window(ob->mlx_ptr, ob->win_ptr, ob->image->img_background
	,0 ,0);
	ft_draw_lines(ob);
	room = ob->rooms;
	while (room)
	{
		mlx_put_image_to_window(ob->mlx_ptr, ob->win_ptr, room->image,
				room->x - 25, room->y - 25);
		mlx_string_put(ob->mlx_ptr, ob->win_ptr, room->x - 5, room->y - 10, 0x000000,
				room->name);
		room = room->down;
	}
	i = -1;
	while (++i < ob->ants)
		mlx_put_image_to_window(ob->mlx_ptr, ob->win_ptr, ob->image->img_ant,
							ob->arr[i].x - 25, ob->arr[i].y - 25);
	ft_draw_menu(ob);
}

void	ft_draw_turn(t_ob *ob)
{
	int 	i;
	t_turn	*cur;
	int static	j = -1;
	int 		arr[2];

	cur = ob->cur;
	i = -1;
	while (cur && cur->matr[++i])
		if (ob->arr[ft_atoi(cur->matr[i] + 1) - 1].x !=
		ft_get_x_room(ob->rooms, ft_strchr(cur->matr[i], '-') + 1) ||
		ob->arr[ft_atoi(cur->matr[i] + 1) - 1].y != ft_get_y_room(ob->rooms,
		ft_strchr(cur->matr[i], '-') + 1))
		{
			arr[0] = ft_get_x_room(ob->rooms, ft_strchr(cur->matr[i], '-') + 1);
			arr[1] = ft_get_y_room(ob->rooms, ft_strchr(cur->matr[i], '-') + 1);
			ob->arr[ft_atoi(cur->matr[i] + 1) - 1].f =
			ft_put_move_ant(&ob->arr[ft_atoi(cur->matr[i] + 1) - 1].x,
			&ob->arr[ft_atoi(cur->matr[i] + 1) - 1].y, arr,
			ob->arr[ft_atoi(cur->matr[i] + 1) - 1].f);
		}
			if (++j == ob->speed)
		{
			ft_draw_all(ob);
			j = -1;
		}
}

void	ft_draw(t_ob *ob)
{
	ft_draw_all(ob);
	key_hook(ob);
	mlx_loop(ob->mlx_ptr);
}
