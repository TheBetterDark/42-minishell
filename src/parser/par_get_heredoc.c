/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_get_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/02/02 16:09:32 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

static int	open_heredoc_fd(t_in *in)
{
	int	fd;

	fd = open(in->read_fn, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Failed to create heredoc filename");
		return (-1);
	}
	return (fd);
}

static char	*get_heredoc_name(int heredoc_ct)
{
	char	*filename;
	char	*num;
	char	*result;

	filename = ft_strdup("/tmp/hd2sh9fd8F32_");
	num = ft_itoa(heredoc_ct);
	result = ft_strjoin(filename, num);
	free(filename);
	free(num);
	return (result);
}

int	get_heredoc(char *eof, int size, t_in *in, t_data *data)
{
	char	*buf;
	char	*temp;
	int		fd;

	in->read_fn = get_heredoc_name(data->heredoc_ct);
	fd = open_heredoc_fd(in);
	if (fd == -1)
		return (-1);
	while (true)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		buf = get_next_line(STDIN_FILENO);
		if (ft_strncmp(buf, eof, size) == 0 && buf[size] == '\n')
		{
			free(buf);
			break ;
		}
		temp = dup_double_quotes(buf, data);
		free(buf);
		buf = temp;
		ft_putstr_fd(buf, fd);
		free(temp);
	}
	close(fd);
	return (fd);
}
