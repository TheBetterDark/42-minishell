/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path_to_cmdv0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:36:23 by smoore            #+#    #+#             */
/*   Updated: 2025/02/19 19:52:10 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static char	**get_paths(t_data *data);
static bool	try_find_target_path(char ***paths, char **cmdv0,
				char *saved_cmdv0);
char		*add_path_cmdv0(char **cmdv0, t_data *data);

static char	**get_paths(t_data *data)
{
	char	*path_str;
	char	**paths;

	path_str = ft_str_arr_has((const char **)data->env, "PATH");
	if (!path_str)
		return (NULL);
	path_str = ft_strchr(path_str, '=') + 1;
	if (!path_str)
		return (NULL);
	paths = ft_split(path_str, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static bool	try_find_target_path(char ***paths, char **cmdv0, char *saved_cmdv0)
{
	char	**paths_ptr;
	char	*target;

	paths_ptr = *paths;
	while (*paths_ptr)
	{
		target = search_paths(*paths_ptr, saved_cmdv0);
		if (target)
		{
			*cmdv0 = target;
			ft_str_arr_free(paths);
			free(saved_cmdv0);
			return (true);
		}
		paths_ptr++;
	}
	return (false);
}

char	*add_path_cmdv0(char **cmdv0, t_data *data)
{
	char	**paths;
	char	*saved_cmdv0;

	if (!(*cmdv0))
		return (NULL);
	saved_cmdv0 = ft_strdup(*cmdv0);
	if (!saved_cmdv0)
		return (NULL);
	if (data->env)
		paths = get_paths(data);
	else
		paths = NULL;
	if (!paths)
	{
		*cmdv0 = saved_cmdv0;
		return (saved_cmdv0);
	}
	*cmdv0 = NULL;
	if (try_find_target_path(&paths, cmdv0, saved_cmdv0))
		return (*cmdv0);
	ft_str_arr_free(&paths);
	*cmdv0 = saved_cmdv0;
	return (*cmdv0);
}
