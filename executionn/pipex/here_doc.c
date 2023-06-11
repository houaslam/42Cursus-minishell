/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:47:12 by aatki             #+#    #+#             */
/*   Updated: 2023/06/11 21:27:09 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// void	here_docc(t_pipe *pipe, int *ph)
// {
// 	int		infile;
// 	char	*tmp;

// 	infile = 0;
// 	tmp = NULL;
// 	infile = open("../../.file.tmp", O_RDWR | O_CREAT, O_TRUNC,0777);
// 	if (infile < 0)
// 		ft_errorb("file can't open\n", NULL, NULL, 1);
// 	write(1, "here_doc>", 9);
// 	tmp = get_next_line(0);
// 	while (tmp)
// 	{
// 		if ((ft_strncmp(tmp, pipe->here_doc, ft_strlen(tmp) - 1) == 0)
// 			&& ft_strlen(tmp) - 1 == ft_strlen(pipe->here_doc))
// 		{
// 			free(tmp);
// 			break ;
// 		}
// 		write(1, "here_doc>", 9);
// 		write(infile, tmp, ft_strlen(tmp));
// 		free(tmp);
// 		tmp = get_next_line(0);
// 	}
// 	close(infile);
// 	after_here_doc(pipe, ph, infile);
// }

int	here_docc(t_pipe *pip, int *ph)
{
	char	*tmp;
	int		p[2];

	if(pipe(p)<0)
		printf("!! ERROR !!\n");
	while (1)
	{
		write(1, "here_doc>", 9);
		tmp = get_next_line(0);
		if(!tmp)
			break;
		if ((ft_strncmp(tmp, pip->here_doc, ft_strlen(tmp) - 1) == 0)
			&& ft_strlen(tmp) - 1 == ft_strlen(pip->here_doc))
		{
			free(tmp);
			break ;
		}
		write(p[1], tmp, ft_strlen(tmp));
		free(tmp);
	}
	close(p[1]);
	return (after_here_doc(pip, p,ph));
}

int	after_here_doc(t_pipe *pipe, int *p,int *ph)
{
	char	*s;

	if (dup2(p[0], 0) < 0)
	{
		ft_errorb("cant dup in here_doc\n", NULL, NULL, 1);
		return 0;
	}
	if ((pipe)->here_doc_out)
		s = (pipe)->here_doc_out;
	else if ((pipe)->outfile)
		s = (pipe)->outfile;
	else
		s = NULL;
	if (s)
	{
		if (dup2(ft_outfile_heredoc(s), 1) < 0)
		{
			ft_errorb("cant dup outfile\n", NULL, NULL, 1);
			return 0;
		}
	}
	else if (dup2(ph[1], 1) < 0)
	{
		ft_errorb("cant d1up pipe[1]\n", NULL, NULL, 1);
		return 0;
	}
	return 1;
}

int	ft_outfile_heredoc(char *s)
{
	int	outfile;

	outfile = open(s, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (outfile < 0)
	{
		ft_errorb("outfile here_doc can't open\n", NULL, NULL, 1);
		return -1;
	}
	return (outfile);
}
