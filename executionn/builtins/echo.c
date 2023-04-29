/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:50:45 by aatki             #+#    #+#             */
/*   Updated: 2023/04/26 09:08:36 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "builtins.h"

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

void	ft_echo(char **s, int fd, char **env)
{
	int	i;

	(void)fd;
	//dup2(fd, 1);
	i = 0;
	if (!ft_strncmp(s[0], "-n", 2))
		i++;
	while (s[i])
	{
		if (s[i][0] == '$')
		{
			if(s[i][1]=='?')
				printf("%d",exit_status);	
			if (s[i][1] == '\'' || s[i][1] == '\"')
				printf("%s", s[i] + 2);
			else
				found(s[i] + 1, env);
		}
		else
			printf("%s", s[i]);
		i++;
		printf(" ");
	}
	if (ft_strncmp(s[0], "-n", 2))
		printf("\n");
}
