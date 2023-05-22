/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:49:13 by houaslam          #+#    #+#             */
/*   Updated: 2023/05/22 15:51:46 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exec	*handle_dollar(t_data *data, t_exec *lexer)
{
	char	*str;
	int		k;

	k = 1;
	if (data -> d_status % 2 == 0 && data -> s_status % 2 != 0)
	{
		str = ft_substr(lexer->value, 1, ft_strlen(lexer->value) - 1);
		data -> tmp -> value = ft_strjoin_free(data->tmp->value, lexer->value);
		data -> tmp -> value = ft_strjoin_free(data->tmp->value, "@");
	}
	else
	{
		if (lexer -> value[k] == '?' && ++k)
			data -> tmp -> value = \
			ft_strjoin_free(data->tmp->value, ft_itoa(g_exit_status));
		str = find_ex(ft_substr(lexer->value, k, \
		ft_strlen(lexer->value) - 1), data->env);
		data -> tmp -> value = ft_strjoin_free(data->tmp->value, str);
		data -> tmp -> value = ft_strjoin_free(data->tmp->value, "@");
	}
	return (lexer);
}

t_exec	*handle_string(t_data *data, t_exec *lexer)
{
	data -> tmp -> value = ft_strjoin_free(data->tmp->value, lexer->value);
	data -> tmp -> value = ft_strjoin_free(data->tmp->value, "@");
	if (lexer->next && lexer->next->type == S_QUOT)
		lexer = handle_s_quote(data, lexer -> next);
	else if (lexer->next && lexer->next->type == D_QUOT)
		lexer = handle_d_quote(data, lexer -> next);
	return (lexer);
}

t_exec	*handle_s_quote(t_data *data, t_exec *lexer)
{
	lexer = lexer->next;
	while (lexer -> type != S_QUOT)
	{
		if (!lexer)
			return (print_token_er(data, 258, "`\"'\n"));
		data->tmp->value = ft_strjoin(data->tmp->value, lexer->value);
		lexer = lexer->next;
	}
	if (lexer->next && lexer->next->type == STRING)
		lexer = handle_string(data, lexer);
	data -> tmp->value = ft_strjoin_free(data -> tmp -> value, "@");
	return (lexer);
}

t_exec	*handle_d_quote(t_data *data, t_exec *lexer)
{
	lexer = lexer->next;
	while (lexer -> type != D_QUOT)
		lexer = lexer->next;
	if (lexer->next && lexer->next->type == STRING)
		lexer = handle_string(data, lexer);
	data -> tmp->value = ft_strjoin_free(data -> tmp -> value, "@");
	return (lexer);
}

t_exec	*handle_pipe(t_data *data, t_exec *lexer)
{
	if (check_pipe(lexer) == 1)
		return (print_token_er(data, 258, "`|'\n"));
	if (data -> tmp -> value)
	{
		ft_lstadd_back_exec(&data->exec, \
		ft_lstnew_exec(data -> tmp->value, PIPE, data -> tmp_f, lexer));
		free_exec(&data -> tmp);
		data -> tmp = ft_lstnew_exec("@", STRING, data -> tmp_f, lexer);
	}
	return (lexer);
}
