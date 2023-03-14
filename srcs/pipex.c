/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:48:46 by ymehlil           #+#    #+#             */
/*   Updated: 2023/03/14 17:24:43 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(int *tube, char **av, char **env, t_pipex *data)
{
	if (data->infile == -1)
		ft_error1();
	dup2(tube[1], STDOUT_FILENO);
	dup2(data->infile, STDIN_FILENO);
	close(tube[0]);
	close(tube[1]);
	ft_execute(av[2], env, tube, data);
}

void	parent_process(int *tube, char **av, char **env, t_pipex *data)
{
	if (data->outfile == -1)
		ft_error1();
	dup2(tube[0], STDIN_FILENO);
	dup2(data->outfile, STDOUT_FILENO);
	close(tube[0]);
	close(tube[1]);
	ft_execute(av[3], env, tube, data);
}

int	main(int ac, char **av, char **env)
{
	int		tube[2];
	pid_t	pid1;
	pid_t	pid2;
	t_pipex	data;

	if (ac != 5)
		return (ft_printf("Error\n: not the right amount of args"), 0);
	if (pipe(tube) == -1)
		ft_error1();
	data.infile = open(av[1], O_RDONLY, 0644);
	data.outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid1 = fork();
	if (pid1 == -1)
		ft_error1();
	if (pid1 == 0)
		child_process(tube, av, env, &data);
	pid2 = fork();
	if (pid2 == 0)
		parent_process(tube, av, env, &data);
	close_all(tube, &data);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
