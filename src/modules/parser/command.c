/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:16:25 by muabdi            #+#    #+#             */
/*   Updated: 2024/11/21 20:37:01 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_command	*command_new(char *path, char **args)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->path = path;
	command->args = args;
	command->input_fd = STDIN_FILENO;
	command->output_fd = STDOUT_FILENO;
	command->append_fd = STDOUT_FILENO;
	command->eof = NULL;
	command->next = NULL;
	return (command);
}

void	command_append(t_command ***commands, t_command *new)
{
	t_command	**last;

	if (!new)
		return ;
	if (!**commands)
	{
		**commands = new;
		return ;
	}
	last = *commands;
	while (*last)
		last = &(*last)->next;
	*last = new;
}

void	command_cleanup(t_command **commands)
{
	if (!commands || !*commands)
		return ;
	if ((*commands)->next)
		token_cleanup(&(*commands)->next);
	if ((*commands)->value)
		free((*commands)->value);
	free(*commands);
	*commands = NULL;
}
