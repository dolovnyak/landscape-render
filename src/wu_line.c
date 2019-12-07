/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:10:35 by sbecker           #+#    #+#             */
/*   Updated: 2019/02/25 23:48:05 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_point(t_wu_line *all, int y, double grad, t_picture *map)
{
	int		a;
	char	intensiv;
	int		x;

	x = all->x;
	if (all->flag)
		ft_swap(&x, &y);
	intensiv = 255 * grad;
	a = map->size_line * y + x * 4;
	map->img_data[a] = (unsigned char)all->color[2];
	map->img_data[a + 1] = (unsigned char)all->color[1];
	map->img_data[a + 2] = (unsigned char)all->color[0];
	map->img_data[a + 3] = intensiv;
}

void	check_and_draw_point(t_wu_line *all, int y, double grad, t_picture *map)
{
	int		a;
	char	intensiv;
	int		x;

	x = all->x;
	if (all->flag)
		ft_swap(&x, &y);
	if (!(check_point(x, y, map)))
		return ;
	intensiv = 255 * grad;
	a = map->size_line * y + x * 4;
	map->img_data[a] = (unsigned char)all->color[2];
	map->img_data[a + 1] = (unsigned char)all->color[1];
	map->img_data[a + 2] = (unsigned char)all->color[0];
	map->img_data[a + 3] = intensiv;
}

void	get_color_and_gradient(t_wu_line *all, t_arr *p1, t_arr *p2)
{
	all->distance = (double)(p2->y - p1->y) / (p2->x - p1->x);
	all->color[0] = *((unsigned char*)&p1->color + 2);
	all->color[1] = *((unsigned char*)&p1->color + 1);
	all->color[2] = *((unsigned char*)&p1->color + 0);
	all->gradient[0] = (double)(all->color[0] -
			(int)*((unsigned char*)&p2->color + 2)) / (p2->x - p1->x);
	all->gradient[1] = (double)(all->color[1] -
			(int)*((unsigned char*)&p2->color + 1)) / (p2->x - p1->x);
	all->gradient[2] = (double)(all->color[2] -
			(int)*((unsigned char*)&p2->color + 0)) / (p2->x - p1->x);
	all->x = p1->x;
	all->y = p1->y;
}

void	swap_and_new_grad(t_wu_line *all, t_arr *p1, t_arr *p2, int flag)
{
	if (flag == 0)
	{
		all->flag = 1;
		ft_swap(&p1->x, &p1->y);
		ft_swap(&p2->x, &p2->y);
	}
	else if (flag == 1)
	{
		ft_swap(&p1->x, &p2->x);
		ft_swap(&p1->y, &p2->y);
		ft_ucswap(((unsigned char*)&p1->color + 0),
				((unsigned char*)&p2->color + 0));
		ft_ucswap(((unsigned char*)&p1->color + 1),
				((unsigned char*)&p2->color + 1));
		ft_ucswap(((unsigned char*)&p1->color + 2),
				((unsigned char*)&p2->color + 2));
	}
	else
	{
		all->color[0] -= all->gradient[0];
		all->color[1] -= all->gradient[1];
		all->color[2] -= all->gradient[2];
	}
}

void	wu_line(t_arr p1, t_arr p2, t_picture *map, int flag_draw)
{
	t_wu_line	all;

	all.flag = 0;
	if (abs((p2.x - p1.x)) < abs((p2.y - p1.y)))
		swap_and_new_grad(&all, &p1, &p2, 0);
	if (p1.x > p2.x)
		swap_and_new_grad(&all, &p1, &p2, 1);
	get_color_and_gradient(&all, &p1, &p2);
	while (all.x < p2.x)
	{
		swap_and_new_grad(&all, &p1, &p2, 2);
		all.y += all.distance;
		all.x++;
		if (flag_draw == 1)
		{
			draw_point(&all, (int)all.y, all.y - (int)all.y, map);
			draw_point(&all, (int)all.y + 1, 1.0 - (all.y - (int)all.y), map);
		}
		else
		{
			check_and_draw_point(&all, (int)all.y, all.y - (int)all.y, map);
			check_and_draw_point(&all, (int)all.y + 1,
					1.0 - (all.y - (int)all.y), map);
		}
	}
}
