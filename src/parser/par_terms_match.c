/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_terms_match.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muabdi <muabdi@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 08:10:13 by muabdi            #+#    #+#             */
/*   Updated: 2025/01/05 08:10:25 by muabdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/data.h"

bool	terms_match(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (false);
	if (ft_strncmp(str1, str2, ft_strlen(str2)))
		return (false);
	return (true);
}