/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:47:12 by aatki             #+#    #+#             */
/*   Updated: 2023/06/14 20:24:00 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ctrl_ch(int i)
{
	if (i == SIGINT)
	{
		exit(0);
		// printf("\n");
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
}

int	*here_docc(char *str)
{
	char	*tmp;
	int		p[2];

	if (pipe(p) < 0)
		ft_errorb("cant pipe in here_doc\n", NULL, NULL, 1);
	while (1)
	{
		tmp = readline("here doc>");
		if (!tmp)
			break ;
		tmp=ft_strjoin_free(tmp,"\n");
		if ((ft_strncmp(tmp, str, ft_strlen(tmp) - 2) == 0)
			&& ft_strlen(tmp) - 1 == ft_strlen(str))
		{
			free(tmp);
			break ;
		}
		write(p[1], tmp, ft_strlen(tmp));
		free(tmp);
	}
	close(p[1]);
	return (p);
}

int	after_here_doc(t_pipe *pipe, int *p, int *ph)
{
	int s;

	if (dup2(p[0], 0) < 0)
	{
		ft_errorb("cant dup in here_doc\n", NULL, NULL, 1);
		return (0);
	}
	if ((pipe)->here_doc_out)
		s = ft_outfile_heredoc(pipe->here_doc_out);
	else if ((pipe)->outfile)
		s = ft_outfile(pipe->outfile);
	else
		s = -1;
	if (s > 0)
	{
		if (dup2(s, 1) < 0)
		{
			ft_errorb("cant dup outfile\n", NULL, NULL, 1);
			return (0);
		}
	}
	else if (dup2(ph[1], 1) < 0)
	{
		ft_errorb("cant d1up pipe[1]\n", NULL, NULL, 1);
		return (0);
	}
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
