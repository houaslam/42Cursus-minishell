/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:34:20 by houaslam          #+#    #+#             */
/*   Updated: 2023/03/14 22:37:56 by houaslam         ###   ########.fr       */
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
		j = -1;
		tmp->ptr = malloc(sizeof(char) * strlen(en[i]));
		while (en[i][++j])
		{
			tmp->ptr[j] = en[i][j];
			printf("%c", en[i][j]);
		}
		printf("\n");
		tmp = tmp->next;
		i++;
		printf("here\n");
	}
}

int	main(int ac, char **av, char **en)
{
	t_env	*env;

	if (ac == 1)
	{
		creat_env(en, env);
		while (env)
		{
			printf("%s\n", env->ptr);
			env = env->next;
		}
		// minishell(ac, av, env);
	}
}
