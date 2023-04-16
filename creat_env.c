/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:04:34 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/15 20:50:06 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	aff(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("---->name = %s path = %s\n", tmp->name, tmp->path);
		tmp = tmp->next;
	}
}

void	creat_env(char **en, t_data **data)
{
	int		i;
	char	*name;
	t_env	*new_node;
	char	*path;
	int		j;

	i = 0;
	(*data)->env = NULL;
	while (en[i])
	{
		j = 0;
		while (en[i][j])
		{
			if (en[i][j] == '=')
			{
				name = ft_substr(en[i], 0, j);
				path = ft_substr(en[i], j + 1, ft_strlen(en[i]));
				new_node = ft_lstnew(name, path);
				ft_lstadd_back(&(*data)->env, new_node);
				free(path);
				free(name);
				j = ft_strlen(en[i]);
			}
			else
				j++;
		}
		i++;
	}
}

