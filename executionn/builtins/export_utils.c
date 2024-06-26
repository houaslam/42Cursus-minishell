/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:41:51 by aatki             #+#    #+#             */
/*   Updated: 2023/06/18 21:32:12 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cases(char **env, char **export, char *arg)
{
	int	c;
	int	e;

	c = foundin(arg, export);
	e = foundin(arg, env);
	if ((c == 1 && e == 1))
		return (1);
	else if (c == 1 && e == 3)
		return (2);
	else if (c == 3 && e == 3)
		return (3);
	else if ((c == 2 && e == 4) || (c == 2 && e == 2))
		return (4);
	else if (c == 4 && e == 4)
		return (5);
	else
		return (0);
}

void	change2(char ***export, char ***env, char *arg, int cas)
{
	if (cas == 3)
	{
		*env = add_str(*env, arg);
		export[0] = add_str(export[0], arg);
		sort_export(*export);
	}
	else if (cas == 5)
	{
		arg = ft_strjoin(arg, "=");
		export[0] = add_str(export[0], arg);
		free(arg);
		sort_export(*export);
	}
}

void	change(char ***export, char ***env, char *arg, int cas)
{
	int	i;

	if (cas == 1)
	{
		i = position(*env, arg);
		free(env[0][i]);
		env[0][i] = ft_strdup(arg);
		i = position(*export, arg);
		free(export[0][i]);
		export[0][i] = ft_strdup(arg);
	}
	else if (cas == 2)
	{
		i = position(*export, arg);
		free(export[0][i]);
		export[0][i] = ft_strdup(arg);
		*env = add_str(*env, arg);
	}
	else
		change2(export, env, arg, cas);
}

int	check_arg(char *s)
{
	unsigned long int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return (0);
	while (s[i] && (ft_isalpha(s[i]) || (s[i] == '=' && s[i + 1] == '\0')
			|| s[i] == '_' || (s[i] == '+' && s[i + 1] == '=' && s[i
				+ 2] == '\0')))
		i++;
	if (s[i] == '\0')
		return (1);
	else
		return (0);
}
