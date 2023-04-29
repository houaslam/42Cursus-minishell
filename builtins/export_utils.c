/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 08:41:51 by aatki             #+#    #+#             */
/*   Updated: 2023/04/28 09:18:36 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
		if (env[i][j] != '=' && env[i])
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
	if (sa[ft_strlen(sa)] == '=')
		return (3);
	else
		return (4);
}

int	ft_cases(char **env, char **export, char *arg)
{
	int	c;
	int	e;

	c = foundin(arg, export);
	e = foundin(arg, env);

	if((c == 1 && e == 1 ))
		return 1;
	else if (c == 1 && e == 3 )
		return 2;
	else if (c == 3 && e == 3 )
		return 3;
	else if ((c == 2 && e == 4)  || (c == 2 && e == 2))
		return 4;
	else if (c == 4 && e == 4 )
		return 5;
    else
        return 0;
}

void	change(char ***export, char ***env, char *arg, int cas)
{
	int i;
	dprintf(2,"%d\n",cas);
	if (cas == 1)
	{
		i=position(*env,arg);
		free(env[0][i]);
		env[0][i] = ft_strdup(arg);
		i=position(*export,arg);
		free(export[0][i]);
		export[0][i] = ft_strdup(arg);
	}
	else if (cas == 2)
	{
		i=position(*export,arg);
		free(*export[i]);
		*export[i] = ft_strdup(arg);
		*env= add_str(*env, arg);
	}
	else if (cas == 3)
	{
		*env= add_str(*env, arg);
		*export= add_str(*export, arg);
		sort_export(*export);
	}
	else if (cas == 4 )
		return;
	else if (cas == 5 )
	{
		*export = add_str(*export, arg);
		sort_export(*export);
	}
}

int	check_arg(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
			|| s[i] == '_'|| s[i] == '=') )
		i++;
	if (s[i] == '\0')
		return (1);
	else
		return (0);
}

int	position(char **doubl,char *str)
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
			break;
		else if (doubl[i])
		{
			i++;
			continue ;
		}
		i++;
	}
	return i;
}
