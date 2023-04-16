/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:34:20 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/16 06:18:56 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	lexer(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	data->join = NULL;
// 	data->pipe = 0;
// 	while (data->s[i])
// 	{
// 		if (data->s[i] == RED_IN && data->s[i + 1] == RED_IN)
// 			i = handle_here_doc_in(data, i);
// 		else if (data->s[i] == RED_OUT && data->s[i + 1] == RED_OUT)
// 			i = handle_here_doc_out(data, i);
// 		else if (data->s[i] == RED_IN)
// 			i = handle_redin(data, i);
// 		else if (data->s[i] == RED_OUT)
// 			i = handle_redout(data, i);
// 		else if (data->s[i] == PIPE)
// 			i = handle_pipe(data, i);
// 		else
// 			i = handle_string(data, i);
// 		i++;
// 		// if (data->s[i] == '\0')
// 		// 	ft_lstadd_back_exec(&data->exec, ft_lstnew_exec(data->join, STRING));
// 	}
// 	// aff1(data->exec, data->exec->file);
// }

void	lexer(t_data *data)
{
	int		i;
	t_exec	*tmp;

	i = 0;
	data->exec = NULL;
	tmp = ft_lstnew_exec("*", STRING);
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
			i = handle_pipe(data, i, tmp);
		else
			i = handle_string(data, i, tmp);
		if (data->s[i] == '\0')
		{
			ft_lstadd_back_exec(&data->exec, tmp);
			printf("KAYDKHEL %s\n", data->exec->value);
			printf("KAYDKHEL %s\n", data->exec->next->value);
		}
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
		data->exec = malloc(sizeof(t_exec));
		// data->exec->file = malloc(sizeof(t_file));
		// creat_env(en, &data);
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
