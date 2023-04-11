/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:49:13 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/11 14:26:16 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_string(t_data *data, int i)
{
	int		k;
	char	*str;
	char	*res;

	k = i;
	if (data->s[i] == '$')
		return (handle_dollar_sign(data, i));
	while (data->s[i] && ft_isstring(data->s[i]))
		i++;
	str = ft_substr(data->s, k, i - k);
	res = ft_strtrim(str, " ");
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(res \
	, STRING));
	free(str);
	free(res);
	return (i + 1);
}

int	handle_d_quote(t_data *data, int i)
{
	int		k;
	char	*str;
	char	*res;

	i++;
	k = i;
	while (data->s[i] != D_QUOT)
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
	{
		printf("ERROR\n");
		free_exec(&data->exec);
		return (ft_strlen(data->s));
	}
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
	{
		printf("ERROR\n");
		free_exec(&data->exec);
		return (ft_strlen(data->s));
	}
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(res, ENV_VAR));
	free(str);
	free(ptr);
	free(res);
	return (i);
}
