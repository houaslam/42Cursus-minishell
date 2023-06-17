/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transmetter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:13:31 by aatki             #+#    #+#             */
/*   Updated: 2023/06/17 20:36:44 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

int	other_file2(t_exec *exec, t_pipe *tmp)
{
	if (exec->file->type == 6)
	{
		if (tmp->outfile)
			tmp->outfile = NULL;
		open(exec->file->file, O_CREAT, 0644);
		(tmp)->here_doc_out = exec->file->file;
	}
	else if (exec->file->type == 60)
	{
		if (tmp->here_doc)
			tmp->here_doc = NULL;
		if (open(exec->file->file, O_RDONLY, 0644) < 0)
		{
			ft_errorb("bash: ", exec->file->file, \
			": No such file or directory\n", 1);
			return (0);
		}
	}
	return (1);
}

int    files(t_exec *exec, t_pipe *tmp, char **env)
{
    (tmp)->infile = NULL;
    (tmp)->outfile = NULL;
    (tmp)->here_doc = NULL;
    (tmp)->here_doc_out = NULL;
    (tmp)->her_docin = 0;
    while (exec->file)
    {
        if (exec->file->type == 62)
        {
            if (tmp->here_doc_out)
                tmp->here_doc_out = NULL;
            open(exec->file->file, O_CREAT, 0644);
            (tmp)->outfile = exec->file->file;
        }
        else if (exec->file->type == 5)
        {
            if (tmp->infile)
                tmp->infile = NULL;
            tmp->here_doc = here_docc(exec->file->file, env, exec->file->expand);
            tmp->her_docin = dup(tmp->here_doc[0]);
            close(tmp->here_doc[1]);
            close(tmp->here_doc[0]);
            free(tmp->here_doc);
        }
        else if (exec->file->type == 6)
        {
            if (tmp->outfile)
                tmp->outfile = NULL;
            open(exec->file->file, O_CREAT, 0644);
            (tmp)->here_doc_out = exec->file->file;
        }
        else if (exec->file->type == 60)
        {
            if (tmp->here_doc)
                tmp->here_doc = NULL;
            if (open(exec->file->file, O_RDONLY, 0644) < 0)
            {
                ft_errorb("bash: ",exec->file->file,": No such \
				file or directory\n",1);
                return (0);
            }
            (tmp)->infile = exec->file->file;
        }
        exec->file = exec->file->next;
    }
    return (1);
}

void	transmettre(t_data *data, char ***env, char ***export)
{
	t_pipe	*tmp;
	t_pipe	*pipe;
	t_exec	*exec;

	pipe = NULL;
	tmp = NULL;
	exec = data->exec;
	while (exec)
	{
		tmp = malloc(sizeof(t_pipe));
		(tmp)->cmd = ft_split(exec->value, '\n');
		checkarg((tmp)->cmd);
		tmp->next = NULL;
		if (!files(exec, tmp, *env))
		{
			free_pipe(tmp);
			break ;
		}
		exec = exec->next;
		ft_lstadd_back2(&pipe, &tmp);
	}
	if (pipe)
		pipex(pipe, env, export);
	free_pipe (pipe);
}
