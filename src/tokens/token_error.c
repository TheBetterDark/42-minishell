/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:52:56 by smoore            #+#    #+#             */
/*   Updated: 2025/02/19 18:09:48 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void		unexpected_token_error(t_token *head, t_data *data);
static bool	is_tok_symbol(t_token *cur);
//static bool	is_file(t_token *cur);
void		check_for_final_cmd(t_token *head, t_data *data);
void		check_for_redir_files(t_token *head, t_data *data);

void	unexpected_token_error(t_token *head, t_data *data)
{
	t_token	*cur;
	bool	cmd_found;

	cur = head;
	cmd_found = false;
	while (cur && !data->token_syntax_error)
	{
		if (cur->type == CMD)
			cmd_found = true;
		if (cur->type == PIPE && !cmd_found)
		{
			data->token_syntax_error = true;
			ft_putstr_fd(PIPE_ERR, 2);
		}
		else if (cur->type == PIPE && cmd_found)
			cmd_found = false;
		cur = cur->next;
	}
}

static bool	is_tok_symbol(t_token *cur)
{
	return (cur->type == RE_READ || cur->type == RE_TRUNC
		|| cur->type == RE_APPEND || cur->type == RE_HEREDOC);
}

void	check_for_final_cmd(t_token *head, t_data *data)
{
	t_token	*cur;
	bool	cmd_found;
	bool	symbol_found;

	cur = tok_lstlast(head);
	cmd_found = false;
	symbol_found = false;
	while (cur && !data->token_syntax_error)
	{
		if (cur->type == CMD)
			cmd_found = true;
		else if (is_tok_symbol(cur))
			symbol_found = true;
		else if (cur->type == PIPE && !cmd_found && symbol_found)
		{
			data->token_syntax_error = true;
			ft_putstr_fd(NL_ERR, 2);
		}
		else if (cur->type == PIPE && !cmd_found && !symbol_found)
		{
			get_next_input(data);
			break ;
		}
		cur = cur->prev;
	}
}

void	check_for_redir_files(t_token *head, t_data *data)
{
	t_token	*cur;

	cur = head;
	while (cur)
	{
		if (!cur->next && is_tok_symbol(cur))
		{
			data->token_syntax_error = true;
			ft_putstr_fd(NL_ERR, 2);
			break ;
		}
		if (cur && cur->next && check_redir_file_error(cur, cur->next))
		{
			data->token_syntax_error = true;
			ft_putstr_fd(NL_ERR, 2);
			break ;
		}
		cur = cur->next;
	}
}
