/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:39:45 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/11 14:17:07 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exec(t_exec **exec)
{
	t_exec	*next;
	t_exec	*head;

	head = *exec;
	while (*exec)
	{
		next = (*exec)->next;
		free((*exec)->value);
		free(*exec);
		*exec = next;
	}
	head = NULL;
}

char	*seach_env_value(char *str, t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->name))
			return (tmp->path);
		tmp = tmp->next;
	}
	return (NULL);
}
