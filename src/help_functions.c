/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:04:18 by sbecker           #+#    #+#             */
/*   Updated: 2019/02/24 14:57:30 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	jtoc_exit_with_error(const char *error)
{
	printf("%s\n", error);
	exit(0);
}

static void	jtoc_map_setup(t_picture *map, const char *path)
{
	t_jnode *root;
	t_jnode *tmp;

	if (!(root = jtoc_read(path)))
		jtoc_exit_with_error("PATH ERROR");
	if (!(tmp = jtoc_node_get_by_path(root, "window_width")) || tmp->type != integer)
		jtoc_exit_with_error("WINDOW_WIDTH ERROR");
	map->s_width = jtoc_get_int(tmp);
	if (!(tmp = jtoc_node_get_by_path(root, "window_height")) || tmp->type != integer)
		jtoc_exit_with_error("WINDOW_HEIGHT ERROR");
	map->s_height = jtoc_get_int(tmp);
	jtoc_node_clear(root);
}

void		initialization(t_picture *map)
{
	jtoc_map_setup(map, CONFIG_PATH);
	map->angle_z = 0.5;
	map->angle_x = 2.1;
	map->zoom = 10;
	map->center_x = map->s_width / 2;
	map->center_y = map->s_height / 2;
	map->button_flag = 0;
	map->spin_z = 1;
	map->spin_x = 0;
	map->size_matrix = map->size_x * map->size_y;
	map->lines_flag = 0;
	map->arr = (t_arr*)malloc(sizeof(t_arr) * map->size_matrix);
	map->wiggle = 0;
	map->up_height = 1;
	map->control_flag = 0;
	map->optimize_flag = 1;
}

void			check_angle_flag(t_picture *map)
{
	if (map->button_flag == 0 && map->spin_z == 1)
		map->angle_z -= 0.01;
	if (map->button_flag == 0 && map->spin_x == 1)
		map->angle_x += 0.01;
}

void		ft_ucswap(unsigned char *a, unsigned char *b)
{
	unsigned char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
