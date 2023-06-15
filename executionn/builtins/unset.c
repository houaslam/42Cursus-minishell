/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:50:55 by aatki             #+#    #+#             */
/*   Updated: 2023/06/15 01:54:54 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_argg(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
			|| s[i] == '_'))
		i++;
	if (s[i] == '\0')
		return (1);
	else
		return (0);
}

void	norm(char **env, int i)
{
	if (!env[i])
		return ;
	while ((env[i + 1]))
	{
		free(env[i]);
		env[i] = ft_strdup(env[i + 1]);
		i++;
	}
	free(env[i]);
	env[i] = NULL;
}

void	ft_unset(char **env, char **arg)
{
	int	i;
	int	j;

	j = 0;
	while (arg[j])
	{
		i = 0;
		if (!check_argg(arg[j]))
		{
			ft_errorb("bash: unset: `", arg[j], ": not a valid identifier\n",
				127);
			return ;
		}
		while ((env[i]))
		{
			if (arg && !ft_strncmp(env[i], arg[j], ft_strlen(arg[j])))
				break ;
			i++;
		}
		j++;
	}
	norm(env, i);
}
