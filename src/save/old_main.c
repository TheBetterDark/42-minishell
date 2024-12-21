/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2024/12/17 13:32:33 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/data.h"

int		find_cmdv_size(t_token *cur)
{
	t_token	*cur_cur;
	int	size;

	size = 0;
	cur_cur = cur;
	while (cur_cur->type != CMD && cur_cur->type != ARG)
	{
		size++;
		cur_cur = cur_cur->next;
	}
	return (size);
}

char	**init_cmdv(t_token *cur, int size)
{
	char **cmdv;
	char **tmp;

	cmdv = malloc(sizeof(char *) * (size + 1));
	if (!cmdv)
		return (NULL);
	tmp = cmdv;
	while (*tmp)
	{
		if (cur->type == CMD || cur->type == ARG)
		{
			*tmp = ft_strdup(cur->cont);
			if (*tmp == NULL)
				return (NULL);
		}
		cur = cur->next;
		tmp++;
	}
	return (cmdv);
}

void	get_new_cmd_data(t_cmd	*new_cmd, t_token *cur)
{
	while (cur && cur->type != PIPE && cur->type != CMD)
	{
		if (cur->type == APPEND_FILE)
			new_cmd->append_fn = cur->cont;
		if (cur->type == OUT_FILE)
			new_cmd->open_fn = cur->cont;
		if (cur->type == IN_FILE)
			new_cmd->input_fn = cur->cont;
		if (cur->type == DELIM)
		{
			new_cmd->eof = cur->cont;
			new_cmd->e_len = ft_strlen(cur->cont);
		}
		cur = cur->next;
	}
}

t_cmd	*init_new_cmd(t_token *cur)
{
	int		size;
	t_cmd	*new_cmd;
	
	size = 0;
	while (cur)
	{
		size = find_cmdv_size(cur);
		new_cmd = malloc(sizeof(t_cmd));
		if (!new_cmd)
			return (NULL);
		new_cmd->cmdv = init_cmdv(cur, size);
		if (!new_cmd->cmdv)
		{
			perror("Cmdv Error");
			return (NULL);
		}
		get_new_cmd_data(new_cmd, cur);
		cur = cur->next;	
	}
	return (new_cmd);
}

void	add_to_job(t_cmd **head_cmd, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (*head_cmd == NULL)
		*head_cmd = new_cmd;
	else
	{
		current = *head_cmd;
		while (current->next != NULL)
			current = current->next;
		current->next = new_cmd;
	}
}

t_cmd	*parser(t_data *d)
{
	t_cmd	*job;
	t_cmd	*new_cmd;
	t_token	*cur;
	int		i;

	job = NULL;
	i = 0;
	cur = d->toks;
	while (i < d->cmd_ct)
	{
		new_cmd = init_new_cmd(cur);	
		add_to_job(&job, new_cmd);
		cur = cur->next;
		i++;
	}
	return (job);
}

void	minishell(t_data *d)
{
	while (1)
	{		
		//d->input = readline("🇲🇮🇳🇮🐚");
		d->input = readline("minishell💲");
		readline_config(d);
		if (!d->input)
			break ;
		d->toks = tokenizer(d);
		print_toks(d);
		d->job = parser(d);
		print_job(d->job);
		free_minishell(d);
	}
}

int	main(void)
{
	t_data		*d;
	extern char	**environ;

	d = init_data(environ);
	minishell(d);
	free_data(d);
}
