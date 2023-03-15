/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:28:03 by ymehlil           #+#    #+#             */
/*   Updated: 2023/03/15 18:33:28 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error1(void)
{
	perror("Error");
	exit(errno);
}

char	*take_path(char **env)
{
	while (*env && ft_strncmp("PATH", *env, 4))
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
	}
	return (free(path), NULL);
}

void	ft_execute(char *av, char **env, int *tube, t_pipex *data)
{
	char	*path;
	char	**cmd;

	path = take_path(env);
	cmd = ft_split(av, ' ');
	if (!cmd[0])
		ft_error3(cmd);
	if (access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, env) == -1)
			ft_error2(data, cmd);
		return ;
	}
	if (!cmd[0])
		ft_error3(cmd);
	path = find_path(cmd[0], path);
	if (!path)
		ft_error4(data, cmd, tube);
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		ft_free_all(cmd);
		close_all(tube, data);
		ft_error1();
	}
}
