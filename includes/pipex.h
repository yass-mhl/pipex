/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:45:19 by ymehlil           #+#    #+#             */
/*   Updated: 2023/02/11 15:44:14 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../ft_printf/ft_printf.h"
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		tube[2];
	int		f1;
	int		f2;
	char	*path;
	char	*cmd;
	char	cmd_paths;
}	t_pipex;

int
main(int ac, char **av, char **env);

void		ft_error(void);
char		*find_path(char *cmd, char *env);
char		*take_path(char **env);
void		ft_free_all(char **tab);
void		ft_execute(char *av, char **env);
void		child_process(int *tube, char **av, char **env, t_pipex *data);
void		parent_process(int *tube, char **av, char **env, t_pipex *data);
void		close_all(int *fd, t_pipex *data);

#endif
