/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 00:23:58 by aatki             #+#    #+#             */
/*   Updated: 2023/04/14 23:52:19 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex(t_data *data)
{
	(void)data;
}

void	ft_errora(char *s, int d, t_data *data)
{
	data->g_exit_status = d;
	write(2, "Error\n", 7);
	write(2, s, ft_strlen(s));
}

void	command(t_data *data, char **env)
{
	char	*str;
	char	**s;
	char	**ligne;

	data->envm = ft_envo(env);
	str = " -n $PATH gjjbjfgj";
	s = ft_split(str, ' ');
	ligne = ft_split(data->exec->value, ' ');
	printf("..%s..\n", data->exec->value);
	if (data->exec->type == PIPE)
	{
		if (!strncmp(ligne[0], "echo", 4))
			ft_echo(ligne++, 1, data->envm);
		else if (!strncmp(ligne[0], "env", 3))
			ft_env(data->envm, NULL, 1);
		else if (!strncmp(ligne[0], "export", 6))
			ft_export(data->envm, NULL, 1);
		else if (!strncmp(ligne[0], "cd", 2))
			ft_cd(data->envm, "hjnbn");
		else if (execve(NULL, NULL, env) > 0)
			pipex(data);
		else
		{
			ft_errora("command not found\n", 127, data);
			return ;
		}
	}
}
