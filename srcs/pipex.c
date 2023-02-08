/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:48:46 by ymehlil           #+#    #+#             */
/*   Updated: 2023/02/08 23:44:16 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void child_process(int *tube, char **av, char **env)
{
	int	infile;
	
	infile = open(av[1], O_RDONLY);
	if (infile == -1)
	{
		write(1, "1", 1);
		ft_error();
	}	
	dup2(tube[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close(tube[0]);
	ft_execute(av[2], env);	
}

void	parent_process(int *tube, char **av, char **env)
{
	int		outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC);
	if (outfile == -1)
	{
		write(1, "1", 1);
		ft_error();
	}
		
	dup2(tube[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(tube[1]);
	ft_execute(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	// int		f1;
	// int		f2;
	int		tube[2];
	pid_t	pid;
	
	if (ac != 5)
		return (ft_printf("Error\n: not the right amount of args"), 0);
	if (pipe(tube) == -1)
		ft_error();
	pid = fork();
	if (pid == -1)
		ft_error();
	if (!pid)
		child_process(tube, av, env);
	waitpid(pid, NULL, 0);
	parent_process(tube, av, env);
	// path = take_path(env);
	// AV[1] PROVISOIRE !!! A CHANGER
	// cmd = ft_split(av[2], ' ');
	// path = find_path(cmd[0], path);
	// if (!path)
	// 	return (ft_printf("Error\nnot path found"), 0);
	
	
	// f1 = open(av[1], O_RDONLY);
	// f2 = open(av[ac - 1], O_TRUNC | O_RDONLY | O_CREAT);

	// execve(path, cmd, env);
}
