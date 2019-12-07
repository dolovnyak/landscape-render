/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 20:43:10 by sbecker           #+#    #+#             */
/*   Updated: 2018/12/02 20:54:35 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strwlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != ' ' && s[i] != '\n' && s[i] != '\t' && s[i])
		i++;
	return (i);
}