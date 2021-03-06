/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 00:34:11 by sbednar           #+#    #+#             */
/*   Updated: 2019/08/19 03:55:31 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

int	jtoc_write_object(t_jnode *n, const int fd, const char arr)
{
	if (n->name && !arr)
	{
		write(fd, "\"", 1);
		write(fd, n->name, ft_strlen(n->name));
		write(fd, "\":", 2);
	}
	write(fd, "{", 1);
	jtoc_write_children(n, fd, 0);
	write(fd, "}", 1);
	if (n->right)
		write(fd, ",", 1);
	return (FUNCTION_SUCCESS);
}

int	jtoc_write_array(t_jnode *n, const int fd, const char arr)
{
	if (n->name && !arr)
	{
		write(fd, "\"", 1);
		write(fd, n->name, ft_strlen(n->name));
		write(fd, "\":", 2);
	}
	write(fd, "[", 1);
	jtoc_write_children(n, fd, 1);
	write(fd, "]", 1);
	if (n->right)
		write(fd, ",", 1);
	return (FUNCTION_SUCCESS);
}

int	jtoc_write_node(t_jnode *n, const int fd, const char arr)
{
	if ((n->type == none && jtoc_write_none(n, fd, arr)) ||
		(n->type == integer && jtoc_write_integer(n, fd, arr)) ||
		(n->type == fractional && jtoc_write_fractional(n, fd, arr)) ||
		(n->type == string && jtoc_write_string(n, fd, arr)) ||
		(n->type == array && jtoc_write_array(n, fd, arr)) ||
		(n->type == object && jtoc_write_object(n, fd, arr)))
		return (FUNCTION_FAILURE);
	return (FUNCTION_SUCCESS);
}

int	jtoc_write_children(t_jnode *n, const int fd, const char arr)
{
	t_jnode	*c;

	c = n->down;
	while (c)
	{
		if (jtoc_write_node(c, fd, arr))
			return (FUNCTION_FAILURE);
		c = c->right;
	}
	return (FUNCTION_SUCCESS);
}

int	jtoc_write(t_jnode *n, const char *str)
{
	int		fd;

	if ((fd = open(str, O_WRONLY | O_CREAT | O_TRUNC)) <= 0)
		return (FUNCTION_FAILURE);
	write(fd, "{", 1);
	if (jtoc_write_children(n, fd, 0))
	{
		close(fd);
		remove(str);
		return (FUNCTION_FAILURE);
	}
	write(fd, "}", 1);
	close(fd);
	return (FUNCTION_SUCCESS);
}
