/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:46:22 by aatki             #+#    #+#             */
/*   Updated: 2023/06/17 18:38:47 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"


// int	other_file2(t_exec *exec, t_pipe *tmp)
// {
// 	if (exec->file->type == 6)
// 	{
// 		if (tmp->outfile)
// 			tmp->outfile = NULL;
// 		open(exec->file->file, O_CREAT, 0644);
// 		(tmp)->here_doc_out = exec->file->file;
// 	}
// 	else if (exec->file->type == 60)
// 	{
// 		if (tmp->here_doc)
// 			tmp->here_doc = NULL;
// 		if (open(exec->file->file, O_RDONLY, 0644) < 0)
// 		{
// 			ft_errorb("bash: ", exec->file->file, \
// 			": No such file or directory\n", 1);
// 			return (0);
// 		}
// 		(tmp)->infile = exec->file->file;
// 	}
// 	return (1);
// }

int	other_file(t_exec *exec, t_pipe *tmp)
{
	if (exec->file->type == 5)
	{
		if (tmp->infile)
			tmp->infile = NULL;
		tmp->here_doc = here_docc(exec->file->file);
		tmp->her_docin = dup(tmp->here_doc[0]);
		close(tmp->here_doc[1]);
		close(tmp->here_doc[0]);
		free(tmp->here_doc);
	}
	else
		return (other_file2(exec, tmp));
}
