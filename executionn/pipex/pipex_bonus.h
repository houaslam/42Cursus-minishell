/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:19:23 by aatki             #+#    #+#             */
/*   Updated: 2023/06/12 17:53:29 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../../libft/libft.h"
# include "../builtins/builtins.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <time.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_pipe
{
	char			**cmd;
	char			*infile;
	char			*outfile;
	char			*here_doc;
	char			*here_doc_out;
	struct s_pipe	*next;
}					t_pipe;

char				*check_env(char **env, char **cmd);
char				*ft_strjoin(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				**ft_free(char **p);
int					here_doc(char **av, int *infile);
int					here_docc(t_pipe *pipe, int *ph);
void				here_doc_child(int *fd, char **av, char **env);
void				execution(char **cmd, char **env);
void				herep(char **av, char **env, int ac);
void				child_two(int *fd, char **av, char **env, int ac);
int					duping(t_pipe *pipe, int fd, int *ph);
int					builtin(char *s);
void				builtin_exec(t_pipe *pipe, char ***env, char ***export);
void				child_two2(t_pipe *pipee, int *fd, char ***env,
						char ***export);
void				child_one(t_pipe *pipee, char ***env, char ***export);
int					ft_infile(char *s);
int					ft_outfile(char *s);
void				command(char **cmd_arg, char ***export, int fdout,
						char ***env);
void				pipex(t_pipe *pipe, char ***env, char ***export);
int					after_here_doc(t_pipe *pipe, int *ph, int *p);
int					builtin(char *s);
void				builtin_exec(t_pipe *pipe, char ***env, char ***export);
int					ft_outfile_heredoc(char *s);
void				ft_errorb(char *s, char *s1, char *s2, int ext);

#endif
