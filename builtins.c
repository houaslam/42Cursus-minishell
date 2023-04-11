/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 05:24:12 by aatki             #+#    #+#             */
/*   Updated: 2023/04/11 02:27:09 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_envo(char **env)
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

void	sort_env(char **env)
{
	int i = 0;
	char *change;
	while ((env[i]))
	{
		if(env[i+1] && env[i][0] > env[i+1][0])
		{
			change=ft_strdup(env[i]);
			env[i]=ft_strdup(env[i+1]);
			env[i+1]=ft_strdup(change);
			free(change);
			i=0;
		}
		i++;
	}
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

int here(char **env,char *arg)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if(arg && arg[ft_strlen(arg)-1]=='=' && !ft_strncmp(env[i],arg,ft_strlen(arg)))
		return (1);
		i++;
	}
	return 0;
}

void	ft_export(char **env, char *arg,int fd)
{
	int	i;

	i = 0;
	char **export=ft_envo(env);
	sort_env(export);
	dup2(fd, 1);
	char **sp;
	if(arg)
		sp=ft_split(arg,'=');
	sp[0]=ft_strjoin(sp[0],"=");
	if(arg && !here(export,sp[0]))
		ft_error("No such file or directory");
	char **sp2;
	while (export[i])
	{
		sp2=ft_split(export[i],'=');
		if(arg && here(export,sp[0]) && !ft_strncmp(export[i],sp[0],ft_strlen(sp[0])))
		{
			printf("declare -x %s=\"%s\"\n", sp[0],sp[1]);
			i++;
		}
		printf("declare -x %s=\"%s\"\n", sp2[0],sp2[1]);
		//ft_free(sp2);
		i++;
	}
}

void	ft_env(char **env, char *arg,int fd)
{
	int	i;

	i = 0;
	dup2(fd, 1);
	char **sp;
	if(arg)
		sp=ft_split(arg,'=');
	if(arg && !here(env,sp[0]))
		ft_error("No such file or directory");
	while (env[i])
	{
		if(arg && here(env,sp[0]) && !ft_strncmp(env[i],sp[0],ft_strlen(sp[0])))
		{
			printf("%s\n",arg);
			i++;
		}
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
