/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 07:01:30 by aatki             #+#    #+#             */
/*   Updated: 2023/05/01 12:54:26 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	util_fun(char **env, char *buff)
{
	int		i;
	char	buff2[1024];

	i = 0;
	if (!getcwd(buff2, 1024))
		ft_errorb("no path1\n", NULL, NULL, 1);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			free(env[i]);
			env[i] = ft_strjoin("PWD=", buff2);
		}
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", buff);
		}
		i++;
	}
	// free(buff);
	// free(buff2);
}

char *telda(char *s)
{
	int i=0;
	char *r;
	char *l;
	while(s[i])
	{
		if(s[i]=='~')
		{
			r=ft_strjoin(ft_substr(s,0,i),"/Users/aatki");
			l=s;
			s=ft_strjoin(r,s+i+1);
			//free(l);
			break;
		}
		i++;
	}
	return s;
}

void	ft_cd(char **env, char **export, char **arg)
{
	int		i;
	char	buff[1024];
	char	*dir=NULL;

	i = 0;
	if (arg[0] && arg[1])
		ft_errorb("cd: string not in pwd: ", arg[0], "\n", 1);
	if (!arg[0])
		dir = ft_strdup("/Users/aatki");
	else
		dir=ft_strdup(arg[0]);
	dir=telda(dir);
	if (!getcwd(buff, 1024))
		ft_errorb("no path1\n", NULL, NULL, 1);
	if (chdir(dir))
		ft_errorb("bash: cd: ", dir, ": No such file or directory\n", 1);
	util_fun(env, buff);
	util_fun(export, buff);
	//free(buff);
	free(dir);
	//ft_free(arg);
}
