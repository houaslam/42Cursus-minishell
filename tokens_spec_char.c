/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_spec_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:56:12 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/04 23:05:01 by houaslam         ###   ########.fr       */
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
	str = ft_substr(data->s, k, i - k + 1);
	if (str[0] == '\0')
		exit(0);
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(str, HERE_DOC_IN));
	free(str);
	return (i - k + 1);
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
	str = ft_substr(data->s, k, i - k + 1);
	if (str[0] == '\0')
		exit(0);
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(str, HERE_DOC_OUT));
	free(str);
	return (i - k + 1);
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
	str = ft_substr(data->s, k, i - k);
	if (str[0] == '\0')
		exit(0);
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
	str = ft_substr(data->s, k, i - k);
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(str, RED_OUT));
	free(str);
	return (i - k);
}

int	handle_pipe(t_data *data, int i)
{
	int	k;

	k = i;
	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(NULL, PIPE));
	i++;
	return (i - k);
}
