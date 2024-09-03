/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:38:05 by jweingar          #+#    #+#             */
/*   Updated: 2024/09/03 16:16:22 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	free_lst_builtin(t_builtin	**lst_builtins)
{
	int	i;

	i = 0;
	if (lst_builtins == NULL)
		return ;
	while (lst_builtins[i] != NULL)
	{
		free(lst_builtins[i]);
		i++;
	}
	free(lst_builtins);
}

t_builtin	**alloc_lst_builtins(void)
{
	t_builtin	**lst_builtins;
	int			i;

	lst_builtins = malloc(sizeof(t_builtin *) * 8);
	if (lst_builtins == NULL)
		return (perror("malloc"), NULL);
	i = 0;
	while (i < 7)
	{
		lst_builtins[i] = malloc(sizeof(t_builtin));
		if (lst_builtins[i] == NULL)
			return (perror("malloc"), NULL);
		i++;
	}
	lst_builtins[7] = NULL;
	return (lst_builtins);
}

t_builtin	**fill_lst_builtins(void)
{
	t_builtin	**lst_builtins;
	lst_builtins = alloc_lst_builtins();
	if (lst_builtins == NULL)
		return (perror("malloc"), NULL);
	lst_builtins[0]->name = "echo\0";
	lst_builtins[0]->func = ft_echo;
	lst_builtins[1]->name = "cd\0";
	lst_builtins[1]->func = ft_cd;
	lst_builtins[2]->name = "pwd\0";
	lst_builtins[2]->func = ft_pwd;
	lst_builtins[3]->name = "export\0";
	lst_builtins[3]->func = ft_export;
	lst_builtins[4]->name = "unset\0";
	lst_builtins[4]->func = ft_unset;
	lst_builtins[5]->name = "env\0";
	lst_builtins[5]->func = ft_env;
	lst_builtins[6]->name = "exit\0";
	lst_builtins[6]->func = ft_exit;
	return (lst_builtins);
}

t_function_ptr	functionpath_builtins(char *name)
{
	t_builtin		**lst_builtins;
	int				i;
	t_function_ptr	func;

	lst_builtins = fill_lst_builtins();
	i = 0;
	while (lst_builtins[i]->name != NULL)
	{
		if (ft_strncmp(lst_builtins[i]->name, name, ft_strlen(name) + 1) == 0)
		{
			func = lst_builtins[i]->func;
			return (free_lst_builtin(lst_builtins), func);
		}
		i++;
	}
	free_lst_builtin(lst_builtins);
	return (0);
}

int	exec_builtin(char **argv, t_shell *mshell)
{
	t_function_ptr	func;

	func = functionpath_builtins(argv[0]);
	if (func != NULL)
	{
		func(argv, mshell);
		return (0);
	}
	else
		return (1);
}
