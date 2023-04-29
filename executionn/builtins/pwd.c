

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*           pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 05:24:12 by aatki             #+#    #+#             */
/*   Updated: 2023/04/17 00:57:02 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_pwd(int fd,char **env)
{
	char	buff[1024];
	char *arg[]={"$PWD",NULL};
	(void)arg;
	(void)env;
	(void)fd;
	ft_echo(arg,fd,env);
	if (getcwd(buff, 1024))
		printf("%s\n", buff);
	else
		ft_errorb("no path",NULL,NULL,4);
}
