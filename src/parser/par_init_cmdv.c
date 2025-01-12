/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_init_cmdv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 14:23:46 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static bool	is_builtin_command(const char *command)
{
	int			i;
	const char	*builtins[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit"
	};

	i = 0;
	while (i < 7)
	{
		if (strcmp(command, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

static char	*add_path_to_cmdv0(t_data *d, char *cmd)
{
	char	**paths;
	char	**tmp;
	char	*target_path;
	char	*cmdv0;

	paths = get_paths(d);
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
			ft_free_str_arr(&paths);
			return (cmdv0);
		}
		tmp++;
	}
	ft_free_str_arr(&paths);
	return (NULL);
}

// TODO: Move command not found to excutor
static char	*handle_first_command(t_token *cur, t_data *d)
{
	char	*cmd;

	if (is_builtin_command(cur->cont))
		cmd = ft_strdup(cur->cont);
	else
	{
		if (access(cur->cont, F_OK | X_OK) == 0)
			cmd = ft_strdup(cur->cont);
		else
			cmd = add_path_to_cmdv0(d, cur->cont);
		if (!cmd)
		{
			ft_printf("%s: command not found\n", cur->cont);
			d->exit_stat = 127;
			return (NULL);
		}
	}
	return (cmd);
}

static char	*duplicate_command(t_token *cur, int is_first, t_data *d)
{
	char	*cmd;

	if (is_first == 0)
	{
		cmd = handle_first_command(cur, d);
	}
	else
	{
		if (cur->type == ARG && cur->cont[0] == '\"')
			cmd = dup_double_quotes(ft_strtrim(cur->cont, "\""), d);
		else if (cur->type == ARG && cur->cont[0] == '\'')
			cmd = ft_strdup(ft_strtrim(cur->cont, "\'"));
		else if (cur->type == EXIT_STAT)
			cmd = ft_itoa(d->exit_stat);
		else
			cmd = ft_strdup(cur->cont);
	}
	return (cmd);
}

char	**init_cmdv(t_token *cur, int size, t_data *d)
{
	char	**cmdv;
	int		i;

	cmdv = malloc(sizeof(char *) * (size + 1));
	if (!cmdv)
		return (NULL);
	i = 0;
	while (i < size && cur)
	{
		if ((cur->type == CMD || cur->type == ARG
				|| cur->type == EXIT_STAT) && cur->type != PIPE)
		{
			cmdv[i] = duplicate_command(cur, i, d);
			if (!cmdv[i])
			{
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
