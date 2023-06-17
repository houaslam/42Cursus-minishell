/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:47:12 by aatki             #+#    #+#             */
/*   Updated: 2023/06/17 22:36:41 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ctrl_ch(int i)
{
	if (i == SIGINT)
	{
		write(1, "HHH\n", 4);
		exit(0);
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
	return (ret);
}

int *the_while2(t_pipe *norm)
{
	int id;

	id = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (id == 0)
	{
		signal(SIGINT, ctrl_ch);
		while (1)
		{
			norm->infile = readline("here doc>");
			if (!norm->infile)
				break ;
			if (norm->her_docin != 1)
				norm->infile = general_expand(norm->infile, norm->cmd);
			norm->infile = ft_strjoin_free(norm->infile, "\n");
			if ((ft_strncmp(norm->infile, norm->outfile, \
			ft_strlen(norm->infile) - 1) == 0) && ft_strlen(norm->infile)
				- 1 == ft_strlen(norm->outfile))
			{
				free(norm->infile);
				break ;
			}
			write(norm->here_doc[1], norm->infile, ft_strlen(norm->infile));
			free(norm->infile);
		}
		close(norm->here_doc[1]);
		exit(0);
	}
	wait(NULL);
	signal(SIGINT, ctrl_c);
	return (norm->here_doc);
}

int	*here_docc(char *str, char **env, int expand)
{
	char	*tmp;
	t_pipe	*norm;
	int		*p;

	tmp = NULL;
	p = malloc(sizeof(int *) * 2);
	if (pipe(p) < 0)
		ft_errorb("cant pipe in here_doc\n", NULL, NULL, 1);
	norm = malloc(sizeof(t_pipe));
	norm->cmd=env;
	norm->infile=tmp;
	norm->outfile=str;
	norm->here_doc=p;
	norm->her_docin=expand;
	return (the_while2(norm));
}

int	after_here_doc(t_pipe *pipe, int *p, int *ph)
{
	int	s;

	s = -1;
	(void)p;
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
