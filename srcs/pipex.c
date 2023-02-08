/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:48:46 by ymehlil           #+#    #+#             */
/*   Updated: 2023/02/08 16:50:00 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*take_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T')
			return (env[i]);
		i++;
	}
	return (NULL);
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
	return (NULL);
	
}

int	main(int ac, char **av, char **env)
{
	char *path;
	char **cmd;
	(void)ac;
	
	path = take_path(env);
	// AV[1] PROVISOIRE !!! A CHANGER
	cmd = ft_split(av[1], ' ');
	path = find_path(cmd[0], path);
	ft_printf("%s\n", cmd[0]);
	ft_printf("%s\n", path);
	execve(path, cmd, env);
}
