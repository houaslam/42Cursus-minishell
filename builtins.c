/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 05:24:12 by aatki             #+#    #+#             */
/*   Updated: 2023/04/12 02:28:58 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**equal(char *s, char c)
{
	char	**sp;
	int		i;

	sp = malloc(sizeof(char *) * 2);
	i = 0;
	sp[0] = malloc(ft_strlen(s));
	// sp[0][ft_strlen(s)-1]='\0';
	while (s[i])
	{
		sp[0][i] = s[i];
		if (s[i] == '=')
		{
			sp[0][i + 1] = '\0';
			// free(sp[0]+i+2);
			break ;
		}
		i++;
	}
	sp[1] = ft_strchr(s, c) + 1;
	return (sp);
}

void	ft_export(char **env, char *arg, int fd, char *plus)
{
	int		i;
	char	**export;
	char	**sp;
	char	**sp2;

	i = 0;
	export = ft_envoo(env, plus);
	sort_env(export);
	dup2(fd, 1);
	if (arg)
		sp = equal(arg, '=');
	//sp[0] = ft_strjoin(sp[0], "=");
	if (arg && !here(export, sp[0]))
		ft_error("No such file or directory");
	while (export[i])
	{
		if (arg && here(export, sp[0]) && !ft_strncmp(export[i], sp[0],
				ft_strlen(sp[0])))
		{
			printf("declare -xx %s\"%s\"\n", sp[0], sp[1]);
			i++;
		}
		sp2 = equal(export[i], '=');
		printf("declare -x %s\"%s\"\n", sp2[0], sp2[1]);
		//ft_free(sp2, 2);
		i++;
	}
}

void	ft_env(char **env, char *arg, int fd)
{
	int		i;
	char	**sp;

	i = 0;
	dup2(fd, 1);
	if (arg)
		sp = equal(arg, '=');
	if (arg && !here(env, sp[0]))
		ft_error("No such file or directory");
	while (env[i])
	{
		if (arg && here(env, sp[0]) && !ft_strncmp(env[i], sp[0],
				ft_strlen(sp[0])))
		{
			printf("%s\n", arg);
			i++;
		}
		printf("%s\n", env[i]);
		i++;
	}
}

void	ft_pwd(int fd)
{
	char	buff[1024];

	dup2(fd, 1);
	if (getcwd(buff, 1024))
		printf("%s\n", buff);
	else
		ft_error("no path");
}

void	ft_unset(char **env, char *arg)
{
	int	i;

	i = 0;
	while ((env[i]))
	{
		if (arg && !ft_strncmp(env[i], arg, ft_strlen(arg)))
			break ;
		i++;
	}
	if (!env[i])
		return ;
	while ((env[i + 1]))
	{
		printf("vjkfdbh\n");
		free(env[i]);
		env[i] = ft_strdup(env[i + 1]);
		i++;
	}
	exit(0);
	env[i] = NULL;
	ft_env(env, NULL, 1);
}
