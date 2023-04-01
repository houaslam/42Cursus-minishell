/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:34:20 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/01 21:49:32 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **en)
{
	t_data	*data;

	(void)av;
	if (ac == 1)
	{
		data = malloc(sizeof(t_data));
		creat_env(en, &data);
		data = malloc(sizeof(t_data));
		while (1)
		{
			write(1, "minishell> ", 11);
			data->string = get_next_line(0);
			if (!data->string)
				exit(1);
			printf("%s\n", data->string);
			// lexer(data);
			free(data->string);
		}
	}
}

// void	lexer(t_data *data)