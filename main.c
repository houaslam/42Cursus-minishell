/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:34:20 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/03 17:36:29 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(t_data *data)
{
	int	i;

	i = 0;
	data->exec = NULL;
	// printf("%lu\n", strlen(data->s));
	while (data->s[i])
	{
		// if (data->s[i] == RED_IN && data->s[i + 1] == RED_IN)
		// 	i += handle_here_doc_in(data, i);
		// else if (data->s[i] == RED_OUT && data->s[i + 1] == RED_OUT)
		// 	i += handle_here_doc_out(data, i);
		if (data->s[i] == RED_IN)
			i += handle_redin(data, i);
		else if (data->s[i] == RED_OUT)
			i += handle_redout(data, i);
		// else if (data->s[i] == PIPE)
		// 	i += handle_pipe(data, i);
		else if (data->s[i] == D_QUOT)
			i += handle_d_quote(data, i);
		else if (data->s[i] == S_QUOT)
			i += handle_s_quote(data, i);
		// if (data->s[i] >= 97 && data->s[i] <= 122)
			// i += handle_string(data, i);
		// printf("%d\n", i);
		i++;
	}
		aff1(data->exec);

}

// void	lexer(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->s[i])
// 	{
// 		if (data->s[i] >= 97 && data->s[i] <= 122)
// 			{printf("char\n");}
// 		else if (data->s[i] == PIPE)
// 			{printf("pipe\n");}
// 		else if (data->s[i] == RED_IN && data->s[i + 1] == RED_IN)
// 			{printf("here_doc\n"); i++;}
// 		else if (data->s[i] == RED_OUT && data->s[i + 1] == RED_OUT)
// 			{printf("here_doc\n"); i++;}
// 		else if (data->s[i] == RED_IN)
// 			{printf("red\n");}
// 		else if (data->s[i] == RED_OUT)
// 			{printf("red\n");}
		// i++;
// 	}
// }

int	main(int ac, char **av, char **en)
{
	t_data	*data;

	(void)av;
	if (ac == 1)
	{
		data = malloc(sizeof(t_data));
		data->exec = malloc(sizeof(t_exec));
		creat_env(en, &data);
		while (1)
		{
			write(1, "minishell> ", 11);
			data->s = get_next_line(0);
			if (!data->s)
				exit(0);
			lexer(data);
			free(data->s);
		}
	}
}
