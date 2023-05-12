/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:41:48 by houaslam          #+#    #+#             */
/*   Updated: 2023/05/12 15:29:02 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add(t_data **data, int *i, int type)
{
	int		k;
	char	*str;

	k = *i;
	(*i)++;
	while ((*data)->s[*i] && ft_isstring \
	((*data)->s[*i]) && (*data)->s[*i] != '$')
		(*i)++;
	str = ft_substr((*data)->s, k, *i - k);
	ft_lstadd_back_exec(&(*data)->lexer, \
	ft_lstnew_exec(str, type, NULL, (*data)->lexer));
	free(str);
	(*i)--;
}

void	the_lexer(t_data **data)
{
	static int	doubl;
	static int	singl;
	int			i;

	i = -1;
	while ((*data)->s[++i])
	{
		if ((*data)->s[i] == SPACE || (*data)->s[i] == TAB)
			ft_lstadd_back_exec(&(*data)->lexer, ft_lstnew_exec(" ", SPACE, NULL, (*data)->lexer));
		else if ((*data)->s[i] == PIPE)
			ft_lstadd_back_exec(&(*data)->lexer, ft_lstnew_exec("|", PIPE, NULL, (*data)->lexer));
		else if ((*data)->s[i] == R_IN && (*data)->s[i + 1] == R_IN && ++i)
			ft_lstadd_back_exec(&(*data)->lexer, ft_lstnew_exec("<<", H_IN, NULL, (*data)->lexer));
		else if ((*data)->s[i] == R_OUT && (*data)->s[i + 1] == R_OUT && ++i)
			ft_lstadd_back_exec(&(*data)->lexer, ft_lstnew_exec(">>", H_OUT, NULL, (*data)->lexer));
		else if ((*data)->s[i] == R_OUT)
			ft_lstadd_back_exec(&(*data)->lexer, ft_lstnew_exec(">", R_OUT, NULL, (*data)->lexer));
		else if ((*data)->s[i] == R_IN)
			ft_lstadd_back_exec(&(*data)->lexer, ft_lstnew_exec("<", R_IN, NULL, (*data)->lexer));
		else if ((*data)->s[i] == D_QUOT && ++doubl)
			ft_lstadd_back_exec(&(*data)->lexer, ft_lstnew_exec("\"", D_QUOT, NULL, (*data)->lexer));
		else if ((*data)->s[i] == S_QUOT && ++singl)
			ft_lstadd_back_exec(&(*data)->lexer, ft_lstnew_exec("\'", S_QUOT, NULL, (*data)->lexer));
		else if ((*data)->s[i] == DOLLAR)
		{
			(*data)-> d_status = doubl;
			(*data)-> s_status = singl;
			add(data, &i, DOLLAR);
		}
		else
			add(data, &i, DOLLAR);
	}
	if (singl %2 != 0 || doubl %2 != 0)
		print_token_er(*data, 285, "'\"`\n");
	aff1((*data)->lexer, NULL);
}

void	options(t_data *data)
{
	while (data->lexer)
	{
		if (data -> lexer -> type == H_IN)
			data->lexer = handle_here_doc_in(data, data->lexer);
		else if (data -> lexer -> type == H_OUT)
			data->lexer = handle_here_doc_out(data, data->lexer);
		else if (data -> lexer -> type == R_IN)
			data->lexer = handle_redin(data, data->lexer);
		else if (data -> lexer -> type == R_OUT)
			data->lexer = handle_redout(data, data->lexer);
		else if (data -> lexer -> type == PIPE)
			data->lexer = handle_pipe(data, data->lexer);
		else if (data -> lexer -> type == S_QUOT)
			data->lexer = handle_s_quote(data, data->lexer);
		else if (data -> lexer -> type == D_QUOT)
			data->lexer = handle_d_quote(data, data->lexer);
		else if (data -> lexer -> type == STRING)
			data->lexer = handle_string(data, data->lexer);
		else if (data -> lexer -> type == DOLLAR)
			data->lexer = handle_dollar(data, data->lexer);
		if (!data->lexer->next && data->g_exit_status == 0)
			ft_lstadd_back_exec(&data->exec, \
			ft_lstnew_exec(data->tmp->value, STRING, data->tmp_f, data->lexer));
		data -> lexer = data -> lexer -> next;
	}
}

void	lexer(t_data **data)
{
	(*data)->lexer = NULL;
	the_lexer(data);
	(*data)->exec = NULL;
	(*data)->f = 0;
	(*data)->tmp_f = NULL;
	(*data)->tmp = ft_lstnew_exec("@", STRING, NULL, NULL);
	(*data)->tmp->file = NULL;
	if ((*data)->g_exit_status == 0)
		options(*data);
}
