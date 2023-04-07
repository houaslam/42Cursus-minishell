/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_linked_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:45:15 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/07 21:37:37 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_exec(t_exec **lst, t_exec *new)
{
	t_exec	*last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		last = ft_lstlast_exec(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

t_exec	*ft_lstnew_exec(char *value, int type)
{
	t_exec	*node;

	node = malloc(sizeof(t_exec));
	if (!node)
		return (NULL);
	node->value = malloc(ft_strlen(value) + 1);
	if (!node->value)
	{
		free(node);
		return (NULL);
	}
	//change this one to ft_strcpy
	strcpy(node->value, value);
	node->type = type;
	node->next = NULL;
	return (node);
}

int	ft_lstsize_exec(t_exec *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_exec	*ft_lstlast_exec(t_exec *lst)
{
	t_exec	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
