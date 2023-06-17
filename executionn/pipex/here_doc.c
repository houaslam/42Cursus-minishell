/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:47:12 by aatki             #+#    #+#             */
/*   Updated: 2023/06/17 17:10:32 by aatki            ###   ########.fr       */
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

int *the_while2(char *str, char *tmp, int *p)
{
	(void)str;
	(void) tmp;
	int id=fork();
	if (id == 0)
	{
		while (1)
		{
			signal(SIGINT, ctrl_ch);
			tmp = readline("here doc>");
			if (!tmp)
				break ;
			tmp = ft_strjoin_free(tmp, "\n");
			if ((ft_strncmp(tmp, str, ft_strlen(tmp) - 1) == 0) && ft_strlen(tmp)
				- 1 == ft_strlen(str))
			{
				free(tmp);
				break ;
			}
			write(p[1], tmp, ft_strlen(tmp));
			free(tmp);
		}
		close(p[1]);
		exit(0);
	}
	wait(NULL);
	return (p);
}

int	*here_docc(char *str)
{
	char	*tmp;

	tmp = NULL;
	int *p;
	p = malloc(sizeof(int *) * 2);
	if (pipe(p) < 0)
		ft_errorb("cant pipe in here_doc\n", NULL, NULL, 1);
	printf("p in heredoc  %d\n",p[0]);
	return (the_while2(str, tmp, p));
}

int	after_here_doc(t_pipe *pipe, int *p, int *ph)
{
	int	s;

	s = -1;
	(void)p;
	// dprintf(2,"p in here  %d\n",p[0]);
	// dprintf(2,"sec %d\n",pipe->here_doc[0]);
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
