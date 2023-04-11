/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 05:24:12 by aatki             #+#    #+#             */
/*   Updated: 2023/04/11 00:16:38 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_env(char **env)
{
	char **menv;
	int i=0;

	while(env[i])
	{
		i++;
	}
	menv=malloc(sizeof(char *)*i);
	i=0;
	while(env[i])
	{
		menv[i]=ft_strdup(env[i]);
		i++;
	}
	return menv;
}

void	ft_cd(char **env, char *dir)
{
	int	i;
	char	buff[1024];

	i = 0;
	printf("%s>>>\n", dir);
	if (!getcwd(buff, 1024))
		ft_error("no path");
	while (env[i])
	{
		if(!ft_strncmp(env[i],"PWD=",4))
		{
			env[i]=ft_strjoin("PWD=",dir);
			printf("%s\n", env[i]);
		}
		if(!ft_strncmp(env[i],"OLDPWD=",7))
		{
			env[i]=ft_strjoin("OLDPWD=",buff);
			printf("%s\n", env[i]);
		}
		i++;
	}
	//ft_env(env,1);
}

void	ft_cdi(char *dir)
{
	if (!chdir(dir))
	{
        ft_pwd(1);
	}
	else
		ft_error("error in chdir");
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

void	ft_echo(char **s, int fd, char **env)
{
	int	i;

	dup2(fd, 1);
	// char **s=ft_split(str,' ');
	i = 1;
	if (!ft_strncmp(s[0], "-n", 2))
		i++;
	while (s[i])
	{
		if (s[i][0] == '$')
		{
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

void	ft_env(char **env, int fd)
{
	int	i;

	i = 0;
	dup2(fd, 1);
	while (env[i])
	{
		printf("declare -x");
		printf("%s\n", env[i]);
		i++;
	}
}

void    ft_pwd(int fd)
{
	char	buff[1024];

	dup2(fd, 1);
	if (getcwd(buff, 1024))
		printf("%s\n", buff);
	else
		ft_error("no path");
}

void	ft_exit(int e)
{
	exit(e);
}
