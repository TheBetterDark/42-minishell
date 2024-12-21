/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_search_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:10:31 by muabdi            #+#    #+#             */
/*   Updated: 2024/12/21 21:41:27 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static bool	check_access(char *target_path)
{
	if (access(target_path, X_OK) == -1)
	{
		perror("access");
		return (false);
	}
	return (true);
}

static char	*join_path_and_cmd(char *path, char *cmd)
{
	char	*tmp_path;
	char	*target_path;

	tmp_path = ft_strjoin(path, "/");
	target_path = ft_strjoin(tmp_path, cmd);
	free(tmp_path);
	if (!target_path)
		return (NULL);
	return (target_path);
}

static char	*check_entry(char *entry, char *path, char *cmd)
{
	char	*target_path;

	if (strcmp(entry, cmd) == 0)
	{
		target_path = join_path_and_cmd(path, cmd);
		if (!target_path)
			return (NULL);
		if (check_access(target_path))
			return (target_path);
	}
	return (NULL);
}

char	*search_paths(char *path, char *cmd)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*target_path;

	dir = opendir(path);
	if (dir)
	{
		while (true)
		{
			entry = readdir(dir);
			if (!entry)
				break ;
			target_path = check_entry(entry->d_name, path, cmd);
			if (target_path)
			{
				closedir(dir);
				return (target_path);
			}
		}
	}
	closedir(dir);
	return (NULL);
}
