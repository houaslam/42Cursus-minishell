/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 00:56:35 by aatki             #+#    #+#             */
/*   Updated: 2023/04/11 03:39:39 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int c, char **av, char **env)
{
	//ft_echo(av, 1, env);
	//ft_pwd(1);
	char **menv=ft_envo(env);
	// ft_export(menv,av[1],1);
	ft_unset(menv,av[1]);
	//ft_env(menv,av[1],1);
	//ft_cd(env,av[1]);
}
