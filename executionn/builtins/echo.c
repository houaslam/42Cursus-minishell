/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:50:45 by aatki             #+#    #+#             */
/*   Updated: 2023/06/17 16:18:30 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	found(char *sa, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], sa, ft_strlen(sa))
			&& env[i][ft_strlen(sa)] == '=')
			printf("%s", env[i] + ft_strlen(sa) + 1);
		i++;
	}
	return ;
}

void	checkarg(char **arg)
{
	int	i;

	i = 0;
	if (arg[0] && arg[0][0] && arg[0][0] == '`' && !arg[1])
		ft_errorb("bash; ", "command not found\n", NULL, 127);
	while (arg[i])
	{
		if (!ft_strcmp(arg[i], "`"))
		{
			free(arg[i]);
			arg[i] = ft_strdup("");
		}
		i++;
	}
}

int	which_flag(char **arg, int *i)
{
	int	j;
	int	flag;

	flag = 0;
	while (arg[*i])
	{
		j = 0;
		if (arg[*i][j] == '-')
		{
			while (arg[*i][++j])
			{
				if (arg[*i][j] != 'n')
				{
					write(1, arg[*i], ft_strlen(arg[*i]));
					write(1, " ", 1);
					return (2);
				}
			}
			flag = 1;
		}
		else
			return (flag);
		(*i)++;
	}
	return (flag);
}

void	ft_echo(char **arg)
{
	int	i;
	int	flag;

	i = 0;
	flag = which_flag(arg, &i);
	if (flag == 2)
		i++;
	while (arg[i])
	{
		write(1, arg[i], ft_strlen(arg[i]));
		if (arg[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (flag != 1)
		printf("\n");
}
