/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:50:27 by aatki             #+#    #+#             */
/*   Updated: 2023/06/17 16:27:59 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_errorb(char *s, char *s1, char *s2, int ext)
{
	if (s)
		write(2, s, ft_strlen(s));
	if (s1)
		write(2, s1, ft_strlen(s1));
	if (s2)
		write(2, s2, ft_strlen(s2));
	g_exit_status = ext;
	return (0);
}

int	nbr(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+' || s[0] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **arg)
{
	int	ext;

	if (!arg[0])
		exit(0);
	if (!nbr(arg[0]))
	{
		write(2, "bash: exit: ", 12);
		ft_putstr_fd(arg[0], 2);
		write(2, ": numeric argument required\n", 27);
		g_exit_status = 255;
		write(2, "exit\n", 5);
		exit(255);
	}
	if (arg[1])
	{
		write(2, "exit: too many arguments\n", 25);
		g_exit_status = 1;
		return ;
	}
	ext = atoi(arg[0]);
	g_exit_status = ext;
	exit(ext);
	ft_free(arg);
}
