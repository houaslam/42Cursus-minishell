/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_spec_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:56:12 by houaslam          #+#    #+#             */
/*   Updated: 2023/05/12 15:28:27 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exec	*handle_here_doc_in(t_data *data, t_exec *lexer)
{
	char	*str;

	lexer = lexer->next;
	while (lexer->type == SPACE)
		lexer = lexer->next;
	if (data -> lexer ->type == STRING)
	{
		ft_lstadd_back_file(&data -> tmp_f, ft_lstnew_file \
		(data -> lexer->value, H_IN, 0));
		return (lexer);
	}
	else if (data -> lexer ->type == S_QUOT || data -> lexer ->type == D_QUOT)
	{
		str = ft_substr(lexer->value, 1, ft_strlen(lexer->value) - 1);
		ft_lstadd_back_file(&data -> tmp_f, ft_lstnew_file \
		(str, H_IN, 1));
		return (lexer);
	}
	else
		return (print_token_er(data, 258, "`newline'\n"));
}

t_exec	*handle_here_doc_out(t_data *data, t_exec *lexer)
{
	char	*str;

	lexer = lexer->next;
	while (lexer->type == SPACE)
		lexer = lexer->next;
	if (data -> lexer ->type == STRING)
	{
		ft_lstadd_back_file(&data -> tmp_f, ft_lstnew_file \
		(data -> lexer->value, H_OUT, 0));
		return (lexer);
	}
	else if (data -> lexer ->type == S_QUOT || data -> lexer ->type == D_QUOT)
	{
		str = ft_substr(lexer->value, 1, ft_strlen \
		(lexer->value) - 1);
		ft_lstadd_back_file(&data -> tmp_f, \
		ft_lstnew_file(str, H_OUT, 1));
		return (lexer);
	}
	else
		return (print_token_er(data, 258, "`newline'\n"));
}

t_exec	*handle_redout(t_data *data, t_exec *lexer)
{
	char	*str;

	lexer = lexer->next;
	while (lexer->type == SPACE)
		lexer = lexer->next;
	printf("|%s| == |%d|\n", lexer->value, lexer->type);
	if (lexer -> type == STRING)
	{
		ft_lstadd_back_file(&data -> tmp_f, \
		ft_lstnew_file(lexer->value, R_OUT, 0));
		return (lexer);
	}
	else if (lexer ->type == S_QUOT || lexer ->type == D_QUOT)
	{
		str = ft_substr(lexer->value, 1, \
		ft_strlen(lexer->value) - 1);
		ft_lstadd_back_file(&data -> tmp_f, ft_lstnew_file(str, R_OUT, 0));
		return (lexer);
	}
	else
		return (print_token_er(data, 258, "`newline'\n"));
}

t_exec	*handle_redin(t_data *data, t_exec *lexer)
{
	char	*str;

	lexer = lexer->next;
	while (lexer->type == SPACE)
		lexer = lexer->next;
	if (data -> lexer ->type == STRING)
	{
		ft_lstadd_back_file(&data -> tmp_f, \
		ft_lstnew_file(data -> lexer->value, R_IN, 0));
		return (lexer);
	}
	else if (data -> lexer ->type == S_QUOT || data -> lexer ->type == D_QUOT)
	{
		str = ft_substr(lexer->value, 1, \
		ft_strlen(lexer->value) - 1);
		ft_lstadd_back_file(&data -> tmp_f, ft_lstnew_file(str, R_IN, 0));
		return (lexer);
	}
	else
		return (print_token_er(data, 258, "`newline'\n"));
}

// int	handle_dollar(t_data *data, int i, int k)
// {
// 	char	*res;

// 	res = ft_substr(data->s, k, i - k);
// 	data -> tmp->value = ft_strjoin_free(data -> tmp->value, res);
// 	data -> tmp->value = ft_strjoin_free(data -> tmp->value, "@");
// 	data -> tmp->value = ft_strjoin_free(data -> tmp->value, "$");
// 	data -> tmp->value = ft_strjoin_free(data -> tmp->value, "@");
// 	k = i + 1;
// 	return (k);
// }
