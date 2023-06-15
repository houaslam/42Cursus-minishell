/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:37:29 by aatki             #+#    #+#             */
/*   Updated: 2023/06/15 17:03:19 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**ft_free(char **p)
{
	int	i;

	if (!*p)
		return (NULL);
	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

int	foundin(char *sa, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=' && env[i][j] == sa[j])
			j++;
		if ((env[i][j] != '=' || (sa[j] && sa[j + 1])) && env[i])
		{
			i++;
			continue ;
		}
		else if (sa[j] == '=')
			return (1);
		else
			return (2);
		i++;
	}
	if (sa[ft_strlen(sa) - 1] == '=')
		return (3);
	else
		return (4);
}

int	position(char **doubl, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (doubl[i])
	{
		j = 0;
		while (doubl[i][j] != '=' && doubl[i][j] == str[j])
			j++;
		if (doubl[i][j] == '=')
			break ;
		else if (doubl[i])
		{
			i++;
			continue ;
		}
		i++;
	}
	return (i);
}

int	the_plus(char **export, char **sp)
{
	int	i;
	int	k;

	i = ft_strlen(sp[0]);
	if (!(sp[0][i - 2] == '+' && sp[0][i - 1] == '='))
		return (0);
	k = position(export, sp[0]);
	export[k] = ft_strjoin_free(export[k], sp[1] + 1);
	ft_free(sp);
	return (1);
}
