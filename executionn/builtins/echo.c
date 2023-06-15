/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:50:45 by aatki             #+#    #+#             */
/*   Updated: 2023/06/14 23:50:49 by aatki            ###   ########.fr       */
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

void	ft_echo(char **arg, int fd, char **env)
{
	int	i;

	(void)env;
	(void)fd;
	i = 0;
	if (*arg && !ft_strcmp(arg[0], "-n"))
		i++;
	while (arg[i])
	{
		write(1, arg[i], ft_strlen(arg[i]));
		i++;
		write(1, " ", 1);
	}
	if (*arg && !ft_strcmp(arg[0], "-n"))
		return ;
	write(1, "\n", 1);
}
