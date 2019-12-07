/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:10:35 by sbecker           #+#    #+#             */
/*   Updated: 2019/02/25 23:47:30 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_intersection_and_draw(t_arr *intersection, t_picture *map)
{
	int		i;
	int		flag;
	t_arr	p1;
	t_arr	p2;

	flag = 0;
	i = -1;
	while (++i < 4)
		if (intersection[i].check == 1 &&
				check_point(intersection[i].x, intersection[i].y, map))
		{
			if (flag == 0)
			{
				p1 = intersection[i];
				flag++;
			}
			else
			{
				p2 = intersection[i];
				flag++;
			}
		}
	if (flag == 2)
		draw_line(p1, p2, map, 120000);
}

void	try_find_intersection_and_draw(t_arr p1, t_arr p2, t_picture *map)
{
	t_arr	*intersection;

	intersection = (t_arr*)malloc(sizeof(t_arr) * 4);
	if (p1.y - p2.y >= -1 && p1.y - p2.y <= 1)
	{
		intersection[1] = find_conflux(p1, p2, map, 0);
		intersection[3] = find_conflux(p1, p2, map, 1);
	}
	if (p1.x - p2.x >= -1 && p1.x - p2.x <= 1)
	{
		intersection[0] = find_conflux(p1, p2, map, 2);
		intersection[2] = find_conflux(p1, p2, map, 3);
	}
	else
	{
		intersection[1] = find_conflux(p1, p2, map, 0);
		intersection[3] = find_conflux(p1, p2, map, 1);
		intersection[0] = find_conflux(p1, p2, map, 2);
		intersection[2] = find_conflux(p1, p2, map, 3);
	}
	check_intersection_and_draw(intersection, map);
	free(intersection);
}

void	intersection_with_one_point(t_arr p, t_arr tmp_p, t_picture *map)
{
	t_arr	*intersection;

	intersection = (t_arr*)malloc(sizeof(t_arr) * 2);
	intersection[0].check = 0;
	if (tmp_p.x < 0)
		intersection[0] = find_conflux(p, tmp_p, map, 2);
	else if (tmp_p.x >= map->s_width)
		intersection[0] = find_conflux(p, tmp_p, map, 3);
	if (tmp_p.y < 0)
		intersection[1] = find_conflux(p, tmp_p, map, 0);
	else if (tmp_p.y >= map->s_height)
		intersection[1] = find_conflux(p, tmp_p, map, 1);
	if (intersection[0].check == 1)
		draw_line(p, intersection[0], map, 120000);
	else if (intersection[1].check == 1)
		draw_line(p, intersection[1], map, 120000);
	free(intersection);
}

void	try_draw(t_arr p1, t_arr p2, t_picture *map)
{
	if ((check_line(p1, p2, map, 0)))
		return ;
	if ((check_line(p1, p2, map, 1)))
	{
		if (map->lines_flag == 1)
			if (map->optimize_flag == 1)
				draw_line(p1, p2, map, 120000);
			else
				draw_line(p1, p2, map, 1020000);
		else
			wu_line(p1, p2, map, 1);
	}
	else if (map->lines_flag == 2)
		wu_line(p1, p2, map, 0);
	else if (map->optimize_flag == 0)
		draw_line(p1, p2, map, 1020000);
	else if ((check_line(p1, p2, map, 2)))
	{
		if (check_point(p1.x, p1.y, map))
			intersection_with_one_point(p1, p2, map);
		else
			intersection_with_one_point(p2, p1, map);
	}
	else
		try_find_intersection_and_draw(p1, p2, map);
}
