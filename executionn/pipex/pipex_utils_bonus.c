/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houaslam <houaslam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:36:28 by aatki             #+#    #+#             */
/*   Updated: 2023/06/14 20:14:33 by houaslam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**ft_ret(char **env, char *error)
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
		ft_errorb("bash: ", error, ": No such file or directory\n", 1);
	return (ret);
}

char	*check_env(char **env, char **cmd)
{
	int		i;
	char	**ret;
	char	*path;
	char	*temp;

	ret = ft_ret(env,cmd[0]);
	if (!ret)
		exit(0);
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
	{
		ft_errorb("bash: ", NULL, "command not found\n", 127);
		return (NULL);
	}
	free(ret);
	return (path);
}

void	builtin_exec(t_pipe *pipe, char ***env, char ***export)
{
	int	orig_fd;
	int	orig_fd1;
	int	ph[2];

	orig_fd = dup(0);
	orig_fd1 = dup(1);
	ph[0] = 0;
	ph[1] = 1;
	if (!duping(pipe, *ph, ph))
		return;
	command(pipe->cmd, export, 1, env);
	if (ph[0] != 0)
	{
		dup2(orig_fd, 0);
		close(orig_fd);
	}
	if (ph[1] != 1)
	{
		dup2(orig_fd1, 1);
		close(orig_fd1);
	}
}

int	builtin(char *s)
{
	if (!s)
		return (0);
	if (!ft_strncmp(s, "echo", 4) || !ft_strncmp(s, "env", 3) || !ft_strncmp(s,
			"export", 6) || !ft_strncmp(s, "exit", 4) || !ft_strncmp(s, "unset",
			5) || !ft_strncmp(s, "pwd", 3) || !ft_strncmp(s, "cd", 3))
		return (1);
	else
		return (0);
}
