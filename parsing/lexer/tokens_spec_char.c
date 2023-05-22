/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_spec_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:56:12 by houaslam          #+#    #+#             */
/*   Updated: 2023/05/22 15:53:01 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_exec	*handle_here_doc_in(t_data *data, t_exec *lexer)
{
	char	*str;

	lexer = lexer->next;
	while (lexer->type == SPACE)
		lexer = lexer->next;
	if (lexer ->type == STRING)
	{
		ft_lstadd_back_file(&data -> tmp_f, ft_lstnew_file \
		(lexer->value, H_IN, 0));
		return (lexer);
	}
	else if (lexer ->type == S_QUOT || lexer ->type == D_QUOT)
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
	if (lexer ->type == STRING)
	{
		ft_lstadd_back_file(&data -> tmp_f, ft_lstnew_file \
		(lexer->value, H_OUT, 0));
		return (lexer);
	}
	else if (lexer ->type == S_QUOT || lexer ->type == D_QUOT)
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

	if (lexer -> next)
		lexer = lexer->next;
	while (lexer && lexer->type == SPACE)
		lexer = lexer->next;
	if (lexer && lexer -> type == STRING)
	{
		ft_lstadd_back_file(&data -> tmp_f, \
		ft_lstnew_file(lexer->value, R_OUT, 0));
		return (lexer);
	}
	else if (lexer && (lexer ->type == S_QUOT || lexer ->type == D_QUOT))
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
	if (lexer ->type == STRING)
	{
		ft_lstadd_back_file(&data -> tmp_f, \
		ft_lstnew_file(data -> lexer->value, R_IN, 0));
		return (lexer);
	}
	else if (lexer ->type == S_QUOT || lexer ->type == D_QUOT)
	{
		str = ft_substr(lexer->value, 1, \
		ft_strlen(lexer->value) - 1);
		ft_lstadd_back_file(&data -> tmp_f, ft_lstnew_file(str, R_IN, 0));
		return (lexer);
	}
	else
		return (print_token_er(data, 258, "`newline'\n"));
}

int	check_pipe(t_exec *lexer)
{
	t_exec	*tmp;

	tmp = lexer;
	while (tmp)
	{
		if (tmp->type == STRING)
			return (0);
		if (tmp->prev == NULL)
			return (1);
		tmp = tmp->prev;
	}
	tmp = lexer;
	while (tmp)
	{
		if (tmp->type == STRING)
			return (0);
		if (tmp->next == NULL)
			return (1);
		tmp = tmp->next;
	}
	return (1);
}
