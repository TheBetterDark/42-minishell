/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_tok_type_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/16 13:24:21 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

bool	is_fd(const char *tk);
bool	is_delim(const char *tk);
bool	is_filename(const char *tk);
char	**get_paths();
bool	is_cmd(const char *tk);
bool	is_valid_cmd(const char *tk);

bool is_fd(const char *tk) 
{
	int	i;
	int	fd;

	i = 0;
	if (!tk || tk[0] == '\0')
		return (false);
	while (tk[i])
	{
		if (!isdigit(tk[i]))
			return (false);
		i++;
	}
	fd = atoi(tk);
	return (fd >= 0);
}


bool is_delim(const char *tk) 
{
	if (tk == NULL)	
		return (false);
	return (
		strcmp(tk, ";") == 0 || strcmp(tk, "&&") == 0 ||
		strcmp(tk, "||") == 0 || strcmp(tk, "(") == 0 || strcmp(tk, ")") == 0
	);
}

bool is_filename(const char *tk) 
{
	struct stat	file_stat;

	if (!tk || tk[0] == '\0')
		return (false);
	if (stat(tk, &file_stat) == 0)
	{
		if (S_ISREG(file_stat.st_mode))
			return (true);
	}
	return (false);
}

char	**get_paths()
{
	char	*path_env;
	char	**paths;
	
	path_env = getenv("PATH");
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

bool	is_cmd(const char *tk)
{
	
}

bool	is_valid_cmd(const char *tk)
{
	char	*tmp_pathway;
	char	*target_pathway;
	char	**paths;

	paths = get_paths();
	while (*paths)
	{
		tmp_pathway = ft_strjoin(*paths, "/");
		target_pathway = ft_strjoin(tmp_pathway, tk);
		free(tmp_pathway);
		if (access(target_pathway, X_OK) == 0)
			return (true);
		free(target_pathway);
		paths++;
	}
	return (false);
}
