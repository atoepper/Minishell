/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:29:53 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/15 15:26:33 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_echo(int argc, ...)
{
	va_list	args;
	char	*flag;
	char	*tmp_str;

	va_start(args, argc);
	flag = ft_strdup(va_arg(args, char *));
	if (flag == NULL)
		return(-1);
	if (ft_strncmp(flag, "-n", 3) == 0)
		argc--;
	else if (argc > 0)
	{
		tmp_str = ft_strtrim(flag, "\'\"");
		printf("%s", tmp_str);
		free(tmp_str);
		argc--;
		if (argc > 0)
			printf(" ");
	}
	if (argc > 0)
	{
		tmp_str = ft_strtrim(va_arg(args, char *), "\'\"");
		printf("%s", tmp_str);
		free(tmp_str);
		argc--;
	}
	while (argc > 0)
	{
		tmp_str = ft_strtrim(va_arg(args, char *), "\'\"");
		printf(" %s", tmp_str);
		free(tmp_str);
		argc--;
	}
	if (ft_strncmp(flag, "-n", 3) != 0)
		printf("\n");
	va_end(args);
	free(flag);
	return (0);
}
