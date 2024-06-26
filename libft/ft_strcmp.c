/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:28:17 by houaslam          #+#    #+#             */
/*   Updated: 2023/06/13 13:53:36 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *str, char *str_2)
{
	int	i;

	i = 0;
	while (str[i] && str_2[i])
	{
		if (str[i] != str_2[i])
			return (str[i] - str_2[i]);
		i++;
	}
	if (str[i] || str_2[i])
		return (1);
	return (0);
}
