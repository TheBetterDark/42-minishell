/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 13:44:53 by smoore            #+#    #+#             */
/*   Updated: 2025/02/11 13:00:13 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	if (write(fd, s, len) == -1)
	{
		if (errno == EPIPE)
			exit(EXIT_FAILURE);
	}
	if (write(fd, "\n", 1) == -1)
	{
		if (errno == EPIPE)
			exit(EXIT_FAILURE);
	}
}
