/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:49:13 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/07 21:37:23 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_string(t_data *data, int i)
{
	int		k;
	char	*str;

	k = i;

	if (data->s[i] == '$')
		return (handle_dollar_sign(data, i));
	while (data->s[i] && ft_isstring(data->s[i]))
		i++;
	str = ft_substr(data->s, k, i - k);
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(\
	ft_strtrim(str, " "), STRING));
	free(str);
	return (i - k);
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
		{
			printf(("EROOR\n"));
			return (i - k + 1);
		}
		i++;
	}
	str = ft_substr(data->s, k, i - k);
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec( \
	ft_strtrim(str, " "), STRING));
	free(str);
	return (i - k + 2);
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
		{
			printf(("EROOR\n"));
			return (i - k + 1);
		}
		i++;
	}
	str = ft_substr(data->s, k, i - k);
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec( \
	ft_strtrim(str, " "), STRING));
	free(str);
	return (i - k + 2);
}

int	handle_dollar_sign(t_data *data, int i)
{
	int		k;
	char	*str;

	i++;
	k = i;
	if (data->s[i] == '?')
	{
		ft_lstadd_back_exec(&data->exec, ft_lstnew_exec("$?", EXIT_STATUS));
		return (2);
	}
	else if (ft_isalpha(data->s[i]))
	{
		while (data->s[i] && ft_isstring(data->s[i]))
			i++;
		str = ft_substr(data->s, k, i - k);
		ft_lstadd_back_exec(&data->exec, ft_lstnew_exec( \
		ft_strtrim(str, " "), ENV_VAR));
		free(str);
	}
	else
	{
		printf("ERROR\n");
		return (1);
	}
	return (i - k + 1);
}
