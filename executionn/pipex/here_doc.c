/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:47:12 by aatki             #+#    #+#             */
/*   Updated: 2023/06/15 01:56:34 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ctrl_ch(int i)
{
	if (i == SIGINT)
	{
		printf("HERE\n");
		g_signals.save = g_signals.exit_status;
		g_signals.exit_status = -1;
		return ;
	}
}

int	*the_while2(char *str, int fd, char *tmp, int *p)
{
	while (1)
	{
		tmp = readline("here doc>");
		if (!tmp)
			break ;
		if (g_signals.exit_status == -1)
		{
			printf("HEREFFFF\n");
			g_signals.exit_status = g_signals.save;
			return (p);
		}
		tmp = ft_strjoin_free(tmp, "\n");
		if ((ft_strncmp(tmp, str, ft_strlen(tmp) - 2) == 0) && ft_strlen(tmp)
			- 1 == ft_strlen(str))
		{
			free(tmp);
			break ;
		}
		write(fd, tmp, ft_strlen(tmp));
		free(tmp);
	}
	close(p[1]);
	return (p);
}

int	*here_docc(char *str)
{
	char	*tmp;
	int		*p;

	tmp = NULL;
	p = malloc(sizeof(int *) * 2);
	if (pipe(p) < 0)
		ft_errorb("cant pipe in here_doc\n", NULL, NULL, 1);
	signal(SIGINT, ctrl_ch);
	return (the_while2(str, p[1], tmp, p));
}

int	after_here_doc(t_pipe *pipe, int *p, int *ph)
{
	int	s;

	s = -1;
	if (dup2(p[0], 0) < 0)
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
