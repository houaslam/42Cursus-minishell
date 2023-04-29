/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 09:46:52 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/29 15:15:12 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n )
{
	size_t	i;
	char	*s;

	s = str;
	i = 0;
	while (i < n)
	{
		s[i] = '\0';
		i++;
	}
}
