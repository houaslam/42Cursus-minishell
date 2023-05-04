/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:14:33 by aatki             #+#    #+#             */
/*   Updated: 2023/05/02 13:16:07 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	command(char **cmd_arg, char ***export, int fdout, char ***env)
{
	if(*cmd_arg)
	{
		if (!ft_strcmp(cmd_arg[0], "echo"))
			ft_echo(++cmd_arg, fdout, *env);
		else if (!ft_strcmp(cmd_arg[0], "env"))
			ft_env(*env, fdout, ++cmd_arg);
		else if (!ft_strcmp(cmd_arg[0], "export"))
			ft_export(export, env, ++cmd_arg, fdout);
		else if (!ft_strcmp(cmd_arg[0], "cd"))
			ft_cd(*env, *export, ++cmd_arg);
		else if (!ft_strcmp(cmd_arg[0], "exit"))
			ft_exit(++cmd_arg);
		else if (!ft_strcmp(cmd_arg[0], "unset"))
		{
			ft_unset(*env, ++cmd_arg);
			ft_unset(*export, cmd_arg);
		}
		else if (!ft_strcmp(cmd_arg[0], "pwd"))
			ft_pwd(fdout, *env);
		else
		{
			execution(cmd_arg, *env);
		}
	}
}

void	execution(char **cmd, char **env)
{
	char	*path;

	path = NULL;
	if (access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, env) < 0)
			ft_errorb("command can't executude\n", NULL, NULL, 1);
	}
	else
	{
		path = check_env(env, cmd);
		if (execve(path, cmd, env) < 0)
			ft_errorb("command can't executude\n", NULL, NULL, 1);
	}
	//free(path);
	//ft_free(cmd);
}

void	child_one(t_pipe **pipee, int *fd, char ***envv, char ***exportv)
{
	int	id;
	int	ph[2];

	// ph[0]=0;
	// ph[1]=1;
	//fd[0] = ft_infile((*pipee)->infile);
	char ** env=*envv;
	char **export =*exportv;
	while ((*pipee)->next)
	{
		if (pipe(ph) < 0)
			ft_errorb("cant pipe in child one\n", NULL, NULL, 1);
		id = fork();
		if (id < 0)
			ft_errorb("cant fork in child one\n", NULL, NULL, 1);
		if (id == 0)
		{
			duping(*pipee, fd, ph);
			command((*pipee)->cmd, &export, ph[1], &env);
			exit(0);
		}
		*fd = dup(ph[0]);
		close(ph[1]);
		*pipee = (*pipee)->next;
		waitpid(id, &g_exit_status, 0);
	}
}

void	child_two2(t_pipe *pipee, int *fd, char ***envv, char ***exportv)
{
	int	id;
	int	ph[2];

	id = fork();
	ph[0] = 0;
	ph[1] = 1;
	char ** env=*envv;
	char **export =*exportv;
	if (id == 0)
	{
		duping(pipee, fd, ph);
		command(pipee->cmd, &export, 1, &env);
		exit(0);
	}
	waitpid(id, &g_exit_status, 0);
}

int	builtin(char *s)
{
	if(!s)
		return 0;
	if (!strncmp(s, "echo", 4) || !strncmp(s, "env", 3) || !strncmp(s, "export",
			6) || !strncmp(s, "exit", 4) || !strncmp(s, "unset", 5)
		|| !strncmp(s, "pwd", 3) || !strncmp(s, "cd", 3))
		return (1);
	else
		return (0);
}

void	builtin_exec(t_pipe *pipe, char ***env, char ***export)
{
	int	orig_fd;
	int	orig_fd1;
	int	ph[2];

	// int ph[2]={0,1};
	orig_fd = dup(0);
	orig_fd1 = dup(1);
	ph[0] = 0;
	ph[1] = 1;
	duping(pipe, ph, ph);
	command(pipe->cmd, export, 1, env);
	//dup2(orig_fd ,0);
	if (ph[0] != 0)
	{
		dup2(orig_fd, 0);
		close(orig_fd);
	}
	if (ph[1] != 1)
	{
		dup2(orig_fd1, 1);
		close(orig_fd1);
	}
}

void	pipex(t_pipe *pipe, char ***env, char ***export)
{
	int	fd;

	fd = 0;

	if (!pipe->next && builtin(*pipe->cmd))
	{
		builtin_exec(pipe, env, export);
		return ;
	}
	child_one(&pipe, &fd, env, export);
	child_two2(pipe, &fd, env, export);
}
