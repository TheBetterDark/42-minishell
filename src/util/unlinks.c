/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlinks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/27 21:29:55 by smoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	unlink_heredocs(t_data *data)
{
	char	*num;
	char	*str;
	char	*file;
	int		count;

	count = 0;
	str = ft_strdup("/tmp/hd2sh9fd8F32_");
	while (count < data->heredoc_ct)
	{
		num = ft_itoa(count);
		file = ft_strjoin(str, num);
		unlink(file);
		count++;
		free(num);
		free(file);
	}
	free(str);
}
