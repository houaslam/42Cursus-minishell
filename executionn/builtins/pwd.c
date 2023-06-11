/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 05:24:12 by aatki             #+#    #+#             */
/*   Updated: 2023/05/08 23:11:38 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_pwd(int fd)
{
	char	buff[1024];
	char	*arg[2];

	arg[0] = "$PWD";
	arg[1] = NULL;
	(void)fd;
	if (getcwd(buff, 1024))
		printf("%s\n", buff);
	else
		ft_errorb("no path\n", NULL, NULL, 4);
}
