/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:14:33 by aatki             #+#    #+#             */
/*   Updated: 2023/06/17 17:45:06 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	command(char **cmd_arg, char ***export, int fdout, char ***env)
{
	if (*cmd_arg)
	{
		if (!ft_strcmp(cmd_arg[0], "echo"))
			ft_echo(++cmd_arg);
		else if (!ft_strcmp(cmd_arg[0], "env"))
			ft_env(*env, fdout, ++cmd_arg);
		else if (!ft_strcmp(cmd_arg[0], "export"))
			ft_export(export, env, ++cmd_arg, -1);
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

int ft_lstSize(t_pipe *head)
{
	int i = 0;
	while(head)
	{
		head = head->next;
		i++;
	}
	return i;
}

void	pipe_fork(int *id, int *ph) 
{
	if (pipe(ph) < 0)
	{
		ft_errorb("cant pipe in child one\n", NULL, NULL, 1);
		return ;
	}
	*id = fork();
	if (*id < 0)
	{
		ft_errorb("cant fork in child one\n", NULL, NULL, 1);
		return ;
	}
}

void	child_one(t_pipe *pipee, char ***env, char ***export)
{
	int	ph[2];
	int	fd;
	int id;

	fd = 0;
	while (pipee)
	{
		pipe_fork(&id, ph);
		if (id == 0)
		{
			signal(SIGINT, SIG_DFL);
			if (!pipee->next)
				ph[1] = 1;
			if (!duping(pipee, fd, ph, 1))
				return ;
			command((pipee)->cmd, export, ph[1], env);
			exit(g_exit_status);
		}
		fd = dup(ph[0]);
		close(ph[1]);
		if (pipee->her_docin)
			close (pipee->her_docin);
		pipee = (pipee)->next;
	}
	waitpid (-1, &g_exit_status, 0);
	if (WIFEXITED(g_exit_status))
		g_exit_status = WEXITSTATUS(g_exit_status);
}

void	pipex(t_pipe *pipe, char ***env, char ***export)
{
	if (!pipe->next && builtin(*pipe->cmd))
		builtin_exec(pipe, env, export);
	else
		child_one(pipe, env, export);
}
