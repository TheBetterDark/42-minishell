/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:50:18 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/25 16:55:47 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	replace_home_with_tilde(char *cwd, const char *home);

int	ft_getcwd(char *cwd)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("Error getting HOME environment variable\n",
			STDERR_FILENO);
		return (-1);
	}
	if (!getcwd(cwd, PATH_MAX))
	{
		perror("Error getting current working directory");
		return (-1);
	}
	if (home && ft_strstr(cwd, home) == cwd)
		replace_home_with_tilde(cwd, home);
	return (0);
}

static void	replace_home_with_tilde(char *cwd, const char *home)
{
	size_t	home_len;
	size_t	cwd_len;

	if (!home)
		return ;
	home_len = ft_strlen(home);
	cwd_len = ft_strlen(cwd);
	if (cwd_len > home_len)
	{
		cwd[0] = '~';
		ft_strlcpy(cwd + 1, cwd + home_len, PATH_MAX - 1);
	}
}
