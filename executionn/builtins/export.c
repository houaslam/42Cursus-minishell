/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:50:50 by aatki             #+#    #+#             */
/*   Updated: 2023/06/18 02:13:20 by houaslam         ###   ########.fr       */
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

void	for_norm_(char ***export, char ***env, char **arg, char **sp)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (arg[i])
	{
		sp = equal(arg[i], &k);
		if ((k == 1 && (!check_arg(sp[0]) || !sp[1] || !sp[1][0])) || (k == 2
				&& !sp[0][0]))
		{
			ft_errorb("bash: export: `", sp[0], "': \
			not a valid identifier\n", 1);
			ft_free(sp);
		}
		else
		{
			if (the_plus(*export, sp))
				return ;
			change(export, env, arg[i], ft_cases(*env, *export, sp[0]));
			ft_free(sp);
		}
		i++;
	}
}

void	ft_export(char ***export, char ***env, char **arg)
{
	char	**sp;
	int		k;

	sp = NULL;
	k = 0;
	if (!*arg)
		affiche_export(*export);
	else
		for_norm_(export, env, arg, sp);
}
