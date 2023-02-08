/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:28:03 by ymehlil           #+#    #+#             */
/*   Updated: 2023/02/08 23:58:30 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void    ft_error(void)
{
    perror("Error");
    exit(EXIT_FAILURE);
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
	}
	return (NULL);
	
}

void   ft_execute(char *av, char **env)
{
    char	*path;
	char	**cmd;
    int i;
    if (access(av, X_OK) == 0)
    {
        path = av;
    }
    else
    {
        path = take_path(env);
        cmd = ft_split(av, ' ');
        path = find_path(cmd[0], path);
        if (!path)
        {
            ft_free_all(cmd);
            ft_error();
        }
    }
    i = execve(path, cmd, env);
    if (i == -1)
    {
        ft_free_all(cmd);
        free(path);
        ft_error();
    }
}