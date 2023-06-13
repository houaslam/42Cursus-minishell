/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transmetter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:13:31 by aatki             #+#    #+#             */
/*   Updated: 2023/06/13 13:55:32 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

void	ft_lstadd_back2(t_pipe **lst, t_pipe *new)
{
	t_pipe	*temp;

	if (!new)
		return ;
	if (*lst)
	{
		temp = (*lst);
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		*lst = new;
}

void	affiche_pipe(t_pipe *pipe)
{
	int	i;

	while (pipe)
	{
		i = 0;
		while (pipe->cmd[i])
			i++;
		pipe = pipe->next;
	}
}

void	free_pipe(t_pipe *pipe)
{
	t_pipe	*tmp;

	if (!pipe)
		return ;
	while (pipe)
	{
		tmp = pipe;
		pipe = pipe->next;
		free(pipe);
	}
}

void	files(t_exec *exec, t_pipe *tmp)
{
	(tmp)->infile = NULL;
	(tmp)->outfile = NULL;
	(tmp)->here_doc = NULL;
	(tmp)->here_doc_out = NULL;
	while (exec->file)
	{
		if (exec->file->type == 60)
			(tmp)->infile = exec->file->file;
		else if (exec->file->type == 62)
		{
			open(exec->file->file, O_CREAT);
			(tmp)->outfile = exec->file->file;
		}
		else if (exec->file->type == 5)
			(tmp)->here_doc = exec->file->file;
		else if (exec->file->type == 6)
		{
			open(exec->file->file, O_CREAT);
			(tmp)->here_doc_out = exec->file->file;
		}
		exec->file = exec->file->next;
	}
}

void	transmettre(t_data *data, char ***env, char ***export)
{
	t_pipe	*tmp;
	t_pipe	*pipe;

	pipe = NULL;
	tmp = NULL;
	while (data->exec)
	{
		tmp = malloc(sizeof(t_pipe));
		(tmp)->cmd = ft_split(data->exec->value, '\n');
		files(data->exec, tmp);
		tmp->next = NULL;
		data->exec = data->exec->next;
		ft_lstadd_back2(&pipe, tmp);
	}
	pipex(pipe, env, export);
}
