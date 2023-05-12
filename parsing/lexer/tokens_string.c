/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 20:49:13 by houaslam          #+#    #+#             */
/*   Updated: 2023/05/12 13:27:42 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *find_ex(char *sa, char **env)
{
    int    i;

    i = 0;
    char *s = NULL;
    while (env[i])
    {
        if (!ft_strncmp(env[i], sa, ft_strlen(sa))
            && env[i][ft_strlen(sa)] == '=')
            s=ft_substr(env[i], ft_strlen(sa) + 1,ft_strlen(env[i]) - ft_strlen(sa));
        i++;
    }
    return s;
}

t_exec	*handle_dollar(t_data *data, t_exec *lexer)
{
	char	*str;

	str = ft_substr(lexer->value, 1, ft_strlen(lexer->value) - 1);
	if (data -> d_status % 2 == 0 && data -> s_status % 2 != 0)
	{
		data -> tmp -> value = ft_strjoin_free(data->tmp->value, lexer->value);
		data -> tmp -> value = ft_strjoin_free(data->tmp->value, "@");
	}
	else
	{
		free(str);
		str = find_ex(ft_substr(lexer->value, 1, ft_strlen(lexer->value) - 1), data->env);
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
	{
		if (!lexer)
			return (print_token_er(data, 258, "`\"'\n"));
		if (lexer -> type == DOLLAR)
			lexer = handle_dollar(data, lexer);
		else
			data->tmp->value = ft_strjoin(data->tmp->value, lexer->value);
		lexer = lexer->next;
	}
	if (lexer->next && lexer->next->type == STRING)
		lexer = handle_string(data, lexer);
	data -> tmp->value = ft_strjoin_free(data -> tmp -> value, "@");
	return (lexer);
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
