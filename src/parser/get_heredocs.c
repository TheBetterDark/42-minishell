/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredocs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:37:18 by smoore            #+#    #+#             */
/*   Updated: 2025/02/07 14:42:41 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static bool	read_write(t_ins *ins, t_data *data);
static void	get_cur_heredoc(t_ins *ins, t_data *data);
void		get_heredocs(t_cmd **cmds, t_data *data);

static bool	read_write(t_ins *ins, t_data *data)
{
	char	*buf;
	char	*expand;

	ft_putstr_fd("> ", STDOUT_FILENO);
	buf = get_next_line(STDIN_FILENO);
	if (!buf)
		return (false);
	if (word_match(buf, ins->eof))
	{
		free(buf);
		return (close(ins->fd), false);
	}
	if (ins->eof_quoted == false)
	{
		expand = try_expand_dup(buf, data);
		free(buf);
		ft_putstr_fd(expand, ins->fd);
		free(expand);
	}
	else
	{
		ft_putstr_fd(buf, ins->fd);
		free(buf);
	}
	return (true);
}

static void	get_cur_heredoc(t_ins *ins, t_data *data)
{
	if (!ins->eof)
		return ;
	ins->fd = open(ins->read_fn, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ins->fd < 0)
	{
		perror("Failed to open heredoc");
		return ;
	}
	while (true)
	{
		if (read_write(ins, data) == false)
			break ;
	}
	close(ins->fd);
}

void	get_heredocs(t_cmd **cmds, t_data *data)
{
	t_cmd	*cmd_ptr;
	t_ins	*in_ptr;

	cmd_ptr = *cmds;
	g_signal = HEREDOC_MODE;
	while (cmd_ptr)
	{
		in_ptr = cmd_ptr->ins;
		while (in_ptr && g_signal != HEREDOC_SIGINT)
		{
			get_cur_heredoc(in_ptr, data);
			in_ptr = in_ptr->next;
		}
		cmd_ptr = cmd_ptr->next;
	}
	if (g_signal == HEREDOC_MODE)
		g_signal = NO_SIGNAL;
}
