/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:50:55 by aatki             #+#    #+#             */
/*   Updated: 2023/04/30 11:18:40 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_unset(char **env,char **arg)
{
	int	i;

	int j=0;
	while(arg[j])
	{
		i=0;
		while ((env[i]))
		{
			if (arg && !ft_strncmp(env[i], arg[j], ft_strlen(arg[j])))
				break ;
			i++;
		}
		if (!env[i])
			return ;
		while ((env[i + 1]))
		{
			free(env[i]);
			env[i] = ft_strdup(env[i + 1]);
			i++;
		}
		env[i] = NULL;
		j++;
	}
}