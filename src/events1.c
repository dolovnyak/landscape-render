/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 15:22:12 by sbecker           #+#    #+#             */
/*   Updated: 2019/02/25 23:48:43 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mouse_event(int button, int x, int y, t_picture *map)
{
	if (button == 4 && map->control_flag == 1)
		map->up_height += 0.5;
	else if (button == 4)
		map->zoom += 1;
	if (button == 5 && map->control_flag == 1)
		map->up_height -= 0.5;
	else if (button == 5 && map->zoom > 1)
		map->zoom -= 1;
	if (button == 1 && map->button_flag == 0)
	{
		map->button_flag = 1;
		map->mouse_x = x;
		map->mouse_y = y;
	}
	return (0);
}

int		mouse_release(int button, int x, int y, t_picture *map)
{
	if (button == 1)
		map->button_flag = 0;
	x = 0;
	y = 0;
	return (0);
}

int		mouse_move(int x, int y, t_picture *map)
{
	if (map->button_flag == 1)
	{
		if (x < map->mouse_x)
		{
			map->angle_z += 0.05;
			map->mouse_x = x;
		}
		else if (x > map->mouse_x)
		{
			map->angle_z -= 0.05;
			map->mouse_x = x;
		}
		if (y < map->mouse_y && map->angle_x >= 0)
		{
			map->angle_x -= 0.02;
			map->mouse_y = y;
		}
		else if (y > map->mouse_y && map->angle_x <= 3.14159)
		{
			map->angle_x += 0.02;
			map->mouse_y = y;
		}
	}
	return (0);
}
