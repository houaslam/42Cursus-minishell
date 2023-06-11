/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:50:42 by aatki             #+#    #+#             */
/*   Updated: 2023/06/10 00:47:42 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	here(char **env, char *arg)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (arg && !ft_strncmp(env[i], arg, ft_strlen(arg)))
			return (1);
		i++;
	}
	return (0);
}

char	**ft_envo(char **env)
{
	char	**menv;
	int		i;

	i = 0;
	while (env[i])
		i++;
	menv = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		menv[i] = ft_strdup(env[i]);
		i++;
	}
	menv[i] = NULL;
	return (menv);
}

void	ft_env(char **env, int fd, char **arg)
{
	int	i;

	i = 0;
	(void)fd;
	if (!here(env, "PATH=/Users/aatki/.brew/"))
		ft_errorb("bash: env: No such file or directory", NULL, NULL, 127);
	if (*arg)
	{
		return ;
		ft_errorb("there is an argument\n", NULL, NULL, 1);
	}
	if (!*env)
		return ;
	while (*env && env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
