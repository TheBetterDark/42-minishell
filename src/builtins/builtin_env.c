/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/02/11 12:41:40 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	builtin_env(t_data *data);

/*
* @brief Print the environment variables
*
* @param data The data structure
*/

void	builtin_env(t_data *data)
{
	char	**tmp;

	tmp = data->env;
	signal(SIGPIPE, SIG_IGN);
	while (*tmp)
	{
		ft_putendl_fd(*tmp, STDOUT_FILENO);
		tmp++;
	}
	signal(SIGPIPE, SIG_DFL);
}
