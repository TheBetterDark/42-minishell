/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_search_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 21:10:31 by muabdi            #+#    #+#             */
/*   Updated: 2025/01/13 12:32:29 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Checks if the command is accessible
*
* @param target_path The path to the command
*
* @return True if the command is accessible, false otherwise
*/
static bool	check_access(char *target_path)
{
	if (access(target_path, X_OK) == -1)
	{
		perror("access");
		return (false);
	}
	return (true);
}

/*
* @brief Joins the path and the command
*
* @param path The path to the command
* @param cmd The command to search for
*
* @return The joined path and command
*/
static char	*join_path_and_cmd(char *path, char *cmd)
{
	char	*tmp_path;
	char	*target_path;

	tmp_path = ft_strjoin(path, "/");
	if (!tmp_path)
		return (NULL);
	target_path = ft_strjoin(tmp_path, cmd);
	if ((void **)&tmp_path && *(void **)&tmp_path)
	{
		free(*(void **)&tmp_path);
		*(void **)&tmp_path = NULL;
	}
	if (!target_path)
		return (NULL);
	return (target_path);
}

/*
* @brief Checks if the entry is the command we are looking for
*
* @param entry The entry to check
* @param path The path to the entry
* @param cmd The command to search for
*
* @return The path to the command if it is found
*/
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

/*
* @brief Searches for the command in the paths
*
* @param path The path to search in
* @param cmd The command to search for
*
* @return The path to the command if it is found
*/
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
	if (dir)
		closedir(dir);
	return (NULL);
}
