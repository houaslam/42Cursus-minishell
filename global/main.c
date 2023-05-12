/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:34:20 by houaslam          #+#    #+#             */
/*   Updated: 2023/05/11 13:38:45 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	ctrl_c(int i)
{
	if (i == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ctrl_d(int i)
{
	if (i == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit(0);
	}
}

// void	ctrl_slash(int i)
// {
	
// }

int	main(int ac, char **av, char **en)
{
	t_data	*data;
	char	**menv;
	char	**export;

	(void)av;
	if (ac == 1)
	{
		menv = ft_envo(en);
		export = ft_envo(en);
		sort_export(export);
		data = malloc(sizeof(t_data));
		data->g_exit_status = 0;
		data -> env = menv;
		// signal(SIGINT, ctrl_c);
		signal(SIGQUIT, ctrl_d);
		// signal(SIGTSTP, ctrl_slash);
		while (1)
		{
			data->s = readline("\e[92mMINISHELL>\e[0m");
			add_history(data->s);
			if (data->s[0] != '\0' && data->s)
			{
				lexer(&data);
				// if (data->g_exit_status == 0)
				// 	transmettre(data, &menv, &export);
				// free_file(&data->tmp_f);
				// free_exec(&data->tmp);
				// free_exec(&data->exec);
				free(data->s);
			}
			data->g_exit_status = 0;
		}
		ft_free(menv);
		ft_free(export);
	}
}
