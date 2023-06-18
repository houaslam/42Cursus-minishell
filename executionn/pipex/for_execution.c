/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 23:46:18 by aatki             #+#    #+#             */
/*   Updated: 2023/06/18 16:56:40 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_lst_size(t_pipe *head)
{
	int	i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

void	ctrl_s(int i)
{
	if (i == SIGQUIT)
	{
		write(1, "\\", 2);
		write(1, "QUIT", 4);
		exit(0);
	}
}

void	command(char **cmd_arg, char ***export, int fdout, char ***env)
{
	if (*cmd_arg)
	{
		if (!ft_strcmp(cmd_arg[0], "echo"))
			ft_echo(++cmd_arg);
		else if (!ft_strcmp(cmd_arg[0], "env"))
			ft_env(*env, fdout, ++cmd_arg);
		else if (!ft_strcmp(cmd_arg[0], "export"))
			ft_export(export, env, ++cmd_arg);
		else if (!ft_strcmp(cmd_arg[0], "cd"))
			ft_cd(*env, *export, ++cmd_arg);
		else if (!ft_strcmp(cmd_arg[0], "exit"))
			ft_exit(++cmd_arg);
		else if (!ft_strcmp(cmd_arg[0], "unset"))
		{
			ft_unset(*env, ++cmd_arg, 0);
			ft_unset(*export, cmd_arg, 1);
		}
		else if (!ft_strcmp(cmd_arg[0], "pwd"))
			ft_pwd(fdout);
		else
			execution(cmd_arg, *env);
		signal(SIGINT, ctrl_c);
	}
}

void	execution(char **cmd, char **env)
{
	char	*path;

	path = NULL;
	if (access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, env) < 0)
		{
			ft_errorb("command can't executude\n", NULL, NULL, 1);
			return ;
		}
	}
	else
	{
		path = check_env(env, cmd);
		if (execve(path, cmd, env) < 0)
			return ;
	}
}
