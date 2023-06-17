/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:47:12 by aatki             #+#    #+#             */
/*   Updated: 2023/06/17 23:29:47 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ctrl_ch(int i)
{
	if (i == SIGINT)
	{
		write(1, "\n", 1);
		exit(22);
	}
}

char	*expand_h(char *str, char **env)
{
	char	*save;
	char	*ptr;

	ptr = ft_substr(str, 1, ft_strlen(str) - 1);
	save = find_ex(ptr, env);
	free(ptr);
	free(str);
	return (save);
}

void	norm_func(t_pipe *norm)
{
	while (1)
	{
		signal(SIGINT, ctrl_ch);
		norm->infile = readline("here doc>");
		if (!norm->infile)
			break ;
		if (norm->her_docin != 1)
			norm->infile = general_expand(norm->infile, norm->cmd);
		norm->infile = ft_strjoin_free(norm->infile, "\n");
		if ((ft_strncmp(norm->infile, norm->outfile, ft_strlen(norm->infile)
					- 1) == 0) && ft_strlen(norm->infile)
			- 1 == ft_strlen(norm->outfile))
		{
			free(norm->infile);
			break ;
		}
		write(norm->here_doc[1], norm->infile, ft_strlen(norm->infile));
		free(norm->infile);
	}
}

int	the_while2(t_pipe *norm)
{
	int	id;
	int	get;
	int	ret;

	id = fork();
	// signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
	if (id == 0)
	{
		signal(SIGINT, ctrl_ch);
		norm_func(norm);
		close(norm->here_doc[1]);
		exit(0);
	}
	// signal(SIGINT, ctrl_c);
	ret = dup(norm->here_doc[0]);
	close(norm->here_doc[1]);
	close(norm->here_doc[0]);
	waitpid(-1, &get, 0);
	if (WIFEXITED(get))
		get = WEXITSTATUS(get);
	if (ret == 22)
		return (-1);
	return (ret);
}

int	here_docc(char *str, char **env, int expand)
{
	char	*tmp;
	t_pipe	*norm;
	int		*p;

	tmp = NULL;
	p = malloc(sizeof(int *) * 2);
	if (pipe(p) < 0)
		ft_errorb("cant pipe in here_doc\n", NULL, NULL, 1);
	norm = malloc(sizeof(t_pipe));
	norm->cmd = env;
	norm->infile = tmp;
	norm->outfile = str;
	norm->here_doc = p;
	norm->her_docin = expand;
	return (the_while2(norm));
}
