/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_spec_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:56:12 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/15 18:47:31 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_here_doc_in(t_data *data, int i)
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
		return (print_token_er(data));
	ft_lstadd_back_file(&data->exec->file, ft_lstnew_file(str, HERE_DOC_IN));
	free(str);
	return (i);
}

int	handle_here_doc_out(t_data *data, int i)
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
		return (print_token_er(data) - 1);
	ft_lstadd_back_file(&data->exec->file, ft_lstnew_file(str, HERE_DOC_OUT));
	free(str);
	return (i);
}

int	handle_redin(t_data *data, int i)
{
	int		k;
	char	*str;
	t_file	*file;

	i++;
	while (data->s[i] == 32)
		i++;
	k = i;
	while (data->s[i] && ft_isstring(data->s[i]))
		i++;
	str = ft_substr(data->s, k, i - k);
	if (str[0] == '\0' || i - k == 0)
		return (print_token_er(data));
	printf("=====%s=====\n", str);
	// if (!data->join)
	// 	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec \
	// 	(ft_strjoin(data->join, " "), STRING));
	file = ft_lstnew_file(str, RED_IN);
	ft_lstadd_back_file(&data->exec->file, file);
	free(str);
	return (i);
}

int	handle_redout(t_data *data, int i)
{
	int		k;
	char	*str;

	i++;
	while (data->s[i] == 32)
		i++;
	k = i;
	while (data->s[i] && ft_isstring(data->s[i]))
		i++;
	str = ft_substr(data->s, k, i - k);
	if (str[0] == '\0' || i - k == 0)
		return (print_token_er(data));
	if (!data->join)
		return (print_token_er(data));
	ft_lstadd_back_file(&data->exec->file, ft_lstnew_file(str, RED_OUT));
	free(str);
	return (i);
}

int	handle_pipe(t_data *data, int i)
{
	int		k;
	int		c;

	k = i + 1;
	c = 0;
	while (data->s[c])
	{
		if (ft_isalpha(data->s[c]))
			break ;
		if (data->s[c] == PIPE)
			return (print_token_er(data));
		c++;
	}
	while (data->s[k])
	{
		if (ft_isstring(data->s[k]))
			break ;
		if (data->s[k] == '\0')
			return (print_token_er(data));
		k++;
	}
	if (data->join)
	{
		printf("%s\n", data->join);
		ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(data->join, PIPE));
		data->pipe = 1;
		free(data->join);
		data->join = NULL;
	}
	free(data->join);
	return (i);
}
