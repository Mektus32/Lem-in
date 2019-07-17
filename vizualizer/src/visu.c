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

void	ft_init_arr(t_ob *ob)
{
	int		i;
	int		x;
	int		y;

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
	ob->speed = 5;
	ob->cur = ob->turn;
	ob->stop = 0;
	ft_draw_all(ob);
}

int		main(void)
{
	t_ob	*ob;
	int		width;
	int		height;

	width = WIDTH;
	height = HEIGHT;
	ob = ft_memalloc(sizeof(t_ob));
	ob->fd = 0;
	ob->mlx_ptr = mlx_init();
	ob->win_ptr = mlx_new_window(ob->mlx_ptr, WIDTH, HEIGHT, "Best Lem-in");
	ob->image = (t_image*)malloc(sizeof(t_image));
	ob->image->img_background = mlx_xpm_file_to_image(ob->mlx_ptr, BACKGROUND,
			&width, &height);
	ob->image->img_ant = mlx_xpm_file_to_image(ob->mlx_ptr, ANT,
			&width, &height);
	if (ft_read(ob))
		return (0);
	ft_init_arr(ob);
	ft_draw(ob);
	return (0);
}
