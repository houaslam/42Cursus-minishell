/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 07:01:30 by aatki             #+#    #+#             */
/*   Updated: 2023/04/30 13:34:28 by aatki            ###   ########.fr       */
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
			env[i] = ft_strjoin("PWD=", buff2);
		}
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
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
	while(s[i])
	{
		if(s[i]=='~')
		{
			r=ft_strjoin(ft_substr(s,0,i),"/Users/aatki");
			s=ft_strjoin(r,s+i+1);
			//free(r);
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
		dir=arg[0];
	dir=telda(dir);
	if (!getcwd(buff, 1024))
		ft_errorb("no path1\n", NULL, NULL, 1);
	if (chdir(dir))
		ft_errorb("bash: cd: ", dir, ": No such file or directory\n", 1);
	util_fun(env, buff);
	util_fun(export, buff);
}
