/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:44:01 by muabdi            #+#    #+#             */
/*   Updated: 2024/09/30 17:25:57 by muabdi           ###   ########.fr       */
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
	if (!lexer)
		return (NULL);
	while (lexer->cursor != '\0')
	{
		if (lexer->cursor == ' ')
			lexer_advance(lexer);
		else if (lexer->cursor == '>')
			return (handle_greater(lexer));
		else if (lexer->cursor == '<')
			return (handle_less(lexer));
		else if (lexer->cursor == '\'')
			return (handle_single_quote(lexer));
		else if (lexer->cursor == '"')
			return (handle_double_quote(lexer));
		else if (lexer->cursor == '|')
			return (handle_pipe(lexer));
		else
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
	if (!lexer)
		return (NULL);
	tokens = NULL;
	while (lexer->cursor != '\0')
	{
		token = lexer_get_next_token(lexer);
		if (!token)
			break ;
		token_append(&tokens, token);
	}
	lexer_cleanup(lexer);
	return (tokens);
}

void	lexer_cleanup(t_lexer *lexer)
{
	if (!lexer)
		return ;
	free(lexer);
}
