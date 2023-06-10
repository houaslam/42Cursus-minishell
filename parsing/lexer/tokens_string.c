/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:49:13 by houaslam          #+#    #+#             */
/*   Updated: 2023/06/01 17:22:49 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exec	*handle_dollar(t_data *data, t_exec *lexer, int sep, int is_red)
{
	char	**str;
	int		k;

	str = ft_split(lexer->value, ' ');
	k = 0;
	while (str[k])
		k++;
	if (k > 1 && is_red == 0)
		print_token_er(data, 1, " ambiguous redirect\n");
	k = 0;
	while (str[k])
	{
		if (sep != 1)
			data -> tmp -> value = ft_strjoin_free(data->tmp->value, "\n");
		data->tmp->value = ft_strjoin_free(data->tmp->value, str[k++]);
	}
	if (lexer->next && lexer->next->type == STRING)
		lexer = handle_string(data, lexer->next, 1);
	else if (lexer->next && lexer->next->type == DOLLAR)
		lexer = handle_dollar(data, lexer->next, 1, 1);
	else if (lexer->next && lexer->next->type == D_QUOT)
		lexer = handle_d_quote(data, lexer->next, 1);
	else if (lexer->next && lexer->next->type == S_QUOT)
		lexer = handle_s_quote(data, lexer->next, 1);
	return (lexer);
}

t_exec	*handle_string(t_data *data, t_exec *lexer, int sep)
{
	data -> tmp -> value = ft_strjoin_free(data->tmp->value, lexer->value);
	if (lexer->next && lexer->next->type == DOLLAR)
		lexer = handle_dollar(data, lexer, 0, 1);
	else if (lexer->next && lexer->next->type == D_QUOT)
		lexer = handle_d_quote(data, lexer->next, 1);
	else if (lexer->next && lexer->next->type == S_QUOT)
		lexer = handle_s_quote(data, lexer->next, 1);
	if (sep != 1)
		data -> tmp -> value = ft_strjoin_free(data->tmp->value, "\n");
	return (lexer);
}

t_exec	*handle_s_quote(t_data *data, t_exec *lexer, int sep)
{
	if (lexer -> next)
		lexer = lexer->next;
	while (lexer -> type != S_QUOT)
	{
		if (!lexer)
			return (print_token_er(data, 258, "`\"'\n"));
		data->tmp->value = ft_strjoin_free(data->tmp->value, lexer->value);
		lexer = lexer->next;
	}
	if (lexer->next && lexer->next->type == STRING)
		lexer = handle_string(data, lexer, 0);
	else if (lexer->next && lexer->next->type == DOLLAR)
		lexer = handle_dollar(data, lexer, 0, 1);
	else if (lexer->next && lexer->next->type == D_QUOT)
		lexer = handle_d_quote(data, lexer->next->next->next, 0);
	else if (lexer->next && lexer->next->type == S_QUOT)
		lexer = handle_s_quote(data, lexer->next, 1);
	if (sep != 1)
			data -> tmp -> value = ft_strjoin_free(data->tmp->value, "\n");
	return (lexer);
}

t_exec	*handle_d_quote(t_data *data, t_exec *lexer, int sep)
{
	if (lexer -> next)
		lexer = lexer->next;
	while (lexer -> type != D_QUOT)
	{
		if (!lexer)
			return (print_token_er(data, 258, "`\"'\n"));
		if (lexer->type == DOLLAR)
			lexer = handle_dollar(data, lexer, 1, 1);
		else
			data->tmp->value = ft_strjoin_free(data->tmp->value, lexer->value);
		lexer = lexer->next;
	}
	if (lexer->next && lexer->next->type == STRING)
		lexer = handle_string(data, lexer, 1);
	else if (lexer->next && lexer->next->type == DOLLAR)
		lexer = handle_dollar(data, lexer->next, 1, 1);
	else if (lexer->next && lexer->next->type == D_QUOT)
		lexer = handle_d_quote(data, lexer->next, 1);
	else if (lexer->next && lexer->next->type == S_QUOT)
		lexer = handle_s_quote(data, lexer->next, 1);
	if (sep != 1)
			data -> tmp -> value = ft_strjoin_free(data->tmp->value, "\n");
	return (lexer);
}

t_exec	*handle_pipe(t_data *data, t_exec *lexer)
{
	if (check_pipe(lexer) == 1)
		return (print_token_er(data, 258, "`|'\n"));
	if (data -> tmp -> value)
	{
		ft_lstadd_back_exec(&data->exec, \
		ft_lstnew_exec(data -> tmp->value, PIPE, copy_f(data -> tmp_f), lexer));
		free_file(&data -> tmp_f);
		free_exec(&data -> tmp);
		data -> tmp = ft_lstnew_exec("\n", STRING, data -> tmp_f, lexer);
		data -> tmp_f = NULL;
	}
	return (lexer);
}
