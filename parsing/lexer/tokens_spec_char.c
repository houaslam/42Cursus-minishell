/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_spec_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:56:12 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/29 17:10:32 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_here_doc_in(t_data *data, int i, t_exec *tmp)
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
		return (print_token_er(data, 1, tmp));
	ft_lstadd_back_file(&tmp->file, ft_lstnew_file(str, RED_OUT));
	free(str);
	return (i);
}

int	handle_here_doc_out(t_data *data, int i, t_exec *tmp)
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
		return (print_token_er(data - 1, 1, tmp));
	ft_lstadd_back_file(&tmp->file, ft_lstnew_file(str, RED_OUT));
	free(str);
	return (i);
}

int	handle_redin(t_data *data, int i, t_exec *tmp)
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
		return (print_token_er(data, 1, tmp));
	file = ft_lstnew_file(str, RED_IN);
	ft_lstadd_back_file(&tmp->file, ft_lstnew_file(str, RED_IN));
	free(str);
	return (i - 1);
}

int	handle_redout(t_data *data, int i, t_exec *tmp)
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
		return (print_token_er(data, 1, tmp));
	ft_lstadd_back_file(&tmp->file, ft_lstnew_file(str, RED_OUT));
	free(str);
	return (i - 1);
}

int	handle_pipe(t_data *data, int i, t_exec *tmp)
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
			return (print_token_er(data, 1, tmp));
		c--;
	}
	while (data->s[k])
	{
		if (ft_isstring(data->s[k]))
			break ;
		if (data->s[k] == '\0')
			return (print_token_er(data, 1, tmp));
		k++;
	}
	if (tmp -> value)
	{
		ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(tmp->value, PIPE));
		// free_exec(&tmp);
		free(tmp->value);
		tmp = ft_lstnew_exec("*", STRING);
		tmp->file = NULL;
		 // tmp->value = "*"; //
	}
	return (i);
}
