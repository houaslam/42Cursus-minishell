/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:49:13 by houaslam          #+#    #+#             */
/*   Updated: 2023/06/13 13:52:56 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exec	*handle_s_quote(t_data *data, t_exec *lexer, int sep)
{
	data->s_status++;
	if (lexer -> next)
		lexer = lexer->next;
	while (lexer -> type != S_QUOT)
	{
		if (!lexer)
			return (print_token_er(data, 258, "`\"'\n"));
		data->tmp->value = ft_strjoin_free(data->tmp->value, lexer->value);
		lexer = lexer->next;
	}
	data->s_status++;
	lexer = next_case(data, lexer);
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

t_exec	*handle_d_quote(t_data *data, t_exec *lexer, int sep)
{
	data->d_status++;
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
	data->d_status++;
	lexer = next_case(data, lexer);
	if (sep != 1)
			data -> tmp -> value = ft_strjoin_free(data->tmp->value, "\n");
	return (lexer);
}

t_exec	*handle_dollar(t_data *data, t_exec *lexer, int sep, int is_red)
{
	char	**str;
	int		k;

	str = ft_split(lexer->value, ' ');
	k = 0;
	while (str[k])
		k++;
	if (k > 1)
	{
		if (is_red == 0)
			print_token_er(data, 1, " ambiguous redirect\n");
		k = -1;
		while (str[++k])
		{
			data->tmp->value = ft_strjoin_free(data->tmp->value, str[k]);
			data -> tmp -> value = ft_strjoin_free(data->tmp->value, "\n");
		}
	}
	else
		data->tmp->value = ft_strjoin_free(data->tmp->value, lexer->value);
	if (data->d_status % 2 == 0 || data->d_status == 0)
		lexer = next_case(data, lexer);
	if (sep != 1)
		data -> tmp -> value = ft_strjoin_free(data->tmp->value, "\n");
	return (lexer);
}

t_exec	*handle_string(t_data *data, t_exec *lexer, int sep)
{
	data -> tmp -> value = ft_strjoin_free(data->tmp->value, lexer->value);
	lexer = next_case(data, lexer);
	if (sep != 1)
		data -> tmp -> value = ft_strjoin_free(data->tmp->value, "\n");
	return (lexer);
}
