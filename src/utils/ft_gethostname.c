/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gethostname.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:52:44 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/25 16:56:06 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	truncate_after_first_period(char *hostname);

int	ft_gethostname(char *hostname)
{
	int		fd;
	ssize_t	bytes_read;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening /etc/hostname");
		return (-1);
	}
	bytes_read = read(fd, hostname, HOST_NAME_MAX - 1);
	if (bytes_read == -1)
	{
		perror("Error reading /etc/hostname");
		close(fd);
		return (-1);
	}
	hostname[bytes_read] = '\0';
	truncate_after_first_period(hostname);
	close(fd);
	return (0);
}

static void	truncate_after_first_period(char *hostname)
{
	int	i;

	i = 0;
	while (hostname[i] != '\0')
	{
		if (hostname[i] == '.')
		{
			hostname[i] = '\0';
			break ;
		}
		i++;
	}
}
