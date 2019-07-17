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

//void	ft_draw_turn(t_ob *ob)
//{
//	t_turn	*turn;
////	int 	i;
//
//	turn = ob->turn;
//	while (turn)
//	{
//		mlx_clear_window(ob->mlx_ptr, ob->win_ptr);
//		mlx_put_image_to_window(ob->mlx_ptr, ob->win_ptr, ob->image->img_background,
//								0, 0);
//		ft_draw_rooms(ob);
//		ft_put_move_ant(100, 100, 2100, 1000, ob);
//		turn = turn->next;
//	}
//}
//
//void	ft_draw_rooms(t_ob *ob)
//{
//	t_room	*room;
//	t_neib	*neib;
//	int 	i;
//
//	room = ob->rooms;
//	while (room)
//	{
//		neib = room->next;
//		while (neib)
//		{
//			Brezenhem(room->x, room->y, ft_get_x_room(ob->rooms, neib->name),
//					ft_get_y_room(ob->rooms, neib->name), ob);
//			printf("{%s} [%d,%d] -> {%s} [%d,%d]\n", room->name, room->x, room->y, neib->name,
//					ft_get_x_room(room, neib->name), ft_get_y_room(room, neib->name));
//			neib = neib->next;
//		}
//		room = room->down;
//	}
//	i = 0;
//	room = ob->rooms;
//	while (room)
//	{
//		mlx_put_image_to_window(ob->mlx_ptr, ob->win_ptr, room->image,
//								room->x - 25, room->y - 25);
//		mlx_string_put(ob->mlx_ptr, ob->win_ptr, room->x - 5, room->y - 10, 0x000000, room->name);
//		i++;
//		printf("room[%s]-x[%d]-y[%d]\n", room->name, room->x, room->y);
//		room = room->down;
//	}
//}

void	ft_draw_lines(t_ob *ob)
{
	t_room	*room;
	t_neib	*neib;

	room = ob->rooms;
	while (room)
	{
		neib = room->next;
		while (neib)
		{
			Brezenhem(room->x, room->y, ft_get_x_room(ob->rooms, neib->name),
					ft_get_y_room(ob->rooms, neib->name), ob);
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
	{
		mlx_put_image_to_window(ob->mlx_ptr, ob->win_ptr, ob->image->img_ant,
							ob->arr[i].x - 25, ob->arr[i].y - 25);
		//printf("ant{%d} [%d,%d]\n", i, ob->arr[i].x, ob->arr[i].y);
	}
//	sleep(1);
}

void	ft_draw_turn(t_ob *ob)
{
	int 	i;
	t_turn	*cur;
	int static	j;

	cur = ob->cur;
	i = 0;
		while (cur && cur->matr[i])
		{
			if (ob->arr[ft_atoi(cur->matr[i] + 1) - 1].x !=
			ft_get_x_room(ob->rooms, ft_strchr(cur->matr[i], '-') + 1) ||
			ob->arr[ft_atoi(cur->matr[i] + 1) - 1].y != ft_get_y_room(ob->rooms,
					ft_strchr(cur->matr[i], '-') + 1))
			{
				ob->arr[ft_atoi(cur->matr[i] + 1) - 1].f = ft_put_move_ant(&ob->arr[ft_atoi(cur->matr[i] + 1) - 1].x, &ob->arr[ft_atoi(cur->matr[i] + 1) - 1].y, ft_get_x_room(ob->rooms, ft_strchr(cur->matr[i], '-') + 1), ft_get_y_room(ob->rooms, ft_strchr(cur->matr[i], '-') + 1), ob->arr[ft_atoi(cur->matr[i] + 1) - 1].f);
			}

			//ft_draw_all(ob);
			i++;
		}
		if (j == 5)
		{
			ft_draw_all(ob);
			j = 0;
		}
		j++;
}

void	ft_draw(t_ob *ob)
{
	int 	weidth;
	int 	height;

	weidth = WIDTH;
	height = HEIGHT;
	ob->image->img_background = mlx_xpm_file_to_image(ob->mlx_ptr, BACKGROUND,
	&weidth, &height);
	ob->image->img_ant = mlx_xpm_file_to_image(ob->mlx_ptr, ANT,
			&weidth, &height);
//	mlx_put_image_to_window(ob->mlx_ptr, ob->win_ptr, ob->image->img_background
//	,0 ,0);
	ob->cur = ob->turn;
	ft_draw_turn(ob);
	//printf("int draw ob->cur->[%p]\n", ob->cur);
	key_hook(ob);
	mlx_loop(ob->mlx_ptr);
}
