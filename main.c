/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:34:20 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/16 12:17:04 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(t_data *data)
{
	int		i;
	t_exec	*tmp;

	i = 0;
	data->exec = NULL;
	tmp = ft_lstnew_exec("*", STRING);
	tmp->file = NULL;
	while (data->s[i])
	{
		if (data->s[i] == RED_IN && data->s[i + 1] == RED_IN)
			i = handle_here_doc_in(data, i, tmp);
		else if (data->s[i] == RED_OUT && data->s[i + 1] == RED_OUT)
			i = handle_here_doc_out(data, i, tmp);
		else if (data->s[i] == RED_IN)
			i = handle_redin(data, i, tmp);
		else if (data->s[i] == RED_OUT)
			i = handle_redout(data, i, tmp);
		else if (data->s[i] == PIPE)
			i = handle_pipe(data, i, tmp);
		else
			i = handle_string(data, i, tmp);
		if (data->s[i] == '\0')
			ft_lstadd_back_exec(&data->exec, tmp);
		i++;
	}
	aff1(data->exec, data->exec->file);
}

int	main(int ac, char **av, char **en)
{
	t_data	*data;

	(void)en;
	(void)av;
	if (ac == 1)
	{
		data = malloc(sizeof(t_data));
		while (1)
		{
			data->s = readline("minishell>");
			add_history(data->s);
			lexer(data);
			free(data->s);
			// free_exec(&data->exec);
		}
	}
}
