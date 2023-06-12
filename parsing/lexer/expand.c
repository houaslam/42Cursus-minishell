/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 14:51:22 by houaslam          #+#    #+#             */
/*   Updated: 2023/06/12 17:40:59 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expande_handle(t_data *data, char *str)
{
	char	*save;

	if (data -> d_status % 2 == 0 && data -> s_status % 2 != 0)
		return (str);
	else
	{
		save = find_ex(ft_substr(str, 1, ft_strlen(str) - 1), data->env);
		free(str);
	}
	return (save);
}

char	*the_expande(t_data *data, char *str)
{
	int		i;
	char	*save;

	i = 0;
	while (str[i])
	{
		if (str[1] == '?')
		{
			save = ft_itoa(g_exit_status);
			str = ft_substr(str, 2, ft_strlen(str) - 2);
			save = ft_strjoin_free(save, str);
			free(str);
			return (save);
		}
		else if (ft_isdigit(str[1]))
			return (ft_substr(str, 2, ft_strlen(str) - 2));
		else
			return (expande_handle(data, str));
		i++;
	}
	return (str);
}
