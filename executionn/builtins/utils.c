/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:37:29 by aatki             #+#    #+#             */
/*   Updated: 2023/04/26 12:33:10 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**ft_free(char **p)
{
	int	i;

	if (!*p)
		return (NULL);
	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}
