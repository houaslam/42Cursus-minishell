/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:36:28 by aatki             #+#    #+#             */
/*   Updated: 2023/03/10 19:55:20 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	while (s1[++i])
		join[i] = s1[i];
	i = -1;
	while (s2[++i])
		join[ft_strlen(s1) + i] = s2[i];
	join[ft_strlen(s1) + i] = '\0';
	free(s1);
	return (join);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n - 1 && s1[i] == s2[i])
		i++;
	if ((unsigned char)s1[i] < (unsigned char)s2[i])
		return (-1);
	else if ((unsigned char)s1[i] > (unsigned char)s2[i])
		return (1);
	else
		return (0);
}

char	**ft_ret(char **env)
{
	int		i;
	char	**ret;

	i = -1;
	ret = NULL;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			ret = ft_split(env[i] + 5, ':');
	}
	if (!ret)
		ft_error("path not found");
	return (ret);
}

char	*check_env(char **env, char **cmd)
{
	int		i;
	char	**ret;
	char	*path;
	char	*temp;

	i = -1;
	ret = ft_ret(env);
	while (ret[++i])
	{
		temp = ft_strjoin(ret[i], "/");
		path = ft_strjoin(temp, cmd[0]);
		if (access(path, R_OK) == 0)
			break ;
		else
			free(path);
	}
	if (access(path, R_OK) == -1)
		ft_error("no access to the command\n");
	free(ret);
	return (path);
}
