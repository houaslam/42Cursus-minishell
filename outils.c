/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:39:45 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/16 05:17:49 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_realloc(void *ptr, size_t size)
// {
// 	char	*res;

// 	res = malloc(sizeof(ptr) + size);
// 	ft_memcpy(res, ptr, ft_strlen(ptr));
// 	free(ptr);
// 	return (ptr);
// }

void	free_exec(t_exec **exec)
{
	t_exec	*next;
	t_exec	*head;

	head = *exec;
	while (*exec)
	{
		next = (*exec)->next;
		free((*exec)->value);
		free(*exec);
		*exec = next;
	}
	head = NULL;
}

char	*seach_env_value(char *str, t_data *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->name))
			return (tmp->path);
		tmp = tmp->next;
	}
	return (NULL);
}

int	print_token_er(t_data *data)
{
	printf("ERROR\n");
	free_exec(&data->exec);
	return (ft_strlen(data->s));
}

void	aff1(t_exec *exec, t_file *file)
{
	t_exec	*tmp;
	t_file	*tmp_;

	tmp = exec;
	tmp_ = file;
	while (tmp)
	{
		printf("---->type = %d value = |%s|\n", tmp->type, tmp->value);
		while (tmp_)
		{
			printf("---->type = %d file = |%s|\n", tmp_->type, tmp_->file);
			tmp_ = tmp_->next;
		}
		tmp = tmp->next;
	}
	printf("HERE\n");
}

void	aff2(t_file *env)
{
	t_file	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("---->type = %d file = |%s|\n", tmp->type, tmp->file);
		tmp = tmp->next;
	}
}
