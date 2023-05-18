/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:50:45 by aatki             #+#    #+#             */
/*   Updated: 2023/05/13 11:01:16 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	found(char *sa, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], sa, ft_strlen(sa))&& env[i][ft_strlen(sa)]=='=')
			printf("%s", env[i] + ft_strlen(sa) + 1);
		i++;
	}
	return ;
}

void	ft_echo(char **arg, int fd, char **env)
{
	int	i;

	(void)fd;
	//dup2(fd, 1);
	i = 0;
	if (*arg && !ft_strncmp(arg[0], "-n", 2))
		i++;
	while (arg[i])
	{
		if (arg[i][0] == '$')
		{
			printf("YESS\n");
			if(arg[i][1]=='?')
				printf("%d",g_exit_status);
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
	if (*arg && !ft_strncmp(arg[0], "-n", 2))
		return;
		printf("\n");
	//ft_free(arg);
}
