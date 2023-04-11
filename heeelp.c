/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heeelp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 02:33:24 by aatki             #+#    #+#             */
/*   Updated: 2023/04/11 03:11:07 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	here(char **env, char *arg)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (arg && arg[ft_strlen(arg) - 1] == '=' && !ft_strncmp(env[i], arg,
				ft_strlen(arg)))
			return (1);
		i++;
	}
	return (0);
}

void	found(char *sa, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], sa, ft_strlen(sa)))
			printf("%s", env[i] + ft_strlen(sa) + 1);
		i++;
	}
	return ;
}

void	sort_env(char **env)
{
	int		i;
	char	*change;

	i = 0;
	while ((env[i]))
	{
		if (env[i+1]&& ft_strncmp(env[i],env[i+1],ft_strlen(env[i]))==1)
		{
			change = ft_strdup(env[i]);
			env[i] = ft_strdup(env[i + 1]);
			env[i + 1] = ft_strdup(change);
			free(change);
			i = -1;
		}
		i++;
	}
}

char	**ft_envo(char **env)
{
	char	**menv;
	int		i;

	i = 0;
	while (env[i])
	{
		i++;
	}
	menv = malloc(sizeof(char *) * i + 2);
	i = 0;
	while (env[i])
	{
		menv[i] = ft_strdup(env[i]);
		i++;
	}
    env[i]=NULL;
	return (menv);
}
