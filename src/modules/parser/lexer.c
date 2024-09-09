/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:44:01 by muabdi            #+#    #+#             */
/*   Updated: 2024/09/09 14:53:46 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_lexer	*lexer_init(char *input)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->input = input;
	lexer->position = 0;
	lexer->cursor = input[0];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->cursor != '\0' && lexer->position < ft_strlen(lexer->input))
	{
		lexer->position++;
		lexer->cursor = lexer->input[lexer->position];
	}
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!lexer)
		return (NULL);
	while (lexer->cursor != '\0')
	{
		if (lexer->cursor == ' ')
			lexer_advance(lexer);
	}
	return (NULL);
}

t_token	*lexer_tokenize(char *input)
{
	t_lexer	*lexer;
	t_token	*tokens;
	t_token	*token;

	lexer = lexer_init(input);
	tokens = NULL;
	while (lexer->cursor != '\0')
	{
		token = lexer_get_next_token(lexer);
		token_append(&tokens, token);
	}
	return (tokens);
}
