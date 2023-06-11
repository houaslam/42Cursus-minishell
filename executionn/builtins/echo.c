/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:50:45 by aatki             #+#    #+#             */
/*   Updated: 2023/06/08 22:53:30 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	found(char *sa, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], sa, ft_strlen(sa))
			&& env[i][ft_strlen(sa)] == '=')
			printf("%s", env[i] + ft_strlen(sa) + 1);
		i++;
	}
	return ;
}

// char *found(char *sa, char **env)
// {
// 	int	i;

// 	i = 0;
// 	char *s;
// 	while (env[i])
// 	{
// 		if (!ft_strncmp(env[i], sa, ft_strlen(sa))
// 			&& env[i][ft_strlen(sa)] == '=')
// 			s=ft_strdup(env[i]);
// 		i++;
// 	}
// 	return s;
// }

void	ft_echo(char **arg, int fd, char **env)
{
	int	i;

	(void)fd;
	i = 0;
	if (*arg && !ft_strcmp(arg[0], "-n"))
		i++;
	while (arg[i])
	{
		if (arg[i][0] == '$')
		{
			if (arg[i][1] == '?')
				printf("%d", g_exit_status);
			if (arg[i][1] == '\'' || arg[i][1] == '\"')
				printf("%s", arg[i] + 2);
			else
				found(arg[i] + 1, env);
		}
		else
			printf("%s", arg[i]);
		i++;
		printf(" ");
	}
	if (*arg && !ft_strcmp(arg[0], "-n"))
		return ;
	printf("\n");
}
