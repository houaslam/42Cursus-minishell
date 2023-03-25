/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:34:20 by houaslam          #+#    #+#             */
/*   Updated: 2023/03/25 13:00:31 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **en)
{
	(void)av;
	t_env	*env;

	if (ac == 1)
	{
		env = NULL;
		creat_env(en, env);
		while (env)
		{
			printf("%s\n", env->path);
			printf("%s\n", env->next->path);
			env = env->next;
		}
		// minishell(ac, av, env);
		aff(env);

	}
}
