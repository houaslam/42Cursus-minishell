/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transmetter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:13:31 by aatki             #+#    #+#             */
/*   Updated: 2023/04/29 11:40:21 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*transmettre(t_data *data)
{
	t_pipe	*tmp;

	while (data)
	{
		tmp = malloc(sizeof(t_pipe));
		(tmp)->cmd = data->exec->cmd;
		while (data->exec->file)
		{
			if (data->exec->file->type == 2)
				(tmp)->infile = data->exec->file->file;
			if (data->exec->file->type == 3 || data->exec->file->type == 6)
				(tmp)->outfile = data->exec->file->file;
			if (data->exec->file->type == 5)
				(tmp)->here_doc = data->exec->file->file;
		}
		tmp->next = NULL;
		ft_lstadd_back(pipe, tmp);
	}
    exit_status=data->g_exit_status;
}
