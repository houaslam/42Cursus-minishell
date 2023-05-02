/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:19:23 by aatki             #+#    #+#             */
/*   Updated: 2023/05/01 14:52:28 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../builtins/builtins.h"
# include"../../libft/libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

typedef struct s_pipe
{
	char			**cmd;
	char			*infile;
	char			*outfile;
	char			*here_doc;
	struct s_pipe	*next;
}					t_pipe;

char				*check_env(char **env, char **cmd);
//char				**ft_split(char *s, char c);
char				*ft_strjoin(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				**ft_free(char **p);
//int					ft_strlen(char *s);
int					here_doc(char **av, int *infile);
//void	ft_error(char *s);
int					here_docc(char *stop, int *ph);
void				here_doc_child(int *fd, char **av, char **env);
void				execution(char **cmd, char **env);
void				herep(char **av, char **env, int ac);
void				child_two(int *fd, char **av, char **env, int ac);
void				duping(t_pipe *pipe, int *fd, int *ph);
int					builtin(char *s);
void				builtin_exec(t_pipe *pipe, char ***env, char ***export);
void				child_two2(t_pipe *pipee, int *fd, char ***env,
						char ***export);
void				child_one(t_pipe **pipee, int *fd, char ***env,
						char ***export);
int					ft_infile(char *s);
int					ft_outfile(char *s);
void				command(char **cmd_arg, char ***export, int fdout,
						char ***env);
void				pipex(t_pipe *pipe, char ***env, char ***export);
#endif