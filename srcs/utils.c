/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:28:03 by ymehlil           #+#    #+#             */
/*   Updated: 2023/02/11 19:03:36 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(void)
{
	perror("Error");
	exit(errno);
}

char	*take_path(char **env)
{
	while (env && ft_strncmp("PATH", *env, 4))
		env++;
	return (*env);
}

char	*find_path(char *cmd, char *env)
{
	int		i;
	char	**path;
	char	*path_cmd;
	char	*slash;

	i = 0;
	path = ft_split(env, ':');
	while (path && path[i])
	{
		slash = ft_strjoin1(path[i], "/");
		path_cmd = ft_strjoin1(slash, cmd);
		if (access(path_cmd, X_OK) == 0)
			return (path_cmd);
		i++;
		free(path_cmd);
		// free(slash);
	}
	return (NULL);
}

void	ft_execute(char *av, char **env, int *tube, t_pipex *data)
{
	char	*path;
	char	**cmd;
	int		i;

	path = take_path(env);
	cmd = ft_split(av, ' ');
	if (access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, env) == -1)
		{
			ft_putstr_fd("Error : command not found ", 2);
			ft_putendl_fd(cmd[0], 2);
			// ft_error();
		}
		return ;
	}
	else
		path = find_path(cmd[0], path);
	if (!path)
	{
		ft_putstr_fd("Error : command not found ", 2);
		ft_putendl_fd(cmd[0], 2);
		ft_free_all(cmd);
		close_all(tube, data);
		exit(127);
		// ft_error();
	}
	i = execve(path, cmd, env);
	if (i == -1)
	{
		free(path);
		ft_free_all(cmd);
		ft_error();
	}
}
