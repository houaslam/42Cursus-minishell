/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatki <aatki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:36:28 by aatki             #+#    #+#             */
/*   Updated: 2023/04/30 13:45:39 by aatki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error(char *s)
{
	write(2, "Error\n", 7);
	write(2, s, ft_strlen(s));
	exit(1);
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
		ft_errorb("path not found\n",NULL,NULL,1);
	return (ret);
}

char	*check_env(char **env, char **cmd)
{
	int		i;
	char	**ret;
	char	*path;
	char	*temp;

	ret = ft_ret(env);
	i = -1;
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
		ft_errorb("bash: ",NULL,"command not found\n",127);
	free(ret);
	return (path);
}
