/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:48:46 by ymehlil           #+#    #+#             */
/*   Updated: 2023/02/10 03:45:47 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void child_process(int *tube, char **av, char **env)
{
	int	infile;
	
	infile = open(av[1], O_RDONLY);
	if (infile == -1)
		ft_error();
	dup2(tube[1], STDOUT_FILENO);
	dup2(infile, STDIN_FILENO);
	close_all(tube);
	ft_execute(av[2], env);	
}

void	parent_process(int *tube, char **av, char **env)
{
	int	outfile;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC);
	if (outfile == -1)
		ft_error();
	dup2(tube[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close_all(tube);
	ft_execute(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		tube[2];
	pid_t	pid1;
	pid_t	pid2;
	
	if (ac != 5)
		return (ft_printf("Error\n: not the right amount of args"), 0);
	if (pipe(tube) == -1)
		ft_error();
	pid1 = fork();
	if (pid1 == -1)
		ft_error();
	if (pid1 == 0)
		child_process(tube, av, env);
	pid2 = fork();
	if (pid2 == 0)
		parent_process(tube, av, env);
	close_all(tube);	
	waitpid(pid1, NULL, 0);	
	waitpid(pid2, NULL, 0);	
}
