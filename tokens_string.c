/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:49:13 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/28 17:55:24 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quote(t_data *data, int i, int type)
{
	int		k;

	i++;
	k = i;
	while (data->s[i] != type)
	{
		if (data->s[i] == '\0')
			break ;
		i++;
	}
	return (i);
}

int	handle_string(t_data *data, int i, t_exec *tmp)
{
	int		k;
	char	*res;
	char	*str;

	str = NULL;
	k = i;
	while (data->s[i] && ft_isstring(data->s[i]))
		i++;
	res = ft_substr(data->s, k, i - k);
	str = ft_strjoin(str, res);
	tmp->value = ft_strjoin(tmp->value, str);
	free(str);
	if (data->s[i] && (data->s[i] == \
	D_QUOT || data->s[i + 1] == S_QUOT))
	{
		i++;
		i = handle_s_quote(data, i, tmp, (int)data->s[i]);
	}
	if (!ft_isstring_w_s(data->s[i]))
		return (i - 1);
	tmp->value = ft_strjoin(tmp->value, "*");
	return (i);
}

int	handle_s_quote(t_data *data, int i, t_exec *tmp, int type)
{
	int		k;
	char	*str;
	char	*res;

	i++;
	k = i;
	str = NULL;
	while (data->s[i] != type)
	{
		if (data->s[i] == '\0')
			print_token_er(data, i, tmp);
		i++;
	}
	res = ft_substr(data->s, k, i - k);
	str = ft_strjoin(str, res);
	tmp->value = ft_strjoin(tmp->value, str);
	free(res);
	free(str);
	i++;
	printf("---->||%c||\n", data->s[i]);
	if (ft_isstring(data->s[i]) && data->s[i])
	{
		i++;
		i = handle_string(data, i, tmp);
	}
	tmp->value = ft_strjoin(tmp->value, "*");
	return (i);
}
