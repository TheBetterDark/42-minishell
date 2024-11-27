/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 18:40:50 by muabdi            #+#    #+#             */
/*   Updated: 2024/11/27 18:46:37 by muabdi           ###   ########.fr       */
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
            return (token_new(TOKEN_HEREDOC, ft_strdup("<<")));
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
t_token	*handle_quotes(t_lexer *lexer, char quote)
{
	if (!quote)
		return (NULL);
	lexer_advance(lexer);
	return (token_new(TOKEN_ARG, ft_strdup(quote_type)));
}

/*
* @brief Handle the delimiter for heredoc
*
* @param lexer The lexer structure
* @return A new token
*/
t_token	*handle_delimiter(t_lexer *lexer, char *delimiter)
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
