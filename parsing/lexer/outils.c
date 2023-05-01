/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:39:45 by houaslam          #+#    #+#             */
/*   Updated: 2023/05/01 13:50:09 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	print_token_er(t_data *data, int status, t_exec *tmp)
{
	printf("ERROR\n");
	free_exec(&data->exec);
	if (tmp)
		free_exec(&tmp);
	data->g_exit_status = status;
	printf("exit status = %d\n", data->g_exit_status);
	return (ft_strlen(data->s) - 1);
}

void	aff1(t_exec *exec, t_file *file)
{
	t_exec	*tmp;
	t_file	*tmp_;

	tmp = exec;
	tmp_ = file;
	while (tmp != NULL)
	{
		printf("---->type = %d value = |%s|\n", tmp->type, tmp->value);
		while (tmp_ != NULL && tmp_->file[0] != '\0')
		{
			printf("---->type = %d file = |%s|\n", tmp_->type, tmp_->file);
			tmp_ = tmp_->next;
		}
		tmp = tmp->next;
	}
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
