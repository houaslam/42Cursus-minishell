/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transmetter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:13:31 by aatki             #+#    #+#             */
/*   Updated: 2023/04/29 21:23:47 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	transmettre(t_data *data, char ***env, char ***export)
{
	t_pipe	*tmp;
	t_pipe	*pipe;

	pipe = NULL;
	tmp = NULL;
	while (data->exec)
	{
		tmp = malloc(sizeof(t_pipe));
		(tmp)->cmd = ft_split(data->exec->value, '*');
		(tmp)->infile = NULL;
		(tmp)->outfile = NULL;
		(tmp)->here_doc = NULL;
		while (data->exec->file)
		{
			printf("<%d>cccgvj\n", data->exec->file->type);
			if (data->exec->file->type == 60)
				(tmp)->infile = data->exec->file->file;
			else if (data->exec->file->type == 62 || data->exec->file->type == 6)
				(tmp)->outfile = data->exec->file->file;
			else if (data->exec->file->type == 5)
				(tmp)->here_doc = data->exec->file->file;
			data->exec->file = data->exec->file->next;
		}
		tmp->next = NULL;
		data->exec = data->exec->next;
		ft_lstadd_back2(&pipe, tmp);
	}
	g_exit_status = data->g_exit_status;
	//ft_free(data);
	pipex(pipe, env, export);
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
