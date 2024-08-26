/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:35:04 by muabdi            #+#    #+#             */
/*   Updated: 2024/08/26 16:11:30 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/colour.h"
#include "../../includes/minishell.h"

static char	*format_prompt(t_prompt *prompt);

t_prompt	*initialize_prompt(void)
{
	t_prompt	*prompt;

	prompt = malloc(sizeof(t_prompt));
	if (!prompt)
		return (perror("Error allocating memory"), NULL);
	prompt->user = getenv("USER");
	if (prompt->user == NULL)
		return (perror("Error getting USER environment variable"), free(prompt),
			NULL);
	if (ft_gethostname(prompt->hostname) == -1)
		return (perror("Error getting hostname"), free(prompt), NULL);
	if (ft_getcwd(prompt->cwd, true) == -1)
		return (perror("Error getting current working directory"), free(prompt),
			NULL);
	return (prompt);
}

char	*display_prompt(t_prompt *prompt)
{
	char	*prompt_str;
	char	*input;

	prompt_str = format_prompt(prompt);
	if (!prompt_str)
		return (perror("Error formatting prompt"), NULL);
	input = readline((const char *)prompt_str);
	return (input);
}

static char	*format_prompt(t_prompt *prompt)
{
	static char	prompt_str[256];

	ft_snprintf(prompt_str, sizeof(prompt_str),
		USR "%s@%s" RST ":" CWD "%s" RST "$ ", prompt->user,
		prompt->hostname, prompt->cwd);
	return (prompt_str);
}
