/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:32:03 by houaslam          #+#    #+#             */
/*   Updated: 2023/03/25 13:01:20 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>
# include<string.h>

typedef struct data
{
	char	**env;
}			t_data;

typedef struct env
{
	char		*path;
	char		*name;
	struct env	*next;
}			t_env;

//libft
int		ft_dim1(char *s, char c);
char	**ft_freestr(char **arr, int p);
char	**ft_func(char **arr, char *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstnew(char *name, char *path);
int	ft_lstsize(t_env *lst);
t_env	*ft_lstlast(t_env *lst);

//env
void	creat_env(char **en, t_env *env);
char    *name(char *env);
char    *path(char *env);

void	aff(t_env *env);


#endif