/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:04:18 by sbecker           #+#    #+#             */
/*   Updated: 2019/02/24 00:27:11 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		check_point(int x, int y, t_picture *map)
{
	if (x >= 0 && x < map->s_width && y >= 0 && y < map->s_height)
		return (1);
	return (0);
}

int		check_line(t_arr p1, t_arr p2, t_picture *map, int flag)
{
	if (flag == 0)
	{
		if ((p1.x < 0 && p2.x < 0) || (p1.y < 0 && p2.y < 0) ||
				(p1.x >= map->s_width && p2.x >= map->s_width) ||
				(p1.y >= map->s_height && p2.y >= map->s_height))
			return (1);
	}
	else if (flag == 1)
	{
		if (check_point(p1.x, p1.y, map) && check_point(p2.x, p2.y, map))
			return (1);
	}
	else
	{
		if (check_point(p1.x, p1.y, map) || check_point(p2.x, p2.y, map))
			return (1);
	}
	return (0);
}

int		calc_intersection(t_arr p1, t_arr p2, t_picture *map, int flag)
{
	double	fp[4];

	fp[0] = (double)p1.x;
	fp[1] = (double)p1.y;
	fp[2] = (double)p2.x;
	fp[3] = (double)p2.y;
	if (flag == 0)
		return (-(fp[0] * fp[3] - fp[1] * fp[2]) / (fp[1] - fp[3]));
	else if (flag == 1)
		return ((-(fp[0] * fp[3] - fp[1] * fp[2]) * (map->s_width - 1) +
				(fp[0] - fp[2]) * (map->s_height - 1) * (map->s_width - 1)) /
				((fp[1] - fp[3]) * (map->s_width - 1)));
	else if (flag == 2)
		return ((fp[0] * fp[3] - fp[1] * fp[2]) / (fp[0] - fp[2]));
	else
		return ((-(fp[0] * fp[3] - fp[1] * fp[2]) * (map->s_height - 1) -
				(fp[1] - fp[3]) * (map->s_width - 1) * (map->s_height - 1)) /
				-((fp[0] - fp[2]) * (map->s_height - 1)));
}

t_arr	find_conflux(t_arr p1, t_arr p2, t_picture *map, int flag)
{
	t_arr	p;

	if (flag == 0)
	{
		p.x = calc_intersection(p1, p2, map, 0);
		p.y = 0;
	}
	else if (flag == 1)
	{
		p.x = calc_intersection(p1, p2, map, 1);
		p.y = map->s_height - 1;
	}
	else if (flag == 2)
	{
		p.y = calc_intersection(p1, p2, map, 2);
		p.x = 0;
	}
	else
	{
		p.x = map->s_width - 1;
		p.y = calc_intersection(p1, p2, map, 3);
	}
	p.check = (check_point(p.x, p.y, map) ? 1 : 0);
	return (p);
}
