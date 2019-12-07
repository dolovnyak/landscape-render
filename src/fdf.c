/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_another_way.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 15:55:17 by sbecker           #+#    #+#             */
/*   Updated: 2019/05/08 02:56:10 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_with_lines(t_picture *map, t_arr *arr)
{
	register int	i;
	register int	k;
	register int	size_x;

	i = -1;
	k = -1;
	size_x = map->size_x;
	while (++k < map->size_y - 1)
	{
		while (++i < size_x - 1)
		{
			try_draw(arr[i], arr[i + 1], map);
			try_draw(arr[i], arr[i + map->size_x], map);
		}
		size_x += map->size_x;
	}
	while (++i < size_x - 1)
		try_draw(arr[i], arr[i + 1], map);
	k = -1;
	i = map->size_x - 1;
	while (++k < map->size_y - 1)
	{
		try_draw(arr[i], arr[i + map->size_x], map);
		i += map->size_x;
	}
}

void	draw_without_lines(t_picture *map, t_arr *arr)
{
	register int	i;
	int				*img;

	img = (int*)map->img_data;
	i = -1;
	while (++i < map->size_matrix)
		if ((arr[i].x >= 0 && arr[i].x < map->s_width) &&
			(arr[i].y >= 0 && arr[i].y < map->s_height))
			img[arr[i].x + map->size_line / 4 * arr[i].y] = 120000;
}

void	get_rotation(t_picture *map, int i)
{
	float			tmp_x;
	float			tmp_y;
	float			tmp_z;

	tmp_x = map->zoom * (map->matrix + i)->x;
	tmp_y = map->zoom * (map->matrix + i)->y;
	tmp_z = map->zoom * (map->matrix + i)->height * map->up_height;
	(map->arr[i]).x = map->center_x + tmp_x * cos(map->angle_z) -
		tmp_y * sin(map->angle_z);
	(map->arr[i]).y = tmp_y * cos(map->angle_z) +
		(tmp_x + map->wiggle) * sin(map->angle_z);
	(map->arr[i]).y = map->center_y -
		(map->arr[i]).y * cos(map->angle_x) - tmp_z * sin(map->angle_x);
	map->arr[i].color = (map->matrix + i)->color;
}

int		refresh(t_picture *map)
{
	register int	i;

	ft_bzero((void*)map->img_data, map->size_line * map->s_height);
	mlx_put_image_to_window(map->mlx, map->win, map->img_ptr, 0, 0);
	check_angle_flag(map);
	i = -1;
	while (++i < map->size_matrix)
		get_rotation(map, i);
	if (map->lines_flag == 0)
		draw_without_lines(map, map->arr);
	else
		draw_with_lines(map, map->arr);
	mlx_put_image_to_window(map->mlx, map->win, map->img_ptr, 0, 0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_matrix		*arr;
	t_picture		map;

	if (argc != 2 || !(argc = open(argv[1], O_RDONLY)) || argc < 0)
		return (0);
	input(argc, &arr, &map);
	map.matrix = arr;
	initialization(&map);
	map.mlx = mlx_init();
	map.win = mlx_new_window(map.mlx, map.s_width, map.s_height, "FDF");
	map.img_ptr = mlx_new_image(map.mlx, map.s_width, map.s_height);
	map.img_data = mlx_get_data_addr(map.img_ptr, &map.bpp,
			&map.size_line, &map.endian);
	mlx_hook(map.win, 2, 0, &keyboard_event, &map);
	mlx_hook(map.win, 4, 0, &mouse_event, &map);
	mlx_hook(map.win, 5, 0, &mouse_release, &map);
	mlx_hook(map.win, 3, 0, &key_release, &map);
	mlx_hook(map.win, 6, 0, &mouse_move, &map);
	mlx_hook(map.win, 17, 0, &exit_event, (void*)0);
	mlx_loop_hook(map.mlx, &refresh, &map);
	mlx_loop(map.mlx);
	exit(0);
}
