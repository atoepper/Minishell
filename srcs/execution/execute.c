/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:09:29 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/20 13:53:36 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	exec_function(char **argv)
{
	if (argv == NULL)
		return (0);
	if (exec_builtin(argv))
		if (exec_external(argv))
			printf("command not found: %s\n", argv[0]);
	return (0);
}

char	*read_fd_to_str(int fd)
{
	char	buffer[1024];
	char	*str;
	int		rt_read;

	rt_read = read(fd, buffer, 1024);
	if (rt_read < 0)
		return (perror("read"), NULL);
	else
	{
		str = ft_strdup(buffer);
		if (str == NULL)
			return (NULL);
	}
	return (str);
}
