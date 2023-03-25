/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:45:15 by houaslam          #+#    #+#             */
/*   Updated: 2023/03/25 12:54:11 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
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
	// node->path = malloc(sizeof(char *));
	node->path = path;
	node->name = name;
    // printf("%s\n", node->name);
	// node->name = malloc(sizeof(char *));
	// strcpy(node->name, name);
	// strcpy(node->path, path);
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
