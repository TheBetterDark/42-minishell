/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/17 13:11:22 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

void	print_type(int type)
{
	printf(", Type: ");
	if (type == PIPE)
		printf("Pipe");
	else if (type == RDR_IN)
		printf("Redir. In");
	else if (type == RDR_OUT)
		printf("Redir. Out");
	else if (type == RDR_APPEND)
		printf("Redir. Append");
	else if (type == RDR_HEREDOC)
		printf("Redir. Heredoc");
	else if (type == CMD)
		printf("Command");
	else if (type == ARG)
		printf("Argument");
	else if (type == DELIM)
		printf("Delimiter");
	else if (type == IN_FILE)
		printf("In File");
	else if (type == OUT_FILE)
		printf("Out File");
	else if (type == APPEND_FILE)
		printf("Append File");
	else
		printf("Error :)");
	printf("\n");
}

void	print_toks(t_data *d)
{
	t_token	*current;

	current = d->toks;
	while (current != NULL)
	{
		printf("Tok: %s", current->cont);
		print_type(current->type);
		current = current->next;
	}
}

void	print_job(t_cmd *job)
{
	t_cmd	*current;
	char	**tmp;
	int	i;
	int	j;

	i = 0;
	current = job;
	while (current)
	{
		printf(":: Command %d ::\n", ++i);
		tmp = current->cmdv;
		j = 0;
		while (*tmp)
		{
			printf("Cmdv[%d]\t%s\n", ++j, *tmp);
			tmp++;
		}
		if (current->eof)
		{
			printf("Eof:\t%s\n", current->eof);
			printf("Eof Len:\t%d\n", current->e_len);
		}
		if (current->open_fn)
			printf("Open_fn:\t%s\n", current->open_fn);
		if (current->append_fn)
			printf("Append_fn:\t%s\n", current->append_fn);
		if (current->input_fn)
			printf("Infile:\t%s\n", current->input_fn);
		printf("\n");
		current = current->next;
	}
}
