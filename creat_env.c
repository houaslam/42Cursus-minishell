/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:04:34 by houaslam          #+#    #+#             */
/*   Updated: 2023/03/26 15:15:03 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *path_(char *env)
{
    int i;
    int j;
    char    *path;

    i = 0;
    while(env[i] != '=')
        i++;
    j = i;
    while(env[j])
        j++;
    path = malloc(sizeof(char) * (j - i));
    j = 0;
    i++;
    while(env[i])
        path[j++] = env[i++];
    path[j] = '\0';
    return(path);
}

char    *name_(char *env)
{
    int i;
    char    *name;
    i = 0;
    while(env[i] != '=')
        i++;
    name = malloc(sizeof(char) * i + 1);
    i = -1;
    while(env[++i] != '=')
		name[i] = env[i];
    name[i] = '\0';
    return(name);
}

void	aff(t_env *env)
{
	t_env *tmp;

	tmp = env;
	while(tmp)
	{
		printf("---->name = %s path = %s\n", tmp->name, tmp->path);
		tmp = tmp->next;
	}
}
void	creat_env(char **en, t_env **env)
{
	int		i;
	char	*name;
	t_env	*new_node;
	char 	*path;

	i = 0;	
    while (en[i])
	{
		name = name_(en[i]);
		path = path_(en[i]);
        new_node =  ft_lstnew(name, path);
		ft_lstadd_back(env, new_node);
        free(path);
        free(name);
		i++;
	}
}
