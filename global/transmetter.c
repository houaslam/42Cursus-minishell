/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transmetter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:13:31 by aatki             #+#    #+#             */
/*   Updated: 2023/06/18 15:48:59 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	for_norm(t_exec *exec, t_pipe **tmp)
{
	int	fd;

	if ((exec)->file->type == R_OUT)
	{
		if ((*tmp)->here_doc_out)
			(*tmp)->here_doc_out = NULL;
		fd = open((exec)->file->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		((*tmp))->outfile = (exec)->file->file;
		close (fd);
	}
	else if ((exec)->file->type == H_OUT)
	{
		fd = open((exec)->file->file, O_CREAT | O_APPEND, 0644);
		((*tmp))->here_doc_out = (exec)->file->file;
		close (fd);
	}
}

int	for_norm2(t_exec **exec, t_pipe **tmp)
{
	int	fd;

	if ((*tmp)->her_docin)
	{
		close((*tmp)->her_docin);
		(*tmp)->her_docin = 0;
	}
	fd = open((*exec)->file->file, O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_errorb("bash: ", (*exec)->file->file, ": No such \
	    file or directory\n", 1);
		return (0);
	}
	(*tmp)->infile = (*exec)->file->file;
	close(fd);
	return (1);
}

int	files(t_exec *exec, t_pipe *tmp, char **env)
{
	int	ret;

	ret = 1;
	(tmp)->infile = NULL;
	(tmp)->outfile = NULL;
	(tmp)->here_doc_out = NULL;
	(tmp)->her_docin = 0;

	(void)env;
	while (exec->file)
	{
		if (exec->file->type == R_OUT || exec->file->type == H_OUT)
			for_norm(exec, &tmp);
		else if (exec->file->type == H_IN)
		{
			if (tmp->infile)
				tmp->infile = NULL;
			if ((tmp)->her_docin)
				close((tmp)->her_docin);
			tmp->her_docin = here_docc(exec->file->file, env, \
				exec->file->expand);
		}
		else if (exec->file->type == R_IN)
			ret = for_norm2(&exec, &tmp);
		exec->file = exec->file->next;
	}
	return (ret);
}

void	transmettre(t_data *data, char ***env, char ***export)
{
	t_pipe	*tmp;
	t_pipe	*pipe;
	t_exec	*t;

	pipe = NULL;
	tmp = NULL;
	t = data->exec;
	while (t)
	{
		tmp = malloc(sizeof(t_pipe));
		(tmp)->cmd = ft_split(t->value, '\n');
		checkarg((tmp)->cmd);
		tmp->next = NULL;
		if (!files(t, tmp, *env))
		{
			free_pipe(tmp);
			break ;
		}
		t = t->next;
		ft_lstadd_back2(&pipe, &tmp);
	}
	if (pipe)
		pipex(pipe, env, export);
	free_pipe(pipe);
}
