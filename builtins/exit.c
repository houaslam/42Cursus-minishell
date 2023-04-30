/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:50:27 by aatki             #+#    #+#             */
/*   Updated: 2023/04/30 12:25:34 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_errorb(char *s, char *s1, char *s2, int ext)
{
	char	*t[2];

	t[0]=ft_itoa(ext);
	t[1]=NULL;
	if(s)
	write(2, s, ft_strlen(s));
	if(s1)
	write(2, s1, ft_strlen(s1));
	if(s2)
	write(2, s2, ft_strlen(s2));
	ft_exit(t);
}

void	ft_exit(char **arg)
{
	int	ext;

	if (!arg[0])
		exit(0);
	if (arg[1])
	{
		write(2,"exit: too many arguments\n",25);
		g_exit_status=1;
		return;
	}
	ext = atoi(arg[0]);
	g_exit_status = ext;
	exit(ext);
}
