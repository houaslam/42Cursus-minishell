/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 07:01:30 by aatki             #+#    #+#             */
/*   Updated: 2023/04/29 16:31:17 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void util_fun(char **env,char *dir,char *buff)
{
	int i=0;
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
}

void	ft_cd(char **env, char **export,char **dir)
{
	int	i;
	char	buff[1024];
	(void)dir;
	i = 0;
	if(dir[1])
		ft_errorb("cd: string not in pwd: \n",dir[0],NULL,1);
	if (!getcwd(buff, 1024))
		ft_errorb("no path\n",NULL,NULL,1);
	if(!chdir(dir[0]))
		ft_errorb("no path\n",NULL,NULL,1);
	util_fun(env,dir[0],buff);
	util_fun(export,dir[0],buff);
}
