/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:02:27 by aatki             #+#    #+#             */
/*   Updated: 2023/05/08 22:28:02 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*check(char **s)
{
	int		i;
	char	*ret;
	char	*tmp2;
	char	*tmp_s;

	i = 0;
	tmp_s = *s;
	if (!tmp_s)
		return (NULL);
	while (tmp_s[i])
	{
		if (tmp_s[i] == '\n')
		{
			ret = ft_strdup(tmp_s + i + 1);
			tmp2 = ft_substr(tmp_s, 0, i + 1);
			free(*s);
			*s = ft_strdup(tmp2);
			free(tmp2);
			return (ret);
		}
		i++;
	}
	return (NULL);
}
