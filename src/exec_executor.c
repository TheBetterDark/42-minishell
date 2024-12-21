/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/21 21:17:22 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	close_pipe_ends(t_data *d)
{
	if (d->input_fd != 0)
		close(d->input_fd);
	if (d->output_fd != 1)
		close(d->output_fd);
}

void	direct_pipe_input(t_data *d)
{
	close_pipe_ends(d);
	d->input_fd = d->pipefd[0];
	unlink("hd2sh9fd8F32");
}

static bool	is_builtin_command(const char *command)
{
	const char	*builtins[] = {
		"export", "unset", "cd"};
	int			i;

	i = 0;
	while (i < 3)
	{
		if (strcmp(command, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	executor(t_data *d)
{
	t_cmd	*cur;
	int		save_stdout;
	int		save_stdin;

	cur = d->job;
	save_stdout = dup(1);
	save_stdin = dup(0);
	if (cur->next == NULL && is_builtin_command(cur->cmdv[0]))
	{
		file_redirections(d, cur);
		execute_parent_process(d, cur);
		direct_pipe_input(d);
	}
	else
	{
		while (cur)
		{
			file_redirections(d, cur);
			fork_child_process(d, cur);
			direct_pipe_input(d);
			cur = cur->next;
		}
	}
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
	if (d->input_fd != 0)
		close(d->input_fd);
}
