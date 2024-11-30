/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:40:50 by muabdi            #+#    #+#             */
/*   Updated: 2024/11/30 16:48:46 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
* @brief Handles redirect out, append, redirect in, and heredoc
*
* @param lexer The lexer structure
* @param type The type of redirection to handle (>, >>, <, <<)
* @return A new token
*/
t_token	*handle_redirect(t_lexer *lexer, char type)
{
	lexer_advance(lexer);
	if (lexer->cursor == type)
	{
		lexer_advance(lexer);
		if (type == '>')
			return (token_new(TOKEN_APPEND, ft_strdup(">>")));
		else if (type == '<')
			handle_heredoc(lexer);
	}
	if (type == '>')
		return (token_new(TOKEN_REDIR_OUT, ft_strdup(">")));
	else if (type == '<')
		return (token_new(TOKEN_REDIR_IN, ft_strdup("<")));
	return (NULL);
}

/*
* @brief Handle the quotes
*
* @param lexer The lexer structure
* @return A new token
*/
/*
    TODO: Grab the stuff inside the quotes 
    TODO: Identify if its a double or single for expasion
*/
t_token	*handle_quotes(t_lexer *lexer, char quote_type)
{
	if (!quote_type)
		return (NULL);
	lexer_advance(lexer);
	return (token_new(TOKEN_ARG, ft_strdup(&quote_type)));
}

/*
* @brief Handle the delimiter for heredoc
*
* @param lexer The lexer structure
* @return A new token
*/
t_token	*handle_heredoc(t_lexer *lexer)
{
	if (!delimiter)
		return (NULL);
	lexer_advance(lexer);
	return (token_new(TOKEN_DELIMETER, ft_strdup(delimiter)));
}

/*
* @brief Handle the pipe sign
*
* @param lexer The lexer structure
* @return A new token
*/
t_token	*handle_pipe(t_lexer *lexer)
{
	lexer_advance(lexer);
	return (token_new(TOKEN_PIPE, ft_strdup("|")));
}
