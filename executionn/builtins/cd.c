/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 07:01:30 by aatki             #+#    #+#             */
/*   Updated: 2023/06/17 13:35:27 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	util_fun(char **env, char *buff, char **export)
{
	int		i;
	char	buff2[1024];

	i = 0;
	if (!getcwd(buff2, 1024))
	{
		ft_errorb("no path1\n", NULL, NULL, 1);
		return ;
	}
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
	if (export)
		util_fun(export, buff, NULL);
}

char	*telda(char *s)
{
	int		i;
	char	*r;
	char	*l;

	i = 0;
	while (s[i])
	{
		if (s[i] == '~')
		{
			r = ft_strjoin_free(ft_substr(s, 0, i), "/Users/houaslam");
			l = s;
			s = ft_strjoin_free(r, s + i + 1);
			free(l);
			break ;
		}
		i++;
	}
	return (s);
}

int	ft_cd(char **env, char **export, char **arg)
{
	int		i;
	char	buff[1024];
	char	*dir;

	i = 0;
	if (arg[0] && arg[1])
		return (ft_errorb("cd: ", arg[0], " No such file or directory \n", 1));
	if (!arg[0])
		dir = ft_strdup("/Users/houaslam");
	else
		dir = ft_strdup(arg[0]);
	dir = telda(dir);
	if (!getcwd(buff, 1024))
	{
		ft_errorb("bash: cd: ", dir, ": No such file or directory\n", 1);
		free(dir);
		return (0);
	}
	if (chdir(dir))
		ft_errorb("bash: cd: ", dir, ": No such file or directory\n", 1);
	else
		util_fun(env, buff, export);
	free(dir);
	return (0);
}
