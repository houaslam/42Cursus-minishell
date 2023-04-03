/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:49:13 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/03 02:26:42 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_string(t_data *data, int i)
{
	int	j;

	j = i;
	while (data->s[i])
	{
		if (!ft_isalpha(data->s[i]))
			break ;
		i++;
	}
	data->string->str = ft_substr(data->s, j, i);
	return (i);
}

int	handle_d_quote(t_data *data, int i)
{
	int	k;

	k = i;
	i++;
	while (data->s[i])
	{
		if (data->s[i] == D_QUOT)
		{
			data->string->str = ft_substr(data->s, k, i + 1);
			return (i - k);
		}
		i++;
	}
	ft_putstr_fd("error\n", 2);
	exit (0);
}

int	handle_s_quote(t_data *data, int i)
{
	int	k;

	k = i;
	i++;
	while (data->s[i])
	{
		if (data->s[i] == S_QUOT)
		{
			data->string->str = ft_substr(data->s, k, i + 1);
			printf("%s\n", data->string->str);
			return (i - k);
		}
		i++;
	}
	ft_putstr_fd("error\n", 2);
	exit (0);
}
