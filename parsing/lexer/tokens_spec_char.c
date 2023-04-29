/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_spec_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:56:12 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/29 21:55:37 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_here_doc_in(t_data *data, int i, t_file *tmp_f)
{
	int		k;
	char	*str;

	i++;
	i++;
	k = i;
	while (data->s[i] == 32 || data->s[i] == 9)
		i++;
	while (data->s[i] && ft_isstring(data->s[i]))
		i++;
	str = ft_substr(data->s, k, i - k);
	if (str[0] == '\0' || i - k == 0)
		return (print_token_er(data, 1, NULL));
	ft_lstadd_back_file(&tmp_f, ft_lstnew_file(str, RED_OUT));
	free(str);
	return (i);
}

int	handle_here_doc_out(t_data *data, int i, t_file *tmp_f)
{
	int		k;
	char	*str;

	i++;
	i++;
	k = i;
	while (data->s[i] == 32 || data->s[i] == 9)
		i++;
	while (data->s[i] && ft_isstring(data->s[i]))
		i++;
	str = ft_substr(data->s, k, i - k);
	if (str[0] == '\0' || i - k == 0)
		return (print_token_er(data - 1, 1, NULL));
	ft_lstadd_back_file(&tmp_f, ft_lstnew_file(str, RED_OUT));
	free(str);
	return (i);
}

int	handle_redin(t_data *data, int i, t_file *tmp_f)
{
	int		k;
	char	*str;
	t_file	*file;

	i++;
	while (data->s[i] == 32 || data->s[i] == 9)
		i++;
	k = i;
	while (data->s[i] && ft_isstring(data->s[i]))
		i++;
	str = ft_substr(data->s, k, i - k);
	if (str[0] == '\0' || i - k == 0)
		return (print_token_er(data, 1, NULL));
	file = ft_lstnew_file(str, RED_IN);
	ft_lstadd_back_file(&tmp_f, ft_lstnew_file(str, RED_IN));
	free(str);
	return (i - 1);
}

int	handle_redout(t_data *data, int i, t_file *tmp_f)
{
	int		k;
	char	*str;

	i++;
	while (data->s[i] == 32 || data->s[i] == 9)
		i++;
	k = i;
	while (data->s[i] && ft_isstring(data->s[i]))
		i++;
	str = ft_substr(data->s, k, i - k);
	if (str[0] == '\0' || i - k == 0)
		return (print_token_er(data, 1, NULL));
	ft_lstadd_back_file(&tmp_f, ft_lstnew_file(str, RED_OUT));
	free(str);
	return (i - 1);
}

int	check_pipe(t_data *data, int i)
{
	int		k;
	int		c;

	k = i + 1;
	c = i - 1;
	while (data->s[c])
	{
		if (ft_isalpha(data->s[c]))
			break ;
		if (c == 0)
			return (1);
		c--;
	}
	while (data->s[k])
	{
		if (ft_isstring(data->s[k]))
			break ;
		if (data->s[k] == '\0')
			return (1);
		k++;
	}
	return (0);
}


int	handle_pipe(t_data *data, int i, t_exec *tmp, t_file *tmp_f)
{
	if (check_pipe(data, i) == 1)
		return (print_token_er(data, 1, tmp));
	if (tmp -> value)
	{
		tmp->file = tmp_f;
		ft_lstadd_back_exec(&data->exec, \
		ft_lstnew_exec(ft_strdup(tmp->value), PIPE));
		free(tmp->value);
		tmp->value = NULL;
		tmp = ft_lstnew_exec("*", STRING);

	}
	return (i);
}
