/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/11/04 17:25:01 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cmd.h"

static void	print_warning(char *eof)
{
	printf("minishell: warning: here-document");
	printf(" delimited by end-of-file (wanted `%s')\n", eof);
}

static void	output_heredoc(t_hdc hdc, char *buf)
{
	int	i;

	i = 0;
	while (buf[i] != '\0')
		write(hdc.pipe[1], &buf[i++], 1);
	free(buf);
	write(1, "> ", 2);
}

static void	heredoc_process(t_mini *m, t_hdc hdc)
{
	char	*buf;
	int		size;

	signal(SIGINT, handle_sigint_hdc);
	size = ft_strlen(hdc.eof);
	buf = get_next_line(0);
	while (buf)
	{
		write(1, "> ", 2);
		if (ft_strncmp(buf, hdc.eof, size) == 0 && buf[size] == '\n')
			break ;
		if (get_env_str(m, &buf))
		{
			m->exit_status = 1;
			return ;
		}
		output_heredoc(hdc, buf);
		buf = get_next_line(0);
	}
	if (!buf)
		print_warning(hdc.eof);
	close(hdc.pipe[1]);
	exit(0);
}

static bool	wait_for_status(int *status)
{
	wait(status);
	if (WIFEXITED(*status))
	{
		*status = WEXITSTATUS(*status);
		return (*status);
	}
	else if (WIFSIGNALED(*status))
	{
		*status = WTERMSIG(*status) + 128;
		return (1);
	}
	return (1);
}

bool	is_heredoc(t_mini *m)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	while (i < m->job_size)
	{
		j = 0;
		while (j < m->cmd[i].hdc_size)
		{
			if (pipe(m->cmd[i].hdc[j].pipe) == -1)
				return (1);
			if (fork() == 0)
				heredoc_process(m, m->cmd[i].hdc[j]);
			close(m->cmd[i].hdc[j].pipe[1]);
			if (wait_for_status(&status))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
