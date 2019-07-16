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

void Brezenhem(int x0, int y0, int x1, int y1, t_ob *ob)
{
	int A, B;
	A = y1 - y0;
	B = x0 - x1;
	int signa, signb;
	if (A < 0) signa = -1;
	else signa = 1;
	if (B < 0) signb = -1;
	else signb = 1;
	int f = 0;
	mlx_pixel_put(ob->mlx_ptr, ob->win_ptr, x0, y0, 0xFFFFFF);
	int x = x0, y = y0;
	if ((abs(A) <= abs(B)))
	{
		do {
			f += A*signa;
			if (f > 0)
			{
				f -= B*signb;
				y += signa;
			}
			x -= signb;
			mlx_pixel_put(ob->mlx_ptr, ob->win_ptr, x, y, 0xFFFFFF);
		} while (x != x1 || y != y1);
	}
	else
	{
		do {
			f += B*signb;
			if (f > 0) {
				f -= A*signa;
				x -= signb;
			}
			y += signa;
			mlx_pixel_put(ob->mlx_ptr, ob->win_ptr, x, y, 0xFFFFFF);
		} while (x != x1 || y != y1);
	}
}

int		ft_put_move_ant(int *x0, int *y0, int x1, int y1, int f)
{
	int A, B, sign;
	A = y1 - *y0;
	B = *x0 - x1;
	if (abs(A) > abs(B)) sign = 1;
	else sign = -1;
	int signa, signb;
	if (A < 0) signa = -1;
	else signa = 1;
	if (B < 0) signb = -1;
	else signb = 1;
	if (sign == -1)
	{
		f += A*signa;
		if (f > 0)
		{
			f -= B*signb;
			*y0 += signa;
		}
		*x0 -= signb;
		return (f);
	}
	else
	{
		f += B*signb;
		if (f > 0) {
			f -= A*signa;
			*x0 -= signb;
		}
		*y0 += signa;
		return (f);
	}
}