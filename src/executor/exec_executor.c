/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/07 18:47:20 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static bool	is_builtin_command(const char *command)
{
	const char	*builtins[] = {
		"export", "unset", "cd", "echo", "pwd", "env"
	};
	int			i;

	i = 0;
	while (i < 6)
	{
		if (strcmp(command, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

static void	handle_builtin_command(t_data *d, t_cmd *cur)
{
	file_redirections(d, cur);
	execute_parent_process(d, cur);
	direct_pipe_input(d);
}

static void	execute_commands(t_data *d)
{
	t_cmd	*cur;

	cur = d->job;
	while (cur)
	{
		file_redirections(d, cur);
		fork_child_process(d, cur);
		direct_pipe_input(d);
		cur = cur->next;
	}
	cur = d->job;
	while (cur)
	{
		if (cur->pid != 0)
			catch_exit_status(cur->pid, d);
		cur = cur->next;
	}
}

static void	restore_file_descriptors(int save_stdout, int save_stdin)
{
	if (dup2(save_stdout, 1) == -1)
	{
		perror("dup2 save_stdout");
		exit(EXIT_FAILURE);
	}
	close(save_stdout);
	if (dup2(save_stdin, 0) == -1)
	{
		perror("dup2 save_stdin");
		exit(EXIT_FAILURE);
	}
	close(save_stdin);
}

void	executor(t_data *d)
{
	t_cmd	*cur;
	int		save_stdout;
	int		save_stdin;

	cur = d->job;
	save_stdout = dup(1);
	save_stdin = dup(0);
	if (!cur)
		return ;
	if (cur->next == NULL && is_builtin_command(cur->cmdv[0]))
		handle_builtin_command(d, cur);
	else
		execute_commands(d);
	restore_file_descriptors(save_stdout, save_stdin);
	if (d->input_fd != 0)
		close(d->input_fd);
}
