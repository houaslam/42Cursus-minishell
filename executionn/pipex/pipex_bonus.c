/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:14:33 by aatki             #+#    #+#             */
/*   Updated: 2023/04/29 10:30:25 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	command(char **cmd_arg, char ***export, int fdout, char ***env)
{
	if (!strncmp(cmd_arg[0], "echo", 4))
		ft_echo(++cmd_arg, fdout, *env);
	else if (!strncmp(cmd_arg[0], "env", 3))
		ft_env(*env, fdout);
	else if (!strncmp(cmd_arg[0], "export", 6))
		ft_export(export, env, ++cmd_arg, fdout);
	else if (!strncmp(cmd_arg[0], "cd", 2))
		ft_cd(*env, *export, ++cmd_arg);
	else if (!strncmp(cmd_arg[0], "exit", 4))
		ft_exit(++cmd_arg);
	else if (!strncmp(cmd_arg[0], "unset", 5))
	{
		ft_unset(*env, ++cmd_arg);
		ft_unset(*export, ++cmd_arg);
	}
	else if (!strncmp(cmd_arg[0], "pwd", 3))
		ft_pwd(fdout, *env);
	else
	{
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
			ft_errorb("command can't executude", NULL, NULL, 1);
	}
	else
	{
		path = check_env(env, cmd);
		if (execve(path, cmd, env) < 0)
			ft_errorb("command can't executude", NULL, NULL, 1);
	}
	free(path);
	ft_free(cmd);
}

void	child_one(t_pipe **pipee, int *fd, char ***env, char ***export)
{
	int	ph[2];
	int	id;

	//fd[0] = ft_infile((*pipee)->infile);
	while ((*pipee)->next)
	{
		if (pipe(ph) < 0)
			ft_errorb("cant pipe in child one", NULL, NULL, 1);
		id = fork();
		if (id < 0)
			ft_errorb("cant fork in child one", NULL, NULL, 1);
		if (id == 0)
		{
			duping(*pipee, fd, ph);
			command((*pipee)->cmd, export, ph[1], env);
			*fd = dup(ph[0]);
		}
		close(ph[1]);
		*pipee = (*pipee)->next;
		waitpid(id, NULL, 0);
	}
}

void	child_two2(t_pipe *pipee, int *fd, char ***env, char ***export)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		duping(pipee, fd, NULL);
		command(pipee->cmd, export, 1, env);
	}
	waitpid(id, NULL, 0);
}

int	builtin(char *s)
{
	if (!strncmp(s, "echo", 4) || !strncmp(s, "env", 3)
		|| !strncmp(s, "export", 6) || !strncmp(s, "exit", 4)
		|| !strncmp(s, "unset", 5) || !strncmp(s, "pwd", 3))
		return (1);
	else
		return (0);
}

void	builtin_exec(t_pipe *pipe, char ***env, char ***export)
{
	duping(pipe, 0, NULL);
	command(pipe->cmd, export, 1, env);
}

void	pipex(t_pipe *pipe, char ***env, char ***export)
{
	int	fd;

	if (!pipe->next && builtin(pipe->cmd[0]))
		builtin_exec(pipe, env, export);
	child_one(&pipe, &fd, env, export);
	child_two2(pipe, &fd, env, export);
}
