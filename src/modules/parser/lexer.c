/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:44:01 by muabdi            #+#    #+#             */
/*   Updated: 2024/11/27 19:51:35 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
* @brief Initialize the lexer
*
* @param input The input string
* @return A new lexer 
*/
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
,l
// TODO: Handle CMD and ARG that is not in quotes
t_token	*lexer_get_next_token(t_lexer *lexer)
{
	if (!lexer)
		return (NULL);
	while (lexer->cursor != '\0')
	{
		if (lexer->cursor == ' ')
			lexer_advance(lexer);
		else if (lexer->cursor == '>' || lexer->cursor == '<')
			return (handle_redirect(lexer, lexer->cursor));
		else if (lexer->cursor == '\'' || lexer->cursor == '"')
			return (handle_quotes(lexer, lexer->cursor));
		else if (lexer->cursor == '|')
			return (handle_pipe(lexer));
		else if (lexer->cursor == '/0')
			return (token_new(TOKEN_END, ft_strdup("\0")));
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
