/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 15:22:12 by sbecker           #+#    #+#             */
/*   Updated: 2019/02/24 07:43:07 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move_and_spin_events(int keycode, t_picture *map)
{
	if (keycode == 0)
		map->center_x += 20;
	if (keycode == 2)
		map->center_x -= 20;
	if (keycode == 1)
		map->center_y -= 20;
	if (keycode == 13)
		map->center_y += 20;
	if (keycode == 12)
		map->angle_z -= 0.05;
	if (keycode == 14)
		map->angle_z += 0.05;
	if (keycode == 15)
		map->spin_z = (map->spin_z == 1 ? 0 : 1);
	if (keycode == 17)
		map->spin_x = (map->spin_x == 0 ? 1 : 0);
}

int		keyboard_event(int keycode, t_picture *map)
{
	if (keycode <= 17)
		move_and_spin_events(keycode, map);
	if (keycode == 31 && map->optimize_flag == 0)
		map->optimize_flag = 1;
	else if (keycode == 31)
		map->optimize_flag = 0;
	if (keycode == 256)
		map->control_flag = 1;
	if (keycode == 37 && map->lines_flag == 0)
		map->lines_flag = 1;
	else if (keycode == 37 && map->lines_flag == 1)
		map->lines_flag = 2;
	else if (keycode == 37)
		map->lines_flag = 0;
	if (keycode == 53)
		exit(0);
	if (keycode == 38 && map->wiggle == 0)
		map->wiggle = 250;
	else if (keycode == 38)
		map->wiggle = 0;
	return (0);
}

int		key_release(int keycode, t_picture *map)
{
	if (keycode == 256)
		map->control_flag = 0;
	return (0);
}

int		exit_event(void *param)
{
	param = 0;
	exit(0);
}
