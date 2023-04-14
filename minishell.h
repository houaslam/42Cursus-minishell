/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:32:03 by houaslam          #+#    #+#             */
/*   Updated: 2023/04/13 03:29:46 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PIPE  124
# define RED_IN  60
# define RED_OUT  62
# define D_QUOT  34
# define S_QUOT  39
# define IN_FILE 2
# define STRING 1
# define BUILTIN 4
# define OUT_FILE 3
# define HERE_DOC_IN 5
# define HERE_DOC_OUT 6
# define EXIT_STATUS 7
# define ENV_VAR 8

# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>
# include<string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include"libft/libft.h"

typedef struct env
{
	char		*path;
	char		*name;
	struct env	*next;
	struct env	*prev;
}			t_env;

typedef struct s_file
{
	int				type;
	char			*file;
	struct s_file	*next;
	struct s_file	*prev;
}			t_file;

typedef struct exec
{
	int			type;
	char		**cmd;
	int			cmd_nb;
	char		*value;
	struct exec	*next;
	struct exec	*prev;
}			t_exec;

typedef struct s_data
{
	int			g_exit_status;
	char		*join;
	t_file		*file;
	t_env		*env;
	t_exec		*exec;
	char		*s;
}			t_data;

//libft
int		ft_dim1(char *s, char c);
char	**ft_freestr(char **arr, int p);
char	**ft_func(char **arr, char *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s);
// linked list
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstnew(char *name, char *path);
int		ft_lstsize(t_env *lst);
t_env	*ft_lstlast(t_env *lst);

// linked list
void	ft_lstadd_back_exec(t_exec **lst, t_exec *new);
t_exec	*ft_lstnew_exec(char *value, int type);
int		ft_lstsize_exec(t_exec *lst);
t_exec	*ft_lstlast_exec(t_exec *lst);
void	free_exec(t_exec **exec);

// linked list
void	ft_lstadd_back_file(t_file **lst, t_file *new);
t_file	*ft_lstnew_file(char *value, int type);
int		ft_lstsize_file(t_file *lst);
t_file	*ft_lstlast_file(t_file *lst);
void	free_file(t_file **file);

//env
void	creat_env(char **en, t_data **data);
void	aff(t_env *env);
void	aff1(t_exec *env);
void	aff2(t_file *env);

//tokens
void	lexer(t_data *data);
int		handle_pipe(t_data *data, int i);
int		handle_redin(t_data *data, int i);
int		handle_string(t_data *data, int i);
int		handle_redout(t_data *data, int i);
int		handle_d_quote(t_data *data, int i);
int		handle_s_quote(t_data *data, int i);
int		handle_here_doc_in(t_data *data, int i);
int		handle_dollar_sign(t_data *data, int i);
int		handle_here_doc_out(t_data *data, int i);
int		handle_env_var(t_data *data, int i, int k);

//outils
char	*seach_env_value(char *str, t_data *data);
int		print_token_er(t_data *data);

#endif