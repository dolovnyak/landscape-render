/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:10:35 by sbecker           #+#    #+#             */
/*   Updated: 2019/02/24 07:32:17 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_draw_line *all, t_arr p1, t_arr p2, t_picture *map)
{
	while (p1.x++ < p2.x)
	{
		all->img[map->s_width * ((all->flag) ? (p1.x) : (p1.y))
			+ ((all->flag) ? (p1.y) : (p1.x))] = all->color;
		all->error -= all->dy;
		if (all->error < 0)
		{
			p1.y += all->ystep;
			all->error += all->dx;
		}
	}
}

void	check_and_put_pixel(t_draw_line *all, t_arr p1,
		t_arr p2, t_picture *map)
{
	while (p1.x++ < p2.x)
	{
		if (check_point((all->flag ? p1.y : p1.x),
					(all->flag ? p1.x : p1.y), map))
			all->img[map->s_width * ((all->flag) ? (p1.x) : (p1.y))
				+ ((all->flag) ? (p1.y) : (p1.x))] = all->color;
		all->error -= all->dy;
		if (all->error < 0)
		{
			p1.y += all->ystep;
			all->error += all->dx;
		}
	}
}

void	draw_line(t_arr p1, t_arr p2, t_picture *map, int color)
{
	t_draw_line	all;

	all.img = (int*)map->img_data;
	all.color = color;
	all.flag = 0;
	if (abs((p2.x - p1.x)) < abs((p2.y - p1.y)))
	{
		all.flag = 1;
		ft_swap(&p1.x, &p1.y);
		ft_swap(&p2.x, &p2.y);
	}
	if (p1.x > p2.x)
	{
		ft_swap(&p1.x, &p2.x);
		ft_swap(&p1.y, &p2.y);
	}
	all.dx = p2.x - p1.x;
	all.dy = abs((p2.y - p1.y));
	all.error = all.dx / 2;
	all.ystep = (p1.y < p2.y) ? 1 : -1;
	p1.x--;
	if (map->optimize_flag == 1)
		put_pixel(&all, p1, p2, map);
	else
		check_and_put_pixel(&all, p1, p2, map);
}
