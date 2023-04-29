/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 09:47:21 by aatki             #+#    #+#             */
/*   Updated: 2023/04/29 12:48:20 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	here_docc(char *stop, int *ph)
{
	int		infile;
	char	*tmp;
	infile = 0;
	tmp = NULL;
	// infile = open("../.file.tmp", O_RDWR | O_CREAT, 0777);
	// if (infile < 0)
	// 	ft_errorb("file can't open", NULL, NULL, 1);
	write(1, "here_doc> ", 10);
	tmp = get_next_line(0);
	while (tmp)
	{
		if ((ft_strncmp(tmp, stop, ft_strlen(tmp) - 1) == 0) && ft_strlen(tmp)
			- 1 == ft_strlen(stop))
		{
			free(tmp);
			break ;
		}
		write(1, "here_doc> ", 10);
		write(ph[1], tmp, ft_strlen(tmp));
		free(tmp);
		tmp = get_next_line(0);
	}
	close(ph[1]);
	// infile = open("../.file.tmp", O_RDONLY);
	// if (infile < 0)
	// 	ft_errorb("file can't open", NULL, NULL, 1);
	if (dup2(ph[0], 0) < 0)
		ft_errorb("cant dup 2 in child one", NULL, NULL, 1);
	return (infile);
}

int	ft_infile(char *s)
{
	int	infile;

	infile = open(s, O_RDWR, 0644);
	if (infile < 0)
		ft_errorb("infile can't open", NULL, NULL, 1);
	return (infile);
}

int	ft_outfile(char *s)
{
	int	outfile;

	outfile = open(s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile < 0)
		ft_errorb("outfile can't open", NULL, NULL, 1);
	return (outfile);
}

void	duping(t_pipe *pipe, int *fd, int *ph)
{
	if (pipe->here_doc)
		here_docc(pipe->here_doc, ph);
	else if ((pipe)->infile)
	{
		if (dup2(ft_infile((pipe)->infile), 0) < 0)
			ft_errorb("cant dup 2 in child one", NULL, NULL, 1);
	}
	else if (dup2(*fd, 0) < 0)
		ft_errorb("cant dup 2 in child one", NULL, NULL, 1);
	if ((pipe)->outfile)
	{
		if (dup2(ft_infile((pipe)->outfile), 1) < 0)
			ft_errorb("cant dup 2 in child one", NULL, NULL, 1);
	}
	else if (dup2(ph[1], 1) < 0)
		ft_errorb("cant dup 2 in child one", NULL, NULL, 1);
}