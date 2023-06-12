/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:32:03 by houaslam          #+#    #+#             */
/*   Updated: 2023/06/12 13:57:59 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		g_exit_status;

void	ft_echo(char **str, int fd, char **env);
void	ft_pwd(int fd);
void	ft_exit(char **s);
void	ft_echo(char **s, int fd, char **env);
void	found(char *sa, char **env);
void	ft_cd(char **env, char **export, char **dir);
void	orb(char *s, char *s1, char *s2, int ext);
void	ft_env(char **env, int fd, char **arg);
char	**ft_envo(char **env);
void	sort_export(char **env);
void	ft_export(char ***export, char ***env, char **arg, int fd);
int		here(char **env, char *arg);
void	found(char *sa, char **env);
void	ft_unset(char **env, char **arg);
char	**add_str(char **env, char *plus);
char	**ft_free(char **p);
char	**equal(char *s, char c);
void	affiche_export(char **export);
int		foundin(char *sa, char **env);
int		position(char **doubl, char *str);
void	change(char ***export, char ***env, char *arg, int cas);
int		ft_cases(char **env, char **export, char *arg);
int		check_arg(char *s);
void	ft_error(char *s, char *s1, char *s2);
void	ft_errorb(char *s, char *s1, char *s2, int ext);
#endif
