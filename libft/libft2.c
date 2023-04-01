/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:45:15 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/01 21:38:41 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		printf("new = %s\n", new->name);
		last = ft_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

t_env	*ft_lstnew(char *name, char *path)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	//change this one
	node->path = malloc(strlen(path) + 1);
	if (!node->path)
	{
		free(node);
		return (NULL);
	}
	node->name = malloc(strlen(name) + 1);
	if (!node->name)
	{
		free(node->path);
		free(node);
		return (NULL);
	}
	//change this one
	strcpy(node->path, path);
	strcpy(node->name, name);
	node->next = NULL;
	return (node);
}

int	ft_lstsize(t_env *lst)
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


t_env	*ft_lstlast(t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
