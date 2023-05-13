/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 00:39:45 by houaslam          #+#    #+#             */
/*   Updated: 2023/05/13 10:51:18 by houaslam         ###   ########.fr       */
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

void	free_file(t_file **file)
{
	t_file	*next;
	t_file	*head;

	head = *file;
	while (*file)
	{
		next = (*file)->next;
		free((*file)->file);
		free(*file);
		*file = next;
	}
	head = NULL;
}

char	*find_ex(char *sa, char **env)
{
	int		i;
	char	*s;

	s = NULL;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], sa, ft_strlen(sa))
			&& env[i][ft_strlen(sa)] == '=')
			s = ft_substr(env[i], ft_strlen(sa) + 1 \
			, ft_strlen(env[i]) - ft_strlen(sa));
		i++;
	}
	return (s);
}

t_exec	*print_token_er(t_data *data, int status, char *s1)
{
	write(2, "bash: syntax error near unexpected token", 41);
	if (s1)
		write(2, s1, ft_strlen(s1));
	g_exit_status = status;
	data->g_exit_status = 1;
	return (ft_lstlast_exec(data->lexer));
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
		while (tmp_ != NULL)
		{
			printf("---->type = %d file = |%s|\n", tmp_->type, tmp_->file);
			tmp_ = tmp_->next;
		}
		tmp = tmp->next;
	}
}
