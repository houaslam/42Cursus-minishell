/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascci.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:29:44 by aatki             #+#    #+#             */
/*   Updated: 2022/10/23 16:32:39 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_isascii(int c)
{
	return ((c >= 0 && c <= 127));
}