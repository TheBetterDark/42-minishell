/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_init_cmdv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/20 14:49:54 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static bool	is_builtin_command(const char *command);

char	*add_path_to_cmdv0(char *cmd)
{
	char	**paths;
	char	**tmp;
	char	*target_path;
	char	*cmdv0;

	paths = get_paths();
	if (!paths)
		return (NULL);
	tmp = paths;
	while (*tmp)
	{
		target_path = search_paths(*tmp, cmd);
		if (target_path)
		{
			cmdv0 = ft_strdup(target_path);
			free(target_path);
			ft_free_str_arr(paths);
			return (cmdv0);
		}
		tmp++;
	}
	ft_free_str_arr(paths);
	return (NULL);
}

char	**init_cmdv(t_token *cur, int size)
{
	char	**cmdv;
	int		i;

	cmdv = malloc(sizeof(char *) * (size + 1));
	if (!cmdv)
		return (NULL);
	i = 0;
	while (i < size && cur)
	{
		if (cur->type == CMD || cur->type == ARG)
		{
			if (i == 0)
			{
				if (is_builtin_command(cur->cont))
				{
					printf("IS_BUILTIN!!: %s\n", cur->cont);
					cmdv[0] = ft_strdup(cur->cont);
				}
				else
				{
					if (access(cur->cont, F_OK | X_OK) == 0)
						cmdv[0] = ft_strdup(cur->cont);
					else
						cmdv[0] = add_path_to_cmdv0(cur->cont);
					if (!cmdv[0])
					{
						ft_printf("%s: command not found\n", cur->cont);
						exit(EXIT_FAILURE);
					}
				}
			}
			else
				cmdv[i] = ft_strdup(cur->cont);
			if (!cmdv[i])
			{
				perror("Cmdv strdup Error");
				while (i > 0)
					free(cmdv[--i]);
				free(cmdv);
				return (NULL);
			}
			i++;
		}
		cur = cur->next;
	}
	cmdv[i] = NULL;
	return (cmdv);
}

static bool	is_builtin_command(const char *command)
{
	const char	*builtins[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit"
	};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (strcmp(command, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}
