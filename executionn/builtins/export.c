/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:50:50 by aatki             #+#    #+#             */
/*   Updated: 2023/06/14 18:18:35 by houaslam         ###   ########.fr       */
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

char	**equal(char *s)
{
	char	**sp;
	int		i;

	if (!s)
		return (NULL);
	sp = malloc(sizeof(char *) * 3);
	i = 0;
	sp[0] = malloc(ft_strlen(s) + 1);
	sp[0][ft_strlen(s)] = '\0';
	while (s[i])
	{
		sp[0][i] = s[i];
		if (s[i] == '=')
		{
			sp[0][i + 1] = '\0';
			break ;
		}
		i++;
	}
	sp[1] = ft_substr(s, i, ft_strlen(s) - i);
	sp[2] = NULL;
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

void	ft_export(char ***export, char ***env, char **arg)
{
	int		i;
	int		c;
	char	**sp;

	sp = NULL;
	i = 0;
	if (!*arg)
		affiche_export(*export);
	else
	{
		while (arg[i])
		{
			sp = equal(arg[i]);
			if (!check_arg(sp[0]))
				return (ft_errorb("bash: export: `", sp[0], \
				"': not a valid identifier\n", 1));
			else
			{
				c = ft_cases(*env, *export, sp[0]);
				change(export, env, arg[i], c);
				ft_free(sp);
			}
			i++;
		}
	}
}
