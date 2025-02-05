/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:15:07 by muabdi            #+#    #+#             */
/*   Updated: 2025/01/28 11:07:42 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

/*
* @brief Cleanup the job list
*
* @param job The job list
*/
static void	cleanup_job(t_cmd *job)
{
	t_cmd	*tmp;

	while (job)
	{
		tmp = job;
		job = job->next;
		ft_free_str_arr(&tmp->cmdv);
		clear_out_list(&tmp->outs);
		clear_in_list(&tmp->ins);
		free(tmp);
		tmp = NULL;
	}
}

static void	cleanup_fds(t_data *data)
{
	if (data->save_stdin != -1)
		close(data->save_stdin);
	data->save_stdin = -1;
	if (data->save_stdout != -1)
		close(data->save_stdout);
	data->save_stdout = -1;
	if (data->r_input_fd != -1)
		close(data->r_input_fd);
	if (data->r_output_fd != -1)
		close(data->r_output_fd);
	data->r_input_fd = -1;
	data->r_output_fd = -1;
}

static void	reset_minishell_data_values(t_data *data)
{
	data->first_cmd = true;
	data->cmd_ct = 0;
	data->pipe_ct = -1;
	data->heredoc_ct = 0;
}

/*
* @brief Cleanup the minishell
*
* @param data The data struct
*/
void	cleanup_minishell(t_data *data)
{
	if (!data)
		return ;
	if (data->input)
	{
		free(data->input);
		data->input = (char *) NULL;
	}
	if (data->toks)
		tok_lstclear(&data->toks);
	if (data->job)
	{
		unlink_heredocs(data);
		cleanup_job(data->job);
		data->job = NULL;
	}
	cleanup_fds(data);
	if (data->pipe_fds)
	{
		free_pipes(data, data->pipe_ct);
		free(data->pipe_fds);
		data->pipe_fds = NULL;
	}
	reset_minishell_data_values(data);
}
