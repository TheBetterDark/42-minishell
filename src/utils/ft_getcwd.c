/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:50:18 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/30 08:25:17 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	replace_home_with_tilde(char *cwd, const char *home);

/*
* @brief Get the current working directory
*
* @param cwd The buffer to store the current working directory
* @param is_tilde If true, replace the home directory with a tilde
* @return int 0 on success, -1 on error
*/
int	ft_getcwd(char *cwd, bool is_tilde)
{
	char	*home;

	if (!getcwd(cwd, PATH_MAX))
	{
		perror("Error getting current working directory");
		return (-1);
	}
	if (!is_tilde)
		return (0);
	home = getenv("HOME");
	if (!home)
	{
		ft_putstr_fd("Error getting HOME environment variable\n",
			STDERR_FILENO);
		return (-1);
	}
	if (home && ft_strstr(cwd, home) == cwd)
		replace_home_with_tilde(cwd, home);
	return (0);
}

/*
* @brief Replace the home directory with a tilde
*
* @param cwd The current working directory
* @param home The home directory
* @return void
*/
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
