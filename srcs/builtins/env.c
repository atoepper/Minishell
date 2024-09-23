/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:58:04 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/23 16:41:05 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		ft_printf("%s\n", envp[i++]);
	return (0);
}

int	ft_env(char **argv, t_shell *mshell, int fd)
{
	t_env	*envlst;
	int		return_val;

	if (argv[1] != NULL)
		return (ft_putstr_fd("env: too many arguments\n", 2), 1);
	envlst = mshell->envlst;
	if (envlst == NULL)
		return (1);
	while (envlst != NULL)
	{
		return_val = write(fd, envlst->key, ft_strlen(envlst->key));
		return_val = write(fd, "=", 1);
		return_val = write(fd, envlst->value, ft_strlen(envlst->value));
		return_val = write(fd, "\n", 1);
		envlst = envlst->next;
		return_val++;
	}
	return (0);
}
