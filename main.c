/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:34:20 by houaslam          #+#    #+#             */
/*   Updated: 2023/03/15 16:39:21 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	creat_env(char **en, t_env *env)
{
	t_env	*tmp;
	int		j;
	int		i;

	env = malloc(sizeof(t_env));
	i = 0;
	while (en[i])
	{
		j = 0;
		tmp->path = malloc(sizeof(en[i]));
		while (en[i][j])
		{
			tmp->path[j] = en[i][j];
			printf("%c", en[i][j]);
			j++;
		}
		printf("\n");
		tmp = tmp->next;
		i++;
		printf("here\n");
	}
}

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
	}
}
