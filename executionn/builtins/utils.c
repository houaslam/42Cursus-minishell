/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:37:29 by aatki             #+#    #+#             */
/*   Updated: 2023/06/18 21:32:41 by aatki            ###   ########.fr       */
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
	int	k;

	i = 0;
	k = 0;
	while (doubl[i])
	{
		j = 0;
		while (doubl[i][j] != '=' && (doubl[i][j] == str[j] || str[j] == '+'))
			j++;
		if (doubl[i][j] == '=')
		{
			k = 1;
			break ;
		}
		else if (doubl[i])
		{
			i++;
			continue ;
		}
		i++;
	}
	if (k == 1)
		return (i);
	return (-1);
}

int	the_plus(char **export, char **sp, char **env)
{
	int	i;
	int	k;

	if (!sp[1] || !sp[1][0])
		return (0);
	i = ft_strlen(sp[0]);
	if (i >= 2 && !(sp[0][i - 2] == '+' && sp[0][i - 1] == '='))
		return (0);
	k = position(export, sp[0]);
	if (k >= 0)
		export[k] = ft_strjoin_free(export[k], sp[1]);
	i = position(env, sp[0]);
	if (i >= 0)
		env[i] = ft_strjoin_free(env[i], sp[1]);
	if (i < 0 || k < 0)
	{
		sp[0][ft_strlen(sp[0]) - 2] = '\0';
		sp[0] = ft_strjoin_free(sp[0], "=");
		return (0);
	}
	ft_free(sp);
	return (1);
}

char	**equal(char *s, int *j)
{
	char	**sp;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	sp = malloc(sizeof(char *) * 3);
	while (s[i])
	{
		if (s[i] == '=')
		{
			sp[0] = ft_substr(s, 0, i + 1);
			sp[1] = ft_substr(s, i + 1, ft_strlen(s) - i);
			sp[2] = NULL;
			*j = 1;
			return (sp);
		}
		i++;
	}
	sp[0] = ft_strdup(s);
	sp[1] = NULL;
	*j = 2;
	return (sp);
}
