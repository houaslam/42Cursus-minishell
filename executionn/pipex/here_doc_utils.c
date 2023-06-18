/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 21:08:11 by aatki             #+#    #+#             */
/*   Updated: 2023/06/18 17:27:29 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	after_here_doc(t_pipe *pipe, int *p, int *ph)
{
	int	s;

	s = -1;
	(void)p;
	if (pipe->her_docin == -1)
		return (0);
	if (dup2(pipe->her_docin, 0) < 0)
		return (ft_errorb("cant dup in here_doc\n", NULL, NULL, 1));
	if ((pipe)->here_doc_out)
		s = ft_outfile_heredoc(pipe->here_doc_out);
	else if ((pipe)->outfile)
		s = ft_outfile(pipe->outfile);
	if (s > 0)
	{
		if (dup2(s, 1) < 0)
			return (ft_errorb("cant dup outfile\n", NULL, NULL, 1));
	}
	else if (dup2(ph[1], 1) < 0)
		return (ft_errorb("cant d1up pipe[1]\n", NULL, NULL, 1));
	return (1);
}

int	ft_outfile_heredoc(char *s)
{
	int	outfile;

	outfile = open(s, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (outfile < 0)
	{
		ft_errorb("outfile here_doc can't open\n", NULL, NULL, 1);
		return (-1);
	}
	return (outfile);
}

char	*general_expand(char *str, char **env)
{
	char	**s;
	char	*save;
	char	*ret;
	int		i;

	s = ft_split(str, ' ');
	i = 0;
	ret = NULL;
	while (s[i])
	{
		if (s[i][0] == '$')
		{
			save = expand_h(s[i], env);
			s[i] = save;
		}
		ret = ft_strjoin_free(ret, s[i]);
		if (ret[i + 1])
			ret = ft_strjoin_free(ret, " ");
		i++;
	}
	free(str);
	ft_free(s);
	return (ret);
}

int	return_func(t_pipe *norm, int id)
{
	int	get;
	int	ret;

	waitpid(id, &get, 0);
	if (WIFEXITED(get))
		get = WEXITSTATUS(get);
	ret = dup(norm->here_doc[0]);
	close(norm->here_doc[1]);
	close(norm->here_doc[0]);
	free(norm->here_doc);
	if (get == 22)
	{
		close(ret);
		g_exit_status = 1;
		return (-1);
	}
	return (ret);
}

int	the_while2(t_pipe *norm)
{
	int	id;

	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, ctrl_h);
		norm_func(norm);
		close(norm->here_doc[1]);
		exit(0);
	}
	return (return_func(norm, id));
}
