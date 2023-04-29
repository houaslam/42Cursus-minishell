/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transmetter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:13:31 by aatki             #+#    #+#             */
/*   Updated: 2023/04/29 15:53:09 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back2(t_pipe **lst, t_pipe *new)
{
	t_pipe	*temp;

	if(!new)
		return;
	if(*lst)
	{
		temp = (*lst);
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		*lst = new;
}

void transmettre(t_data *data,char ***env,char ***export)
{
	t_pipe	*tmp;
    t_pipe *pipe;

	pipe = NULL;
	tmp = NULL;
	while (data->exec)
	{
		tmp = malloc(sizeof(t_pipe));
		(tmp)->cmd = ft_split(data->exec->value, '*');
		while (data->exec->file)
		{
			if (data->exec->file->type == 2)
				(tmp)->infile = data->exec->file->file;
			if (data->exec->file->type == 3 || data->exec->file->type == 6)
				(tmp)->outfile = data->exec->file->file;
			if (data->exec->file->type == 5)
				(tmp)->here_doc = data->exec->file->file;
			data->exec->file = data->exec->file->next;
		}
		data->exec = data->exec->next;
		ft_lstadd_back2(&pipe, tmp);
	}
	exit_status = data->g_exit_status;
	//ft_free(data);
	printf("**%s\n***", tmp->cmd[0]);
	printf("**%s\n***", tmp->cmd[1]);
	printf("**%s\n***", tmp->cmd[2]);
    pipex(pipe,env,export);
}

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*p;
	size_t			k;

	if (!s)
		return (NULL);
	k = ft_strlen((char *)s);
	if (start > k)
		return (ft_strdup(""));
	if (len > ft_strlen((char *)s + start))
		len = ft_strlen((char *)s + start);
	p = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	if (!p)
		return (NULL);
	while (i < len && start < k)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}


