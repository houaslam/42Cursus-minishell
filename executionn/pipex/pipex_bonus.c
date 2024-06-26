/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:14:33 by aatki             #+#    #+#             */
/*   Updated: 2023/06/18 17:47:57 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipe_fork(int *id, int *ph)
{
	signal(SIGINT, SIG_IGN);
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
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

void	wait_func(int *tab, int i)
{
	i--;
	while (i >= 0)
	{
		waitpid(tab[i], &g_exit_status, 0);
		if (WIFEXITED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		else if (WIFSIGNALED(g_exit_status))
			g_exit_status = WEXITSTATUS(g_exit_status);
		i--;
	}
	free(tab);
}

void	dup_func(int *ph, int *fd, int *i, t_pipe **pipe)
{
	*fd = dup(ph[0]);
	close(ph[1]);
	if ((*pipe)->her_docin)
		close((*pipe)->her_docin);
	*pipe = (*pipe)->next;
	*i += 1;
}

void	child_one(t_pipe *pipee, char ***env, char ***export)
{
	int	ph[2];
	int	fd;
	int	*tab;
	int	i;

	i = 0;
	fd = 0;
	tab = malloc(ft_lst_size(pipee) * sizeof(int));
	while (pipee)
	{
		pipe_fork(&tab[i], ph);
		if (tab[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, ctrl_s);
			if (!pipee->next)
				ph[1] = 1;
			if (!duping(pipee, fd, ph, 1))
				exit(g_exit_status);
			command((pipee)->cmd, export, ph[1], env);
			exit(g_exit_status);
		}
		dup_func(ph, &fd, &i, &pipee);
	}
	wait_func(tab, i);
}

void	pipex(t_pipe *pipe, char ***env, char ***export)
{
	if (!pipe->next && builtin(*pipe->cmd))
		builtin_exec(pipe, env, export);
	else
		child_one(pipe, env, export);
}
