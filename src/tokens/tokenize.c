/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:35:40 by smoore            #+#    #+#             */
/*   Updated: 2025/02/19 15:18:06 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	tokenize(t_data *data);

void	tokenize(t_data *data)
{
	char	**words;
	char	**cur;
	t_token	*new;

	if (!g_signal && data->input)
	{
		words = command_line_split(data->input);
		cur = words;
		while (*cur)
		{
			new = tok_lstnew(*cur);
			if (!new)
				return (tok_lstclear(&data->toks), ft_str_arr_free(&words));
			tok_lstadd_back(&data->toks, new);
			cur++;
		}
	}
	ft_str_arr_free(&words);
	assign_tok_types(data->toks, data);
}
