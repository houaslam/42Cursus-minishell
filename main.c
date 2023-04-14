/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:34:20 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/13 23:58:14 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(t_data *data)
{
	int	i;

	i = 0;
	data->exec = NULL;
	data->join = NULL;
	data->file = NULL;
	while (data->s[i])
	{
		if (data->s[i] == RED_IN && data->s[i + 1] == RED_IN)
			i = handle_here_doc_in(data, i);
		else if (data->s[i] == RED_OUT && data->s[i + 1] == RED_OUT)
			i = handle_here_doc_out(data, i);
		else if (data->s[i] == RED_IN)
			i = handle_redin(data, i);
		else if (data->s[i] == RED_OUT)
			i = handle_redout(data, i);
		else if (data->s[i] == PIPE)
			i = handle_pipe(data, i);
		else if (data->s[i] == '$')
			i = handle_dollar_sign(data, i);
		else
			i = handle_string(data, i);
		i++;
		if (data->s[i] == '\0')
		{
			if (data->join)
				ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(data->join, PIPE));
		}
	}
	aff1(data->exec);
	aff2(data->file);
}

int	main(int ac, char **av, char **en)
{
	t_data	*data;

	(void)av;
	if (ac == 1)
	{
		data = malloc(sizeof(t_data));
		data->exec = malloc(sizeof(t_exec));
		data->file = malloc(sizeof(t_file));
		creat_env(en, &data);
		while (1)
		{
			data->s = readline("minishell>");
			if (!data->s)
				exit(0);
			add_history(data->s);
			lexer(data);
			free(data->s);
			free_exec(&data->exec);
		}
	}
}
