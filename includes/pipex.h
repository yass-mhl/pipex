/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:45:19 by ymehlil           #+#    #+#             */
/*   Updated: 2023/03/15 17:24:25 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../ft_printf/ft_printf.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		tube[2];
	int		infile;
	int		outfile;
	char	*path;
	char	*cmd;
	char	cmd_paths;
	int		error;
	char	*error_msg;
}			t_pipex;

int			main(int ac, char **av, char **env);

void		ft_error1(void);
char		*find_path(char *cmd, char *env);
char		*take_path(char **env);
void		ft_free_all(char **tab);
void		ft_error2(t_pipex *data, char **cmd);
void		ft_error3(char **cmd);
void		ft_error4(t_pipex *data, char **cmd, int *tube);
void		ft_execute(char *av, char **env, int *tube, t_pipex *data);
void		child_process(int *tube, char **av, char **env, t_pipex *data);
void		parent_process(int *tube, char **av, char **env, t_pipex *data);
void		close_all(int *fd, t_pipex *data);

#endif
