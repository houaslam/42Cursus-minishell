/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:50:27 by aatki             #+#    #+#             */
/*   Updated: 2023/04/28 15:57:19 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_errorb(char *s,char *s1,char *s2,int ext)
{
	write(2,s,ft_strlen(s));
	write(2,s1,ft_strlen(s1));
	write(2,s2,ft_strlen(s2));
	char *t[]={ft_itoa(ext),NULL};
	ft_exit(t);
}

void	ft_exit(char **arg)
{
	int ext=atoi(arg[0]);
	exit_status=ext;
	exit(ext);
}
