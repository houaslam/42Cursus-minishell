/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:49:13 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/12 22:43:22 by houaslam         ###   ########.fr       */
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

int	handle_string(t_data *data, int i)
{
	int		k;
	int		o;
	char	*str;

	k = 0;
	str = malloc(sizeof(char *));
	while (data->s[i] && ft_isstring__(data->s[i]))
	{
		if (data->s[i] == D_QUOT || data->s[i] == S_QUOT)
		{
			o = handle_quote(data, i, (int)data->s[i]);
			if (data->s[o] == '\0')
				return (print_token_er(data));
			i++;
			str = ft_strjoin(str, ft_substr(data->s, i, o - i));
			k += o - i;
			i = o + 1;
		}
		else
			str[k] = data->s[i];
		k++;
		i++;
	}
	str[k] = '\0';
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(str, STRING));
	free(str);
	return (i);
}

int	handle_s_quote(t_data *data, int i)
{
	int		k;
	char	*str;
	char	*res;

	i++;
	k = i;
	while (data->s[i] != S_QUOT)
	{
		if (data->s[i] == '\0')
		{
			printf(("EROOR\n"));
			free_exec(&data->exec);
			return (ft_strlen(data->s));
		}
		i++;
	}
	str = ft_substr(data->s, k, i - k);
	res = ft_strtrim(str, " ");
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(res, STRING));
	free(str);
	free(res);
	return (i + 1);
}

int	handle_dollar_sign(t_data *data, int i)
{
	int		k;

	i++;
	k = i;
	if (data->s[i] == '?')
	{
		ft_lstadd_back_exec(&data->exec, ft_lstnew_exec("$?", EXIT_STATUS));
		return (i + 1);
	}
	else if (ft_isalpha(data->s[i]))
		return (handle_env_var(data, i, k));
	else
		return (print_token_er(data));
	return (i);
}

int	handle_env_var(t_data *data, int i, int k)
{
	char	*str;
	char	*res;
	char	*ptr;

	while (data->s[i] && ft_isstring(data->s[i]))
		i++;
	str = ft_substr(data->s, k, i - k);
	ptr = ft_strtrim(str, " ");
	res = seach_env_value(ptr, data);
	if (!res)
		return (print_token_er(data));
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(res, ENV_VAR));
	free(str);
	free(ptr);
	free(res);
	return (i);
}
