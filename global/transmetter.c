/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transmetter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:13:31 by aatki             #+#    #+#             */
/*   Updated: 2023/06/10 23:34:41 by aatki            ###   ########.fr       */
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
		{
			//printf("cmd[%d]=%s\n", i, pipe->cmd[i]);
			i++;
		}
		printf("infile=%s\n", pipe->infile);
		printf("outfile=%s\n", pipe->outfile);
		printf("here_doc=%s\n", pipe->outfile);
		pipe = pipe->next;
	}
}

// void ft_free_data(t_data *data)
// {
// 	t_data *tmp;
// 	while(data->exec)
// 	{
// 		tmp=data->exec;
// 		data->exec=data->exec->next;
// 		free(tmp);
// 	}
// }

void free_pipe(t_pipe *pipe)
{
	t_pipe *tmp;
	if(!pipe)
		return;
	while(pipe)
	{
		tmp=pipe;
		//ft_free(pipe->cmd);
		pipe=pipe->next;
		free(pipe);
	}
}

void files(t_exec *exec,t_pipe *tmp)
{
	(tmp)->infile = NULL;
	(tmp)->outfile = NULL;
	(tmp)->here_doc = NULL;
	(tmp)->here_doc_out=NULL;
	while (exec->file)
	{
		// printf("file type=<%d>\n", exec->file->type);
		// printf("file type=<%s>\n", exec->file->file);
		if (exec->file->type == 60)
			(tmp)->infile = exec->file->file;
		else if (exec->file->type == 62)
			(tmp)->outfile = exec->file->file;
		else if (exec->file->type == 5)
			(tmp)->here_doc = exec->file->file;
		else if (exec->file->type == 6)
			(tmp)->here_doc_out=exec->file->file;
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
		files(data->exec,tmp);
		tmp->next = NULL;
		data->exec = data->exec->next;
		ft_lstadd_back2(&pipe, tmp);
	}
	// g_exit_status = g_exit_status;
	//affiche_pipe(pipe);
	//ft_free_data(data);
	pipex(pipe, env, export);
	//free_pipe(pipe);
	//system("leaks minishell");
}