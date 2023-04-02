/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:34:20 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/02 18:02:35 by houaslam         ###   ########.fr       */
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
		while (1)
		{
			write(1, "minishell> ", 11);
			data->s = get_next_line(0);
			if (!data->s)
				exit(0);
			printf("%s\n", data->s);
			lexer(data);
			free(data->s);
		}
	}
}

void	lexer(t_data *data)
{
	int	i;

	i = 0;
	while (data->s[i])
	{
		if (data->s[i] >= 97 && data->s[i] <= 122)
			i += handle_string(data->s);
		else if (data->s[i] == PIPE)
			i += handle_special(data->s);
	}
}