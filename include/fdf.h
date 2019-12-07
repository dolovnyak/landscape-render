/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 21:07:31 by sbecker           #+#    #+#             */
/*   Updated: 2019/12/07 20:18:03 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"

typedef struct		s_arr_struct
{
	int				height;
	int				color;
	float			x;
	float			y;
}					t_matrix;

typedef struct		s_new_arr
{
	int				x;
	int				y;
	int				color;
	char			check;
}					t_arr;

typedef struct		s_bresenhem_line
{
	int				flag;
	int				dx;
	int				dy;
	int				error;
	int				ystep;
	int				color;
	int				*img;
}					t_draw_line;

typedef struct		s_wu_line
{
	int				flag;
	double			distance;
	double			y;
	int				x;
	double			color[3];
	double			gradient[3];
}					t_wu_line;

typedef struct		s_picture
{
	void			*img_ptr;
	void			*mlx;
	void			*win;
	char			*img_data;
	int				bpp;
	int				endian;
	int				size_line;
	float			angle_x;
	float			angle_z;
	t_matrix		*matrix;
	int				size_x;
	int				size_y;
	int				zoom;
	int				center_x;
	int				center_y;
	int				mouse_x;
	int				mouse_y;
	int				button_flag;
	int				lines_flag;
	int				control_flag;
	int				optimize_flag;
	int				spin_z;
	int				spin_x;
	int				size_matrix;
	int				s_width;
	int				s_height;
	t_arr			*arr;
	int				wiggle;
	float			up_height;
}					t_picture;

typedef struct		s_floats_for_find_intersetion
{
	float			x1;
	float			y1;
	float			x2;
	float			y2;
}					t_floats_coord;

void				input(int fd, t_matrix **arr, t_picture *map);
int					exit_event(void *param);
int					mouse_move(int x, int y, t_picture *map);
int					mouse_release(int button, int x, int y, t_picture *map);
int					keyboard_event(int keycode, t_picture *map);
int					mouse_event(int button, int x, int y, t_picture *map);
void				initialization(t_picture *map);
void				draw_line(t_arr p1, t_arr p2, t_picture *map, int color);
int					check_line(t_arr p1, t_arr p2, t_picture *map, int flag);
void				try_draw(t_arr p1, t_arr p2, t_picture *map);
void				check_angle_flag(t_picture *map);
void				ft_swap(int *a, int *b);
void				initialization_and_free_intersection(int ***arr, int flag);
int					check_point(int x, int y, t_picture *map);
t_arr				find_conflux(t_arr p1, t_arr p2, t_picture *map, int flag);
int					key_release(int keycode, t_picture *map);
void				wu_line(t_arr p1, t_arr p2, t_picture *map, int flag_draw);
void				ft_ucswap(unsigned char *a, unsigned char *b);

#endif
