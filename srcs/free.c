/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 21:59:01 by ymehlil           #+#    #+#             */
/*   Updated: 2023/03/15 18:34:33 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_error3(char **cmd)
{
	ft_putstr_fd("Error : command not found \n", 2);
	ft_free_all(cmd);
	exit(127);
}

void	ft_error2(t_pipex *data, char **cmd)
{
	data->error_msg = ft_strjoin("Error : command not found", cmd[0]);
	ft_putendl_fd(data->error_msg, 2);
	free(data->error_msg);
	exit(127);
}

void	ft_error4(t_pipex *data, char **cmd, int *tube)
{
	data->error_msg = ft_strjoin("Error : command not found ", cmd[0]);
	ft_putendl_fd(data->error_msg, 2);
	free(data->error_msg);
	ft_free_all(cmd);
	close_all(tube, data);
	exit(127);
}

void	close_all(int *fd, t_pipex *data)
{	
	if (data->infile != -1)
		close(data->infile);
	if (data->outfile != -1)
		close(data->outfile);
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
}
