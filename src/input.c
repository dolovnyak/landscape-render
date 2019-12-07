/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 22:03:28 by sbecker           #+#    #+#             */
/*   Updated: 2019/02/26 02:17:45 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_str_space_plus_join_free(char *s, char const *s1)
{
	char	*check;
	char	*a;
	int		i;

	i = 0;
	check = s;
	a = (char*)malloc(ft_strlen(s) + ft_strlen(s1) + 2);
	if (a)
	{
		while (*s)
		{
			a[i++] = *s;
			s++;
		}
		a[i++] = ' ';
		while (*s1)
		{
			a[i++] = *s1;
			s1++;
		}
		a[i] = '\0';
	}
	free(check);
	return (a);
}

char	**create_tmp_arr_and_find_sizes(int fd, t_picture *map)
{
	char	*line;
	char	*all_lines;
	char	**tmp_arr;

	get_next_line(fd, &line);
	map->size_y = 1;
	map->size_x = ft_strwcnumber(line, ' ');
	all_lines = ft_strdup(line);
	free(line);
	while (get_next_line(fd, &line) == 1)
	{
		all_lines = ft_str_space_plus_join_free(all_lines, line);
		free(line);
		map->size_y++;
	}
	tmp_arr = ft_strsplit(all_lines, ' ');
	free(line);
	free(all_lines);
	return (tmp_arr);
}

void	get_color(t_matrix *arr, char *s)
{
	int		i;

	i = 0;
	while (s[i] != 'x' && s[i])
		i++;
	if (!s[i])
	{
		arr->color = 16777215;
		return ;
	}
	i++;
	arr->color = ft_atoi_base(&s[i], 16);
}

void	input(int fd, t_matrix **arr, t_picture *map)
{
	char	**tmp_arr;
	int		i;

	tmp_arr = create_tmp_arr_and_find_sizes(fd, map);
	*arr = (t_matrix*)malloc(sizeof(t_matrix) * (map->size_x * map->size_y));
	i = -1;
	while (tmp_arr[++i])
	{
		(*arr + i)->x = (float)(i % map->size_x) - (map->size_x - 1) / 2.0;
		(*arr + i)->y = (float)(i / map->size_x) - (map->size_y - 1) / 2.0;
		(*arr + i)->height = ft_atoi(tmp_arr[i]);
		get_color((*arr + i), tmp_arr[i]);
	}
	ft_dpclearnum(tmp_arr, map->size_x * map->size_y);
}
