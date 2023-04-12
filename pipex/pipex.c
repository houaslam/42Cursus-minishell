/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:14:33 by aatki             #+#    #+#             */
/*   Updated: 2023/03/10 19:55:31 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *s)
{
	write(2, "Error\n", 7);
	write(2, s, ft_strlen(s));
	exit(1);
}

void	execution(char *command, char **env)
{
	char	*path;
	char	**cmd;

	path = NULL;
	cmd = ft_split(command, ' ');
	if (access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, env) < 0)
			ft_error("command can't executude");
	}
	else
	{
		path = check_env(env, cmd);
		if (execve(path, cmd, env) < 0)
			ft_error("command can't executude");
	}
	free(path);
	ft_free(cmd);
}

void	child_one(char **av, char **env, int *fd)
{
	int	infile;

	infile = open(av[1], O_RDONLY);
	close(fd[0]);
	if (dup2(infile, 0) < 0)
		ft_error("can't dup");
	if (dup2(fd[1], 1) < 0)
		ft_error("can't dup");
	execution(av[2], env);
}

void	child_two(char **av, char **env, int *fd)
{
	int	outfile;

	outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile < 0)
		ft_error("file can't opennn");
	if (close(fd[1]) < 0)
		ft_error("file can't close in child 2");
	if (dup2(fd[0], 0) < 0)
		ft_error("can't 2 dup in child 2");
	if (dup2(outfile, 1) < 0)
		ft_error("can't 1 dup in child 2");
	execution(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int	fd[2];
	int	id;
	int	id2;

	if (ac == 5)
	{
		if (pipe(fd) < 0)
			ft_error("can't pipe");
		id = fork();
		if (id < 0)
			ft_error("can't fork");
		if (id == 0)
			child_one(av, env, fd);
		id2 = fork();
		if (id2 < 0)
			ft_error("can't fork");
		if (id2 == 0)
			child_two(av, env, fd);
		if (close(fd[0]) < 0)
			ft_error("file can't close");
		if (close(fd[1]) < 0)
			ft_error("file can't close");
		waitpid(id, NULL, 0);
		waitpid(id2, NULL, 0);
	}
}
