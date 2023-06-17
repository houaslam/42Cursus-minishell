/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:32:03 by houaslam          #+#    #+#             */
/*   Updated: 2023/06/17 18:25:03 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../libft/libft.h"
# include "../../parsing/minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		g_exit_status;

//builtins
void		ft_pwd(int fd);
void		ft_exit(char **s);
void		ft_echo(char **s);
int			ft_cd(char **env, char **export, char **dir);
void		ft_env(char **env, int fd, char **arg);
void		ft_unset(char **env, char **arg, int flag);
int			ft_export(char ***export, char ***env, char **arg, int i);

//function
void		found(char *sa, char **env);
void		orb(char *s, char *s1, char *s2, int ext);
char		**ft_envo(char **env);
void		sort_export(char **env);
int			here(char **env, char *arg);
void		found(char *sa, char **env);
char		**add_str(char **env, char *plus);
char		**ft_free(char **p);
char		**equal(char *s, int *i);
void		affiche_export(char **export);
int			foundin(char *sa, char **env);
int			position(char **doubl, char *str);
void		change(char ***export, char ***env, char *arg, int cas);
int			ft_cases(char **env, char **export, char *arg);
int			check_arg(char *s);
void		ft_error(char *s, char *s1, char *s2);
int			ft_errorb(char *s, char *s1, char *s2, int ext);
char		*recherche(char **env, char *s);
void		ctrl_ch(int i);
int			the_plus(char **export, char **sp);
void		checkarg(char **arg);
int			other_file(t_exec *exec, t_pipe *tmp);
int			other_file2(t_exec *exec, t_pipe *tmp);
#endif
