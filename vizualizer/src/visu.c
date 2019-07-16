/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 17:32:12 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/16 13:53:30 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"

void	ft_print_list(t_ob *ob)
{
	t_room	*room;
	t_neib	*neib;
//	t_turn	*turn;

	room = ob->rooms;
	while (room)
	{
		printf("room[%s, %d]->", room->name, room->cont);
		neib = room->next;
		while (neib)
		{
			printf("%s->", neib->name);
			neib = neib->next;
		}
		printf("\n");
		room = room->down;
	}
//	printf("\n\n");
//	turn = ob->turn;
//	while (turn)
//	{
//		printf("%s\n", turn->str);
//		turn = turn->next;
//	}
}

void	ft_init_arr(t_ob *ob)
{
	int 	i;
	int 	x;
	int 	y;

	if (!(ob->arr = ft_memalloc(sizeof(t_coor) * ob->ants)))
		return ;
	y = ft_get_y_room_cont(ob->rooms, 1);
	x = ft_get_x_room_cont(ob->rooms, 1);
	i = -1;
	while (++i < ob->ants)
	{
		ob->arr[i].x = x;
		ob->arr[i].y = y;
		ob->arr[i].f = 0;
	}
}

int 	main(void)
{
	t_ob *ob;

	ob = ft_memalloc(sizeof(t_ob));
	ob->fd = open("/Users/ojessi/Desktop/lem/vizualizer/out_put", O_RDONLY);
	ob->mlx_ptr = mlx_init();
	ob->win_ptr = mlx_new_window(ob->mlx_ptr, WIDTH, HEIGHT, "Best Lem-in");
	ob->image = (t_image *) malloc(sizeof(t_image));
	if (ft_read(ob))
		return (0);
	ft_init_arr(ob);
	ft_print_list(ob);
	ft_draw(ob);
	return (0);
}
