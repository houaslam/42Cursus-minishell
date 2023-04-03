/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:49:13 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/03 18:03:39 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	handle_string(t_data *data, int i)
// {
// 	int	j;
//
// 	j = i;
// 	while (data->s[i])
// 	{
// 		if (!ft_isalpha(data->s[i]))
// 			break ;
// 		i++;
// 	}
// 	data->string->str = ft_substr(data->s, j, i);
// 	return (i);
// }

int	handle_d_quote(t_data *data, int i)
{
	int		k;
	char	*str;

	i++;
	k = i;
	while (data->s[i])
	{
		if (data->s[i] == D_QUOT)
			break ;
		i++;
	}
	str = ft_substr(data->s, k, i);
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(str, STRING));
	free(str);
	return (i - k + 1);
	// ft_putstr_fd("error\n", 2);
	return (0);
}

int	handle_s_quote(t_data *data, int i)
{
	int		k;
	char	*str;

	i++;
	k = i;
	while (data->s[i] && ft_isstring_(data->s[i]))
		i++;
	if (data->s[i] == S_QUOT)
	{
		str = ft_substr(data->s, k, i);
		ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(str, STRING));
		free(str);
		return (i - k + 1);
	}
	// ft_putstr_fd("error\n", 2);
	return (0);
	// exit (0);
}

int	handle_redin(t_data *data, int i)
{
	int		k;
	char	*str;

	i++;
	k = i;
	while (data->s[i] == 32)
		i++;
	while (data->s[i] && ft_isstring(data->s[i]))
		i++;
	str = ft_substr(data->s, k, i);
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(str, RED_IN));
	free(str);
	return (i - k);
}

int	handle_redout(t_data *data, int i)
{
	int		k;
	char	*str;

	i++;
	k = i;
	while (data->s[i] == 32)
		i++;
	while (data->s[i] && ft_isstring(data->s[i]))
		i++;
	str = ft_substr(data->s, k, i);
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(str, RED_OUT));
	free(str);
	return (i - k);
}
