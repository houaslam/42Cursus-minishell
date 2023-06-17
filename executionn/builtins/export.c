/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:50:50 by aatki             #+#    #+#             */
/*   Updated: 2023/06/17 17:19:05 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	sort_export(char **export)
{
	int		i;
	char	*change;

	i = 0;
	while ((export[i]))
	{
		if (export[i + 1] && ft_strncmp(export[i], export[i + 1],
				ft_strlen(export[i])) == 1)
		{
			change = ft_strdup(export[i]);
			free(export[i]);
			export[i] = ft_strdup(export[i + 1]);
			free(export[i + 1]);
			export[i + 1] = ft_strdup(change);
			free(change);
			i = -1;
		}
		i++;
	}
}

char	**add_str(char **env, char *plus)
{
	int		i;
	char	**menv;

	i = 0;
	while (env[i])
		i++;
	menv = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		menv[i] = ft_strdup(env[i]);
		i++;
	}
	if (plus)
	{
		menv[i] = ft_strdup(plus);
		i++;
	}
	menv[i] = NULL;
	ft_free(env);
	return (menv);
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

void	affiche_export(char **export)
{
	int	i;
	int	j;

	i = 0;
	while (export[i])
	{
		j = 0;
		printf("declare -x ");
		while (export[i][j])
		{
			printf("%c", export[i][j]);
			if (export[i][j] == '=')
				printf("\"");
			j++;
		}
		printf("\"\n");
		i++;
	}
}

int	ft_export(char ***export, char ***env, char **arg, int i)
{
	int		c;
	char	**sp;
	int		k;

	sp = NULL;
	k = 0;
	if (!*arg)
		affiche_export(*export);
	else
	{
		while (arg[++i])
		{
			sp = equal(arg[i], &k);
			if ((k == 1 && (!check_arg(sp[0]) \
			|| !sp[1] || !sp[1][0])) || (k == 2 && !sp[0][0]))
			{
				ft_errorb("bash: export: `", sp[0],
					"': not a valid identifier\n", 1);
				ft_free(sp);
				return (0);
			}
			else
			{
				if (the_plus(*export, sp))
					return (0);
				c = ft_cases(*env, *export, sp[0]);
				change(export, env, arg[i], c);
				ft_free(sp);
			}
		}
	}
	return (0);
}
