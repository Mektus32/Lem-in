/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojessi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:02:28 by ojessi            #+#    #+#             */
/*   Updated: 2019/07/16 14:02:29 by ojessi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vizualizer.h"
#define ABS(Value) (Value < 0 ? -(Value) : Value)

void	ft_while_1(int arr[4], int fun[5], t_ob *ob)
{
	while (fun[2] != arr[2] || fun[3] != arr[3])
	{
		fun[4] += fun[0] * (fun[0] < 0 ? -1 : 1);
		if (fun[4] > 0)
		{
			fun[4] -= fun[1] * (fun[1] < 0 ? -1 : 1);
			fun[3] += fun[0] < 0 ? -1 : 1;
		}
		fun[2] -= fun[1] < 0 ? -1 : 1;
		mlx_pixel_put(ob->mlx_ptr, ob->win_ptr, fun[2], fun[3], 0xFFFFFF);
	}
}

void	ft_while_2(int arr[4], int fun[5], t_ob *ob)
{
	while (fun[2] != arr[2] || fun[3] != arr[3])
	{
		fun[4] += fun[1] * (fun[1] < 0 ? -1 : 1);
		if (fun[4] > 0) {
			fun[4] -= fun[0] * (fun[0] < 0 ? -1 : 1);
			fun[2] -= fun[1] < 0 ? -1 : 1;
		}
		fun[3] += fun[0] < 0 ? -1 : 1;
		mlx_pixel_put(ob->mlx_ptr, ob->win_ptr, fun[2], fun[3], 0xFFFFFF);
	}
}

void ft_draw_links(int arr[4], t_ob *ob)
{
	int 	fun[5];

	fun[0] = arr[3] - arr[1];
	fun[1] = arr[0] - arr[2];
	fun[2] = arr[0];
	fun[3] = arr[1];
	fun[4] = 0;
	mlx_pixel_put(ob->mlx_ptr, ob->win_ptr, arr[0], arr[1], 0xFFFFFF);
	if ((ABS(fun[0]) <= ABS(fun[1])))
		ft_while_1(arr, fun, ob);
	else
		ft_while_2(arr, fun, ob);
}

int		ft_put_move_ant(int *x0, int *y0, int arr[2], int f)
{
	int A, B;
	A = arr[1] - *y0;
	B = *x0 - arr[0];
	if (ABS(A) <= ABS(B))
	{
		f += A * (A < 0 ? -1 : 1);
		if (f > 0)
		{
			f -= B * (B < 0 ? -1 : 1);
			*y0 += A < 0 ? -1 : 1;
		}
		*x0 -= B < 0 ? -1 : 1;
		return (f);
	}
	else
	{
		f += B* (B < 0 ? -1 : 1);
		if (f > 0) {
			f -= A * (A < 0 ? -1 : 1);
			*x0 -= B < 0 ? -1 : 1;
		}
		*y0 += A < 0 ? -1 : 1;
		return (f);
	}
}