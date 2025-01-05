/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:35:25 by smoore            #+#    #+#             */
/*   Updated: 2025/01/05 15:10:11 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

void	skyy_pwd(void)
{
	char	buf[256];

	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		perror("cwd");
		exit(EXIT_FAILURE);
	}
	ft_putendl_fd(buf, 1);
	exit(EXIT_SUCCESS);
}
