/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_get_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/28 10:53:15 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

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
	int		fd;

	in->read_fn = get_heredoc_name(data->heredoc_ct);
	fd = open(in->read_fn, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Failed to create heredoc filename");
		return (-1); // whatever an error fd is suppose to be
	}
	write(1, "> ", 2);
	while (1)
	{
		buf = get_next_line(STDIN_FILENO);
		if (ft_strncmp(buf, eof, size) == 0 && buf[size] == '\n')
		{
			free(buf);
			break ;
		}
		buf = dup_double_quotes(buf, data);
		write(fd, buf, ft_strlen(buf));
		free(buf);
		write(1, "> ", 2);
	}
	close(fd);
	return (fd);
}
