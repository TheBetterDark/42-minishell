/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:52:56 by smoore            #+#    #+#             */
/*   Updated: 2025/02/10 15:14:59 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

static bool	has_plain_text(char *buf);
static void	join_input_and_buf(t_data *data, char *buf);
void		get_next_input(t_data *data);

static bool	has_plain_text(char *buf)
{
	int	i;	

	i = 0;
	while (buf[i])
	{
		if (!is_blank(buf[i]) && buf[i] != '\n')
			return (true);
		i++;
	}
	return (false);
}

static void	join_input_and_buf(t_data *data, char *buf)
{
	char	*join;	
	char	*trim;	

	join = ft_strjoin(data->input, " ");
	if (!join)
	{
		data->input = NULL;
		return ;
	}
	free(data->input);
	trim = ft_strtrim(buf, "\n");
	free(buf);
	data->input = ft_strjoin(join, trim);
	free(join);
	free(trim);
	if (!data->input)
		data->input = NULL;
}

void	get_next_input(t_data *data)
{
	char	*buf;

	while (g_signal == NO_SIGNAL)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		buf = get_next_line(STDIN_FILENO);
		if (g_signal == NO_SIGNAL && has_plain_text(buf))
		{
			join_input_and_buf(data, buf);
			if (!data->input)
				return ;
			if (g_signal == NO_SIGNAL)
			{
				tok_lstclear(&data->toks);
				tokenize(data);
				return ;
			}
			else
				run_minishell(data);
		}
		free(buf);
	}
}
