/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_function_buildin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:24:37 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/19 12:27:05 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	is_function_builtin(char *name)
{
	char	*lst_builtins[8];
	int		i;

	lst_builtins[0] = "echo\0";
	lst_builtins[1] = "cd\0";
	lst_builtins[2] = "pwd\0";
	lst_builtins[3] = "export\0";
	lst_builtins[4] = "unset\0";
	lst_builtins[5] = "env\0";
	lst_builtins[6] = "exit\0";
	lst_builtins[7] = NULL;
	i = 0;
	while (lst_builtins[i] != NULL)
	{
		if (ft_strncmp(lst_builtins[i], name, ft_strlen(name) + 1) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(void)
{
	char name[] = "echso";

	printf("is %s in list? %i\n", name, is_function_builtin(name));
	return (0);
}