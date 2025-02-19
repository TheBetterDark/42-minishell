/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:52:56 by smoore            #+#    #+#             */
/*   Updated: 2025/02/19 17:23:13 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static void	free_minishell_util(t_data *data);
void		free_minishell(t_data *data);
t_data		*initialize_minishell(void);

static void	free_minishell_util(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->toks)
		tok_lstclear(&data->toks);
	if (data->cmds && data->pipe_ct)
		free_pipes(data, data->pipe_ct);
	if (data->cmds)
		cmd_lstclear(&data->cmds);
	if (data->read_fd != -1)
	{
		close(data->read_fd);
		data->read_fd = -1;
	}
	if (data->write_fd != -1)
	{
		close(data->write_fd);
		data->write_fd = -1;
	}
}

void	free_minishell(t_data *data)
{
	if (data)
	{
		free_minishell_util(data);
		data->cmd_ct = 0;
		data->pipe_ct = 0;
		data->heredoc_ct = 0;
		data->token_syntax_error = false;
		data->input_mode = false;
		data->prompt_cont_error = false;
	}
}

t_data	*initialize_minishell(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	modify_sigquit(NORMAL_SIGNAL);
	init_termios(data);
	data->input = NULL;
	data->toks = NULL;
	data->cmds = NULL;
	data->cmd_ct = 0;
	data->pipe_ct = 0;
	data->pipe_fd = NULL;
	data->heredoc_ct = 0;
	data->env = ft_str_arr_dup((const char **)__environ);
	data->read_fd = -1;
	data->write_fd = -1;
	data->pwd = getcwd(NULL, 0);
	data->exit_stat = 0;
	data->token_syntax_error = false;
	data->input_mode = false;
	data->prompt_cont_error = false;
	return (data);
}
