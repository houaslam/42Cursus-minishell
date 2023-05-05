/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 09:47:21 by aatki             #+#    #+#             */
/*   Updated: 2023/05/05 13:46:02 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	here_docc(t_pipe *pipe, int *ph)
{
	int		infile;
	char	*tmp;
	infile = 0;
	tmp = NULL;
	infile = open("../.file.tmp", O_RDWR | O_CREAT, 0777);
	if (infile < 0)
		ft_errorb("file can't open\n", NULL, NULL, 1);
	write(1, "here_doc> ", 10);
	tmp = get_next_line(0);
	while (tmp)
	{
		if ((ft_strncmp(tmp, pipe->here_doc, ft_strlen(tmp) - 1) == 0) && ft_strlen(tmp)
			- 1 == ft_strlen(pipe->here_doc))
		{
			free(tmp);
			break ;
		}
		write(1, "here_doc> ", 10);
		write(infile, tmp, ft_strlen(tmp));
		free(tmp);
		tmp = get_next_line(0);
	}
	close(infile);
	// infile = open("../.file.tmp", O_RDONLY);
	// if (infile < 0)
	// 	ft_errorb("file can't open", NULL, NULL, 1);
	if (dup2(ph[0], 0) < 0)
		ft_errorb("cant dup in here_doc\n", NULL, NULL, 1);
	after_here_doc(pipe,ph);
	return (infile);
}

int	ft_infile(char *s)
{
	int	infile;

	infile = open(s, O_RDWR, 0644);
	if (infile < 0)
		ft_errorb("infile can't open\n", NULL, NULL, 1);
	return (infile);
}

int	ft_outfile(char *s)
{
	int	outfile;

	outfile = open(s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (outfile < 0)
		ft_errorb("outfile can't open\n", NULL, NULL, 1);
	return (outfile);
}

int	ft_outfile_heredoc(char *s)
{
	int	outfile;

	outfile = open(s, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (outfile < 0)
		ft_errorb("outfile here_doc can't open\n", NULL, NULL, 1);
	return (outfile);
}

void after_here_doc(t_pipe *pipe,int *ph)
{
	char *s;
	if((pipe)->here_doc_out )
			s = (pipe)->here_doc_out;
		else if ((pipe)->outfile)
			s = (pipe)->outfile;
		else
			s = NULL;
		if (s)
		{
			ph[1]=dup(ft_outfile_heredoc((pipe)->here_doc_out));
			if (dup2(ph[1], 1) < 0)
				ft_errorb("cant dup outfile\n", NULL, NULL, 1);
		}
		else if (dup2(2, 1) < 0)
				ft_errorb("cant dup pipe[1]\n", NULL, NULL, 1);
}

void	duping(t_pipe *pipe, int *fd, int *ph)
{
	
	if (pipe->here_doc)
		here_docc(pipe, ph);
	else if ((pipe)->infile)
	{
		ph[0]=dup(ft_infile((pipe)->infile));
		if (dup2(ph[0], 0) < 0)
			ft_errorb("cant dup  infile\n", NULL, NULL, 1);
	}
	else if (dup2(*fd, 0) < 0)
		ft_errorb("cant dup pipe[0]\n", NULL, NULL, 1);
	if ((pipe)->outfile)
	{
		ph[1]=dup(ft_outfile((pipe)->outfile));
		if (dup2(ph[1], 1) < 0)
			ft_errorb("cant dup outfile\n", NULL, NULL, 1);
	}
	else if ((pipe)->here_doc_out)
	{
		ph[1]=dup(ft_outfile_heredoc((pipe)->here_doc_out));
		if (dup2(ph[1], 1) < 0)
			ft_errorb("cant dup outfile\n", NULL, NULL, 1);
	}
	else if (dup2(ph[1], 1) < 0)
		ft_errorb("cant dup pipe[1]\n", NULL, NULL, 1);
}






































// void	duping(t_pipe *pipe, int *fd, int *ph)
// {
//     int fd_in = 0; // to store the original value of ph[0]
//     int fd_out = 1; // to store the original value of ph[1]

// 	if (pipe->here_doc)
// 		here_docc(pipe->here_doc, ph);
// 	else if ((pipe)->infile)
// 	{
// 		fd_in = dup(ph[0]); // save the original value of ph[0]
// 		ph[0] = ft_infile((pipe)->infile);
// 		if (dup2(ph[0], 0) < 0)
// 			ft_errorb("cant dup  infile\n", NULL, NULL, 1);
//         close(ph[0]); // close the file descriptor returned by ft_infile()
// 	}
// 	else if (dup2(*fd, 0) < 0)
// 		ft_errorb("cant dup pipe[0]\n", NULL, NULL, 1);
// 	if ((pipe)->outfile)
// 	{
// 		fd_out = dup(ph[1]); // save the original value of ph[1]
// 		ph[1] = ft_outfile((pipe)->outfile);
// 		if (dup2(ph[1], 1) < 0)
// 			ft_errorb("cant dup outfile\n", NULL, NULL, 1);
//         close(ph[1]); // close the file descriptor returned by ft_outfile()
// 	}
// 	else if (dup2(ph[1], 1) < 0)
// 		ft_errorb("cant dup pipe[1]\n", NULL, NULL, 1);

//     // call command() with the modified file descriptors
//     //command(pipe->cmd, export, ph[1], env);

//     // restore the original file descriptors
//     if ((pipe)->infile)
//     {
//         if (dup2(fd_in, 0) < 0)
//             ft_errorb("cant restore original ph[0]\n", NULL, NULL, 1);
//         close(fd_in);
//     }
//     else if (dup2(*fd, 0) < 0)
//         ft_errorb("cant dup pipe[0]\n", NULL,NULL,2);
// }