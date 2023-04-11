/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:32:03 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/11 23:20:51 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct t_cmd
{
	char			*cmd;
	struct t_cmd	*next_cmd;
}					t_cmd;

typedef struct t_pipe
{
	t_cmd			c;
	struct t_pipe	*next_pipe;
	char			*infile;
	char			*outfile;
	char			*heredoc;
}					t_pipe;

//execution
//builtins

void				ft_echo(char **str, int fd, char **env);
void				ft_pwd(int fd);
void				ft_exit(int e);
void				ft_echo(char **s, int fd, char **env);
void				found(char *sa, char **env);
void				ft_cd(char **env, char *dir);
//
void				ft_error(char *s);
void				ft_env(char **env, char *arg, int fd);
char				**ft_envo(char **env);
void				sort_env(char **env);
void				ft_export(char **env, char *arg, int fd,char *plus);
int					here(char **env, char *arg);
void				found(char *sa, char **env);
void				sort_env(char **env);
void				ft_unset(char **env, char *arg);
char				**ft_envoo(char **env,char *plus);
#endif