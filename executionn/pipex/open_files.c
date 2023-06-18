/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 09:47:21 by aatki             #+#    #+#             */
/*   Updated: 2023/06/18 14:01:55 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_infile(char *s)
{
	int	infile;

	infile = open(s, O_RDWR, 0644);
	if (infile < 0)
	{
		ft_errorb("bash: ", s, "no such file or directory\n", 1);
		return (-1);
	}
	return (infile);
}

int	ft_outfile(char *s)
{
	int	outfile;

	outfile = open(s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile < 0)
	{
		ft_errorb("bash: ", s, "no such file or directory\n", 1);
		return (-1);
	}
	return (outfile);
}

int	duping(t_pipe *pipe, int fd, int *ph, int h)
{
	if (pipe->her_docin && h)
		return (after_here_doc(pipe, pipe->here_doc, ph));
	else if ((pipe)->infile)
	{
		ph[0] = dup(ft_infile((pipe)->infile));
		if (dup2(ph[0], 0) < 0)
			return (ft_errorb("cant dup  infile\n", NULL, NULL, 1));
	}
	else if (dup2(fd, 0) < 0)
		return (ft_errorb("cant dup pipe[0]\n", NULL, NULL, 1));
	if ((pipe)->outfile)
	{
		ph[1] = dup(ft_outfile((pipe)->outfile));
		if (dup2(ph[1], 1) < 0)
			return (ft_errorb("cant dup outfile\n", NULL, NULL, 1));
	}
	else if ((pipe)->here_doc_out)
	{
		ph[1] = dup(ft_outfile_heredoc((pipe)->here_doc_out));
		if (dup2(ph[1], 1) < 0)
			return (ft_errorb("cant dup outfile\n", NULL, NULL, 1));
	}
	else if (dup2(ph[1], 1) < 0)
		return (ft_errorb("cant dup pipe[1]\n", NULL, NULL, 1));
	return (1);
}
