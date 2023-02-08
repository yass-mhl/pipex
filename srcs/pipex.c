/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:48:46 by ymehlil           #+#    #+#             */
/*   Updated: 2023/02/08 21:09:23 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

void child_process(int f1, char *cmd)
{
	dup2()
}

void	pipex(int f1, int f2, char *cmd1, char *cmd2)
{
	int	end[2];
	pid_t	pid;
	
	pipe(end);
	pid = fork();
	if (parent < 0)
		return(perror("Fork : "));
	if (!parent)
		child_process(f1, cmd1);
	else
		parent_process(f2, cmd2);
}

int	main(int ac, char **av, char **env)
{
	char	*path;
	char	**cmd;
	int		f1;
	int		f2;
	
	if (ac != 5)
		return (ft_printf("Error\n: not the right amount of args"), 0);
	path = take_path(env);
	// AV[1] PROVISOIRE !!! A CHANGER
	cmd = ft_split(av[2], ' ');
	path = find_path(cmd[0], path);
	if (!path)
		return (ft_printf("Error\nnot path found"), 0);
	f1 = open(av[1], O_RDONLY);
	f2 = open(av[ac - 1], O_TRUNC | O_RDONLY | O_CREAT);

	execve(path, cmd, env);
}
