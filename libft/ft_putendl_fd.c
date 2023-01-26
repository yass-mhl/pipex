/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymehlil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 16:59:40 by ymehlil           #+#    #+#             */
/*   Updated: 2022/11/08 10:42:16 by ymehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	char	backslash;

	backslash = '\n';
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
	write(fd, &backslash, 1);
}
