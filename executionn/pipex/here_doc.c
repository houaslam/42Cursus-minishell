/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:47:12 by aatki             #+#    #+#             */
/*   Updated: 2023/06/18 16:02:15 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ctrl_ch(int i)
{
	if (i == SIGINT)
	{
		write(1, "\n", 1);
		exit(0);
	}
}

void	ctrl_h(int i)
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

int	here_docc(char *str, char **env, int expand)
{
	char	*tmp;
	t_pipe	*norm;
	int		*p;
	int		ret;

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
	ret = the_while2(norm);
	free (norm);
	return (ret);
}
