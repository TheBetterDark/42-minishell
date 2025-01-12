/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/12 20:44:22 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

/*
* @brief Frees the split string
*
* @param split The split string
*/
static void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

/*
* @brief Tokenizes the input string
*
* @param data The data structure
*
* @return The head of the token list
*/
t_token	*tokenizer(t_data *data)
{
	char	**toks;
	char	**toks_start;
	t_token	*head;
	t_token	*new_tok;

	toks = command_line_split(data->input, data);
	if (!toks)
		return (handle_error(data, ERR_OUT_OF_MEMORY, 1, false), NULL);
	toks_start = toks;
	head = NULL;
	while (*toks)
	{
		new_tok = tok_lstnew(*toks);
		tok_lstadd_back(&head, new_tok);
		toks++;
	}
	free_split(toks_start);
	tok_redir_operator_type_assigner(head);
	tok_redir_file_type_assigner(head);
	tok_cmd_type_assigner(head);
	return (head);
}
