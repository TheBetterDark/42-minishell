/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:15:07 by muabdi            #+#    #+#             */
/*   Updated: 2025/01/15 13:03:06 by smoore           ###   ########.fr       */
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
		if (tmp->open_fn != NULL)
			free(tmp->open_fn);
		tmp->open_fn = NULL;
		if (tmp->append_fn != NULL)
			free(tmp->append_fn);
		tmp->append_fn = NULL;
		if (tmp->input_fn != NULL)
			free(tmp->input_fn);
		tmp->input_fn = NULL;
		free(tmp);
		tmp = NULL;
	}
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
		data->input = NULL;
	}
	if (data->toks)
		tok_lstclear(&data->toks);
	if (data->job)
	{
		cleanup_job(data->job);
		data->job = NULL;
	}
	if (data->save_stdin != -1)
		close(data->save_stdin);
	data->save_stdin = -1;
	if (data->save_stdout != -1)
		close(data->save_stdout);
	data->save_stdout = -1;
	data->r_input_fd = -1;
	data->r_output_fd = -1;
	data->first_cmd = true;
	data->cmd_ct = 0;
}
