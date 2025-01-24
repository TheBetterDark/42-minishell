/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlinks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/24 17:38:57 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	unlink_heredocs(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		count;
	char	*num;
	char	*str;
	char	*file;

	if (!cmd->ins)
		return ;
	count = 0;
	tmp = cmd;
	str = ft_strdup("/tmp/hd2sh9fd8F32_");
	while (tmp)
	{
		if (tmp->ins && tmp->ins->eof)
		{
			num = ft_itoa(count);
			file = ft_strjoin(str, num);
			unlink(file);
			count++;
			free(num);
			free(file);
		}
		tmp = tmp->next;
	}
	free(str);
}
