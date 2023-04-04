/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:49:13 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/04 22:56:50 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_string(t_data *data, int i)
{
	int		k;
	char	*str;


	k = i;
	while (data->s[i] && data->s[i] != 32 && data->s[i] != 9)
		i++;
	str = ft_substr(data->s, k, i - k);
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(str, STRING));
	free(str);
	return (i - k - 1);
}

int	handle_d_quote(t_data *data, int i)
{
	int		k;
	char	*str;

	i++;
	k = i;
	while (data->s[i] != D_QUOT)
	{
		if (data->s[i] == '\0')
			exit(1);
		i++;
	}
	str = ft_substr(data->s, k, i - k);
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(str, STRING));
	free(str);
	return (i - k + 1);
}

int	handle_s_quote(t_data *data, int i)
{
	int		k;
	char	*str;

	i++;
	k = i;
	while (data->s[i] != S_QUOT)
	{
		if (data->s[i] == '\0')
			exit(1);
		i++;
	}
	str = ft_substr(data->s, k, i - k);
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(str, STRING));
	free(str);
	return (i - k + 1);
}




