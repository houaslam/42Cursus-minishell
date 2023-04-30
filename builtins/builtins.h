/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:32:03 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/30 11:19:04 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct t_cmd
{
	char			*cmd;
	struct t_cmd	*next_cmd;
}					t_cmd;

// typedef struct t_pipe
// {
// 	t_cmd			**c;
// 	char			*infile;
// 	char			*outfile;
// 	char			*here_doc;
// 	struct t_pipe	*next_pipe;
// }					t_pipe;

//execution
//builtins

int					g_exit_status;
void				ft_echo(char **str, int fd, char **env);
void				ft_pwd(int fd,char **env);
void				ft_exit(char **s);
void				ft_echo(char **s, int fd, char **env);
void				found(char *sa, char **env);
void				ft_cd(char **env, char **export,char **dir);
//
void				ft_errorb(char *s, char *s1, char *s2, int ext);
void				ft_env(char **env, int fd);
char				**ft_envo(char **env);
void				sort_export(char **env);
void				ft_export(char ***export, char ***env, char **arg, int fd);
int					here(char **env, char *arg);
void				found(char *sa, char **env);
void				ft_unset(char **env,char **arg);
char				**add_str(char **env, char *plus);
char				**ft_free(char **p);
char				**equal(char *s, char c);
void				affiche_export(char **export);
int					foundin(char *sa, char **env);
int					position(char **doubl, char *str);
void				change(char ***export, char ***env, char *arg, int cas);
int					ft_cases(char **env, char **export, char *arg);
int					check_arg(char *s);

#endif
